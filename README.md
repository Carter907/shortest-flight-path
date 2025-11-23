# Shortest Flight Path

This project is a C++ application that calculates the shortest flight path between two airports based on distance. It uses a graph data structure to represent airports and flight connections, and Dijkstra's algorithm to find the shortest path.

## Project Structure

The project is organized into the following directories:

```
.
├── assets/
│   ├── airports.csv
│   └── FlightConnectionsJan2025.csv
├── include/
│   ├── fileio.h
│   ├── Graph.h
│   └── GraphBase.h
├── src/
│   ├── fileio.cpp
│   ├── Graph.cpp
│   └── main.cpp
├── tests/
│   └── test.cpp
└── external/
    └── catch2/
```

-   `assets/`: Contains the data files used by the application.
-   `include/`: Header files for the core components of the project.
-   `src/`: Source code files for the implementation of the core components and the main application.
-   `tests/`: Unit tests for the project.
-   `external/`: Contains external libraries, in this case, the Catch2 testing framework.

## Core Components

### `Graph`

The `Graph` class (defined in `include/Graph.h` and implemented in `src/Graph.cpp`) is the core of the application. It represents the flight network as a directed graph where:

-   **Vertices** are airports, identified by their 3-letter IATA code.
-   **Edges** are flight connections between airports, with a weight corresponding to the distance in miles.

The graph is implemented using an adjacency list (`std::map`), which maps each airport's IATA code to a `Vertex` struct. The `Vertex` struct contains the airport's label and a list of `Edge` structs, each representing a flight to another airport.

The `shortestPath` method implements Dijkstra's algorithm to find the shortest path between two airports.

### `fileio`

The `fileio` component (defined in `include/fileio.h` and implemented in `src/fileio.cpp`) is responsible for loading data from the CSV files in the `assets` directory.

-   `loadAirportCodeMapCSV`: Loads the airport data from `airports.csv`.
-   `loadFlightsCSV`: Loads the flight connection data from `FlightConnectionsJan2025.csv` and constructs a `Graph` object.

### `main`

The `main` function (in `src/main.cpp`) provides a command-line interface (CLI) for the application. It parses the source and destination airport codes from the command-line arguments, loads the flight data, calculates the shortest path using the `Graph` class, and prints the result to the console.

## Data

The application uses two CSV files located in the `assets` directory:

-   `airports.csv`: Contains a list of airports with their IATA codes and names.
-   `FlightConnectionsJan2025.csv`: Contains flight connection data for January 2025, including the origin, destination, and distance of each flight.

## Building and Running

To build and run the project, you can use a C++ compiler like `g++`.

### Building the Application

```sh
g++ -std=c++17 -I./include/ src/main.cpp src/Graph.cpp src/fileio.cpp -o flightpath
```

### Running the Application

The application expects the source and destination airport codes as command-line arguments.

**Usage:**

```sh
./flightpath -s <source_airport> -d <destination_airport>
```

**Example:**

```sh
./flightpath -s JFK -d LAX
```

This will output the shortest flight path and total distance between John F. Kennedy International Airport (JFK) and Los Angeles International Airport (LAX).

## Running Tests

The project uses the [Catch2](https://github.com/catchorg/Catch2) testing framework for unit tests.

### Building the Tests

```sh
g++ -std=c++17 -I./include/ -I./external/ tests/test.cpp src/Graph.cpp src/fileio.cpp external/catch2/catch_amalgamated.cpp -o flight_test
```

### Running the Tests

```sh
./flight_test
```
