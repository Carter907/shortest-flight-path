#include "../include/fileio.h"
#include "../include/Graph.h"
#include <stdexcept>

std::unordered_map<std::string, std::string>
loadAirportCodeMapCSV(const std::string &filename) {
  std::unordered_map<std::string, std::string> database;
  std::ifstream file(filename);
  std::string line;

  if (!file.is_open()) {
    throw std::runtime_error("Failed to load airport code data"
                             "\nPlease check your executable location");
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

Graph loadFlightsCSV(std::string file_path) {
  Graph flight_graph;
  std::ifstream flight_data{file_path};

  if (!flight_data) {

    throw std::runtime_error("Failed to load flight path data"
                             "\nPlease check your executable location");
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
    flight_graph.addEdge(origin, dest, dist_ul, actual_time_ul,
                         estimated_time_ul);
  }

  return flight_graph;
}
