#ifndef GRAPH_H
#define GRAPH_H

#include "GraphBase.h"
#include <limits>
#include <list>
#include <map>
#include <string>
#include <tuple>
#include <vector>

/**
 * @brief Represents a graph of airports and flights.
 *
 * This class provides a graph data structure where vertices represent airports
 * and edges represent flights between them. It supports operations such as adding
 * and removing airports and flights, as well as finding the shortest path between
 * two airports using Dijkstra's algorithm.
 */
class Graph : public GraphBase {
public:
    /**
     * @brief Represents a flight between two airports.
     *
     * An Edge connects two vertices (airports) in the graph, representing a flight
     * route. It contains the destination airport's label and the distance of
     * the flight.
     */
    struct Edge {
        std::string destinationLabel;
        unsigned long distance;

        /**
         * @brief Constructs a new Edge.
         * @param dest The label of the destination airport.
         * @param dis The distance of the flight.
         */
        Edge(std::string dest, unsigned long dis)
            : destinationLabel(dest), distance(dis) {}

        /**
         * @brief Gets the label of the destination airport.
         * @return std::string The destination airport's label.
         */
        std::string getDestinationLabel() const { return destinationLabel; }

        /**
         * @brief Gets the distance of the flight.
         * @return unsigned long The flight distance.
         */
        unsigned long getDistance() const { return distance; }
    };

    /**
     * @brief Represents an airport in the graph.
     *
     * A Vertex represents an airport, uniquely identified by its label (e.g., IATA
     * code). It maintains a list of edges to other airports, representing
     * available flights.
     */
    struct Vertex {
        std::string label;
        std::list<Edge> edges;

        /**
         * @brief Constructs a new Vertex.
         * @param l The label of the airport (e.g., IATA code).
         */
        Vertex(std::string l) : label(l) {}

        /**
         * @brief Gets the label of the airport.
         * @return std::string The airport's label.
         */
        std::string getLabel() const { return label; }

        /**
         * @brief Gets the list of outgoing flights (edges) from this airport.
         * @return const std::list<Edge>& A constant reference to the list of edges.
         */
        const std::list<Edge> &getEdges() const { return edges; }
    };

private:
    std::map<std::string, Vertex *> vertices;

    /**
     * @brief Clears the graph, deallocating all vertices.
     */
    void clearGraph();

public:
    /**
     * @brief Constructs an empty Graph.
     */
    Graph();

    /**
     * @brief Destroys the Graph, freeing all allocated memory.
     */
    ~Graph();

    /**
     * @brief Adds an airport (vertex) to the graph.
     * @param label The IATA code or label for the airport.
     */
    void addVertex(std::string label) override;

    /**
     * @brief Removes an airport (vertex) from the graph.
     * @param label The IATA code or label of the airport to remove.
     */
    void removeVertex(std::string label) override;

    /**
     * @brief Adds a flight (edge) between two airports.
     * @param label1 The label of the starting airport.
     * @param label2 The label of the destination airport.
     * @param distance The distance of the flight.
     */
    void addEdge(std::string label1, std::string label2,
                 unsigned long distance) override;

    /**
     * @brief Removes a flight (edge) between two airports.
     * @param label1 The label of the starting airport.
     * @param label2 The label of the destination airport.
     */
    void removeEdge(std::string label1, std::string label2) override;

    /**
     * @brief Finds the shortest flight path between two airports using Dijkstra's algorithm.
     * @param startLabel The label of the starting airport.
     * @param endLabel The label of the destination airport.
     * @param path A vector of strings to be populated with the labels of the airports in the shortest path.
     * @return unsigned long The total distance of the shortest path. Returns std::numeric_limits<unsigned long>::max() if no path is found.
     */
    unsigned long shortestPath(std::string startLabel, std::string endLabel,
                               std::vector<std::string> &path) override;

    /**
     * @brief Gets all vertices in the graph.
     * @return const std::map<std::string, Vertex *>& A constant reference to the map of vertices.
     */
    const std::map<std::string, Vertex *> &getVertices() const {
        return vertices;
    }

    /**
     * @brief Gets all edges in the graph.
     * @return std::vector<Edge> A vector containing all edges in the graph.
     */
    std::vector<Edge> getEdges() const;
};

#endif