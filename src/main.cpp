#include "Graph.hpp"
#include <fstream>
#include <iostream>
#include <sstream>
#include <stdexcept>
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

int main(int argc, char *argv[]) {

  // parse arguments

  if (argc != 5) {
    std::cerr << "Invalid number of arguments\nPlease define -s (source "
                 "airport) and -d (destination airport)\n";
    return 1;
  } else if (std::string(argv[1]) != "--source" &&
             std::string(argv[1]) != "-s") {
    std::cerr << "Source not defined\n";
    return 1;
  } else if (std::string(argv[3]) != "--destination" &&
             std::string(argv[3]) != "-d") {
    std::cerr << "Destination not defined\n";
    return 1;
  }

  std::string user_source{argv[2]}, user_destination{argv[4]};

  if (user_source.length() > 3 || user_source.length() < 3) {
    std::cerr << "Invalid source format\nPlease use the Buearu of "
                 "Transportation Statistics airport codes\n";
    return 1;
  }
  if (user_destination.length() > 3 || user_destination.length() < 3) {
    std::cerr << "Invalid destination format\nPlease use the Buearu of "
                 "Transportation Statistics airport codes\n";
    return 1;
  }

  Graph flight_graph;

  std::cout << "reading from flight data...\n";

  // loading airport map

  auto airportMap = loadAirportData("airports.csv");

  if (airportMap.find(user_source) == airportMap.end()) {
    std::cerr << "Source \'" << user_source
              << "\' not found\nPlease try another airport code\n";
    return 0;
  }
  if (airportMap.find(user_destination) == airportMap.end()) {
    std::cerr << "Destination \'" << user_destination
              << "\' not found\nPlease try another airport code\n";
    return 0;
  }

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

    if (actual_time.empty() || estimated_time.empty() || dist.empty())
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

  std::vector<std::string> flight_route;
  auto route_dist =
      flight_graph.shortestPath(user_source, user_destination, flight_route);

  std::cout << "The closest route between " << user_source << " and "
            << user_destination << " is from ";

  for (int i = 0; i < flight_route.size(); i++) {
    if (i == flight_route.size() - 1) {
      std::cout << flight_route[i];
      continue;
    }
    std::cout << flight_route[i] << " to ";
  }

  std::cout << "\nThe total distance is " << route_dist << " miles\n";

  return 0;
}
