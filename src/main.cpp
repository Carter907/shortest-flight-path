#include "../include/Graph.h"
#include "../include/fileio.h"
#include <iostream>
#include <string>

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

  std::cout << "reading from flight data...\n";

  // loading airport map

  auto airportMap = loadAirportCodeMapCSV("assets/airports.csv");

  // check if airports are in map

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

  // load flight connections graph for January 2025.

  Graph flight_graph = loadFlightsCSV("assets/FlightConnectionsJan2025.csv");

  // get shortest route and distance for flights from and to user specified
  // airports.

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
