#include "Graph.hpp"
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <unordered_map>

std::unordered_map<std::string, std::string>
loadAirportData(const std::string &filename) {
  std::unordered_map<std::string, std::string> database;
  std::ifstream file(filename);
  std::string line;

  if (!file.is_open()) {
    std::cerr << "Error opening file!" << std::endl;
    return database;
  }

  while (std::getline(file, line)) {
    std::stringstream ss(line);
    std::string code, name;

    // Assuming CSV format is: JFK,John F. Kennedy International Airport
    if (std::getline(ss, code, ',') && std::getline(ss, name)) {
      database[code] = name;
    }
  }

  return database;
}

int main() {
  Graph flight_graph;

  std::cout << "reading from flight data...\n";

  // loading airport map

  auto airportMap = loadAirportData("airports.csv");

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

    if (actual_time.empty())
      continue;

    unsigned long actual_time_ul = std::stoul(actual_time);
    unsigned long estimated_time_ul = std::stoul(estimated_time);
    unsigned long dist_ul = std::stoul(dist);

    flight_graph.addVertex(origin);
    flight_graph.addVertex(dest);
    flight_graph.addEdge(origin, dest, actual_time_ul, estimated_time_ul,
                         dist_ul);
  }

  flight_data.close();

  return 0;
}
