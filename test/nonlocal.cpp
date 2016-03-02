#include <sstream>

#include "gtest/gtest.h"
#include "tz.h"

template<class Duration>
const char* toString( std::pair<std::chrono::time_point<std::chrono::system_clock, Duration>, std::string>& p ) {
   using namespace date;
   static std::ostringstream oss;

   oss.str( "" );

   oss << p.first << " " << p.second;

   return oss.str().c_str();
}


TEST( nonlocal, birthday ) {
   auto hnl_tz = date::locate_zone( "Pacific/Honolulu" );
   auto nyc_tz = date::locate_zone( "America/New_York" );
   auto teh_tz = date::locate_zone( "Asia/Tehran" );
   auto utc_tz = date::locate_zone( "UTC" );
   auto yeg_tz = date::locate_zone( "America/Edmonton" );

   std::map<const date::Zone*, std::string> zones = {
        { hnl_tz, "1971-03-31 22:06:00 HST" }
      , { nyc_tz, "1971-04-01 03:06:00 EST" }
      , { teh_tz, "1971-04-01 11:36:00 IRST" }
      , { utc_tz, "1971-04-01 08:06:00 UTC" }
      , { yeg_tz, "1971-04-01 01:06:00 MST" }
   };

   auto birth = date::day_point( date::apr / 1 / 1971 ) + std::chrono::hours{ 1 } + std::chrono::minutes{ 6 };
   auto tp_sys = yeg_tz->to_sys( birth );

   using namespace date;

   for ( auto zone : zones ) {
      auto local = zone.first->to_local( tp_sys );

      ASSERT_STREQ( zone.second.c_str(), toString( local ) );
   }
}


TEST( nonlocal, convertLocalToDesired ) {
   std::tm tm{ 0 };

   // populate tm with data for the desired tm
   tm.tm_year = 1971 - 1900;
   tm.tm_mon = 4 - 1;
   tm.tm_mday = 1;
   tm.tm_hour = 1;
   tm.tm_min = 6;
   tm.tm_isdst = -1;

   // convert to time_point
   auto local_t = std::mktime( &tm ); // mktime assumes that tm is in localtime
   auto local_tp = std::chrono::system_clock::from_time_t( local_t );

   // convert local to desired
   auto local_tz = date::current_zone();
   auto local_info = local_tz->get_info( local_tp, date::tz::utc );
   auto yeg_tz = date::locate_zone( "America/Edmonton" );
   auto yeg_info = yeg_tz->get_info( local_tp, date::tz::utc );
   auto offset = std::chrono::seconds { local_info.offset } - std::chrono::seconds { yeg_info.offset };
   auto yeg_tp = local_tp + offset; // convert local_tp to desired tp
   auto yeg = yeg_tz->to_local( yeg_tp ); // convert yeg_tp to pair

   ASSERT_STREQ( "1971-04-01 01:06:00.000000000 MST", toString( yeg ) );
}

