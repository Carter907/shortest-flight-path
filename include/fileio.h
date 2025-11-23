
#ifndef FILEIO_H
#define FILEIO_H

#include "Graph.h"

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <unordered_map>

std::unordered_map<std::string, std::string> loadAirportCodeMapCSV();

Graph loadFlightsCSV(std::string file_path);
#endif
