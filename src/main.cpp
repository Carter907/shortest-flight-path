#include "Graph.hpp"
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

int main() {
  Graph flight_graph;

  std::cout << "reading from flight data...\n";
  // Constructing distance and time graphs from input csv file.
  std::ifstream flight_data{"FlightConnectionsJan2025.csv"};

  if (!flight_data) {

    std::cerr << "Could not read from input data\n";
    return 1;
  }

  std::string flight_line{};
  std::getline(flight_data, flight_line); // take in redundant line

  char delim = ',';

  while (std::getline(flight_data, flight_line)) {
    std::stringstream flight_line_stream(flight_line);

    std::string origin, dest, actual_time, estimated_time, dist;

    std::getline(flight_line_stream, origin, delim);
    std::getline(flight_line_stream, dest, delim);
    std::getline(flight_line_stream, actual_time, delim);
    std::getline(flight_line_stream, estimated_time, delim);
    std::getline(flight_line_stream, dist, delim);

    flight_graph.addVertex(origin);
    flight_graph.addVertex(dest);
    flight_graph.addEdge(origin, dest, actual_time, estimated_time, dist);
  }

  flight_data.close();

  // g.addEdge("1", "2", 7);

  // std::vector<std::string> path;

  // unsigned long distance = dist_graph.shortestPath("1", "5", path);

  // std::cout << "Shortest Path from 1 to 5: ";
  // for (size_t i = 0; i < path.size(); ++i) {
  //   std::cout << path[i] << (i < path.size() - 1 ? " -> " : "");
  // }
  // std::cout << "\nTotal Distance: " << distance << std::endl;

  return 0;
}
