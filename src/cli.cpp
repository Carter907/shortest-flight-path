#include "../include/cli.h"
#include <iostream>
#include <stdexcept>
#include <string>

void print_usage() {
  std::cout << "Usage: ./flightpath --source <source_airport> --destination "
               "<destination_airport> --flight-data <flight_data_csv>"
            << std::endl;
}

void parse_args(int argc, char **argv) {
  if (argc == 2 &&
      (std::string(argv[1]) == "-h" || std::string(argv[1]) == "--help")) {
    print_usage();
    exit(0);
  }
  if (argc != 7) {
    throw std::runtime_error(
        "Invalid number of arguments\n"
        "Please define -s (source airport), -d (destination airport), and -f "
        "(flight data path)\n"
        "For help, run ./flightpath --help");
  } else if (std::string(argv[1]) != "--source" &&
             std::string(argv[1]) != "-s") {
    throw std::runtime_error(
        "Invalid argument\n"
        "Please define -s (source airport), -d (destination airport), and -f "
        "(flight data path)\n"
        "For help, run ./flightpath --help");
  } else if (std::string(argv[3]) != "--destination" &&
             std::string(argv[3]) != "-d") {
    throw std::runtime_error(
        "Invalid argument\n"
        "Please define -s (source airport), -d (destination airport), and -f "
        "(flight data path)\n"
        "For help, run ./flightpath --help");
  } else if (std::string(argv[5]) != "--flight-data" &&
             std::string(argv[5]) != "-f") {
    throw std::runtime_error(
        "Invalid argument\n"
        "Please define -s (source airport), -d (destination airport), and -f "
        "(flight data path)\n"
        "For help, run ./flightpath --help");
  }
}
