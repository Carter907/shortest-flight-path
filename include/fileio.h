#ifndef FILEIO_H
#define FILEIO_H

#include "Graph.h"

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <unordered_map>

/**
 * @brief Loads a mapping of airport IATA codes to airport names from a CSV file.
 *
 * This function reads the 'airports.csv' file, which is expected to contain airport
 * information. It parses the CSV data to create a map where the key is the
 * 3-letter IATA code of an airport and the value is the full name of the airport.
 * This map can be used to look up airport names based on their IATA codes.
 *
 * @return std::unordered_map<std::string, std::string> An unordered map containing
 *         IATA codes as keys and airport names as values.
 */
std::unordered_map<std::string, std::string> loadAirportCodeMapCSV();

/**
 * @brief Loads flight data from a CSV file into a Graph data structure.
 *
 * This function is responsible for reading a CSV file specified by the file path.
 * Each row in the CSV is expected to represent a flight, containing information
 * such as the source and destination airport IATA codes. This data is then used to
 * construct a graph where airports are vertices and flights are edges.
 *
 * @param file_path The path to the CSV file containing flight data.
 * @return Graph A graph object representing the flight network, with airports
 *         as vertices and flights as edges.
 */
Graph loadFlightsCSV(std::string file_path);
#endif