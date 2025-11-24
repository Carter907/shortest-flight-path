#include "../include/Graph.h"
#include "../include/cli.h"
#include "../include/fileio.h"
#include <iostream>
#include <string>

int main(int argc, char *argv[]) {

  try {
    parse_args(argc, argv);
  } catch (const std::runtime_error &e) {
    std::cerr << e.what() << std::endl;
    return 1;
  }

  std::string user_source{argv[2]}, user_destination{argv[4]},
      flights_csv{argv[6]};

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

  if (flights_csv.substr(flights_csv.size() - 4, 4) != ".csv") {

    std::cerr << "Invalid file format\nPlease use a csv file\n";
    return 1;
  }

  std::cout << "Reading from flight data...\n";

  auto airportMap = loadAirportCodeMapCSV();

  if (airportMap.find(user_source) == airportMap.end()) {
    std::cerr << "Source '" << user_source
              << "' not found\nPlease try another airport code\n";
    return 0;
  }
  if (airportMap.find(user_destination) == airportMap.end()) {
    std::cerr << "Destination '" << user_destination
              << "' not found\nPlease try another airport code\n";
    return 0;
  }

  Graph flight_graph = loadFlightsCSV(flights_csv);

  std::vector<std::string> flight_route;

  auto route_dist =
      flight_graph.shortestPath(user_source, user_destination, flight_route);

  std::cout << "\n✈️  Shortest Flight Route ✈️\n\n";
  if (route_dist > 15000) {

    std::cout
        << "It looks like you chose two airports that are not connected! \n"
           "According to Dijkstra's algorithm, They have a distance of \n"
           "infinity miles!\n";

  } else {

    std::cout << "The closest route between\n"
              << (airportMap.find(user_source) != airportMap.end()
                      ? airportMap[user_source]
                      : user_source)
              << " and "
              << (airportMap.find(user_destination) != airportMap.end()
                      ? airportMap[user_destination]
                      : user_destination)
              << " is:\n";
    std::cout << '\n';

    for (int i = 0; i < flight_route.size(); i++) {
      if (i == flight_route.size() - 1) {
        std::cout << flight_route[i];
        continue;
      }
      std::cout << flight_route[i] << " -> ";
    }
    std::cout << "\n\n";
    std::cout << "Total distance: " << route_dist << " miles\n";
  }

  return 0;
}
