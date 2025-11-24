# Shortest Flight Path

This project is a C++ application that calculates the shortest flight path between two airports based on distance. It uses a graph data structure to represent airports and flight connections, and Dijkstra's algorithm to find the shortest path.

## Project Structure

The project is organized into the following directories:

```
.
├── assets/
│   ├── airports.csv
│   ├── flight-path-hypothetical-project_annotated.pdf
│   ├── FlightConnectionsJan2025.csv
│   ├── flights-test-data.csv
│   ├── Term.csv
│   └── test-case-diagram.pdf
├── include/
│   ├── cli.h
│   ├── fileio.h
│   ├── Graph.h
│   ├── GraphBase.h
│   └── PriorityQueue.h
├── src/
│   ├── cli.cpp
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

### `CLI`

The `CLI` component (defined in `include/cli.h` and implemented in `src/cli.cpp`) is responsible for handling command-line argument parsing and user interaction. It parses the source and destination airport codes from the command-line arguments.

### `main`

The `main` function (in `src/main.cpp`) orchestrates the application flow. It utilizes the `CLI` component to parse command-line arguments, loads flight data using `fileio`, calculates the shortest path using the `Graph` class, and prints the result to the console.

## Data

The application uses the following files located in the `assets` directory:

-   `airports.csv`: Contains a list of airports with their IATA codes and names, used for output result.
-   `FlightConnectionsJan2025.csv`: Contains flight connection data for January 2025, including the origin, destination, and distance of each flight.
-   `flights-test-data.csv`: A smaller dataset of flight connections, used for tests.
-   `Term.csv`: Contains terminal information for airports.
-   `flight-path-hypothetical-project_annotated.pdf`: A diagram representing a hypothetical flight path project.
-   `test-case-diagram.pdf`: A graph diagram representing mock data found in 'flights-test-data.csv', used in tests/test.cpp.

## Building and Running

To build and run the project, you can use a C++ compiler like `g++`.

### Building the Application

To compile the main executable, use the following command, which specifies the C++17 standard:

```sh
g++ -std=c++17 -I./include/ src/main.cpp src/Graph.cpp src/fileio.cpp src/cli.cpp -o flightpath
```

### Running the Application

The application requires a source airport, a destination airport, and a flight data file to calculate the shortest path.

For help, you can use the `-h` or `--help` flag:

```sh
./flightpath --help
```

**Usage:**

```sh
./flightpath -s <source_airport> -d <destination_airport> -f <flight_data_csv>
```

or with long-form arguments:

```sh
./flightpath --source <source_airport> --destination <destination_airport> --flight-data <flight_data_csv>
```

**Example:**

Using the provided test data:

```sh
./flightpath -s JFK -d LAX -f assets/flights-test-data.csv
```

This will output the shortest flight path and total distance between John F. Kennedy International Airport (JFK) and Los Angeles International Airport (LAX) based on the data in `flights-test-data.csv`.

Example Output:
```
Reading from flight data...

✈️  Shortest Flight Route ✈️

The closest route between
John F. Kennedy International Airport and Los Angeles International Airport is:

JFK -> LAX

Total distance: 385 miles
```

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
