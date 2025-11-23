#define CATCH_CONFIG_MAIN

#include "../external/catch2/catch_amalgamated.hpp"
#include "../include/fileio.h"

// TEST_CASE("Graph ADT", "[basic operations]") {

//   REQUIRE(1 == 1); // not implemented yet so it fails.
// }

// TEST_CASE("Shortest Path of Flights", "[mock graph used]") {

//   Graph flightsNetwork;

//   flightsNetwork.addVertex("LAX");
//   flightsNetwork.addVertex("DEN");
//   flightsNetwork.addVertex("JFK");
//   flightsNetwork.addVertex("SUN");

//   flightsNetwork.addEdge("LAX", "DEN", 120, 0, 0);
//   flightsNetwork.addEdge("LAX", "SUN", 400, 0, 0);
//   flightsNetwork.addEdge("LAX", "JFK", 385, 0, 0);

//   flightsNetwork.addEdge("SUN", "DEN", 557, 0, 0);
//   flightsNetwork.addEdge("SUN", "LAX", 696, 0, 0);

//   flightsNetwork.addEdge("DEN", "SUN", 50, 0, 0);

//   flightsNetwork.addEdge("JFK", "SUN", 283, 0, 0);

//   auto shortest_route{std::vector<std::string>()};
//   auto dist = flightsNetwork.shortestPath("LAX", "SUN", shortest_route);

//   REQUIRE(dist == 170);
//   REQUIRE(shortest_route == std::vector<std::string>{"LAX", "DEN", "SUN"});
// }

TEST_CASE("Shortest Path of Flights", "[test file used]") {

  auto flightsNetwork = loadFlightsCSV("./assets/flights-test-data.csv");

  for (const auto &[origin, airport] : flightsNetwork.getVertices()) {

    for (const auto &flight : airport->getEdges()) {

      std::cout << "edge: { " << origin << " to "
                << flight.getDestinationLabel()
                << ", dist: " << flight.getDistance() << " miles }\n";
    }
  }

  auto shortest_route{std::vector<std::string>()};
  auto dist = flightsNetwork.shortestPath("LAX", "SUN", shortest_route);

  REQUIRE(dist == 170);
  REQUIRE(shortest_route == std::vector<std::string>{"LAX", "DEN", "SUN"});
}
