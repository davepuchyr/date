#include <sstream>

#include "gtest/gtest.h"
#include "tz.h"


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

   std::ostringstream oss;
   using namespace date;

   for ( auto zone : zones ) {
      auto local = zone.first->to_local( tp_sys );

      oss.str( "" );

      oss << local.first << " " << local.second;

      ASSERT_STREQ( zone.second.c_str(), oss.str().c_str() );
   }
}

