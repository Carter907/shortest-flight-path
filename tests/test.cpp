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

  auto shortest_route{std::vector<std::string>()};
  auto dist = flightsNetwork.shortestPath("LAX", "SUN", shortest_route);

  REQUIRE(dist == 170);
  REQUIRE(shortest_route == std::vector<std::string>{"LAX", "DEN", "SUN"});
}

TEST_CASE("test", "[mock graph used]") {

  Graph basic_graph;

  basic_graph.addVertex("A");
  basic_graph.addVertex("B");
  basic_graph.addVertex("C");
  basic_graph.addVertex("D");
  basic_graph.addVertex("E");

  basic_graph.addEdge("A", "B", 4);
  basic_graph.addEdge("A", "C", 8);
  basic_graph.addEdge("B", "D", 6);
  basic_graph.addEdge("C", "E", 2);
  basic_graph.addEdge("C", "B", 3);
  basic_graph.addEdge("D", "E", 10);

  auto shortest_route{std::vector<std::string>()};
  auto dist = basic_graph.shortestPath("A", "E", shortest_route);

  REQUIRE(dist == 9);
  REQUIRE(shortest_route == std::vector<std::string>{"A", "B", "C", "E"});
}
