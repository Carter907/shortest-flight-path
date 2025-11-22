#include "src/fileio.h"
#include <catch2/catch_test_macros.hpp>

TEST_CASE("Graph ADT", "[basic operations]") {

  REQUIRE(0 == 1); // not implemented yet so it fails.
}

TEST_CASE("Shortest Path of Flights", "[test file used]") {

  auto airportMap = loadAirportCodeMapCSV("airports.csv");
  auto flightsNetwork = loadFlightsCSV("flights-test-data.csv");

  auto shortest_route{std::vector<std::string>()};
  auto dist = flightsNetwork.shortestPath("LAX", "SUN", shortest_route);

  REQUIRE(dist == 170);
  REQUIRE(shortest_route ==
          std::vector<std::string>{"LAX", "DEN", "JFK", "SUN"});
}
