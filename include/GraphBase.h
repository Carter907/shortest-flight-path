#ifndef GRAPHBASE_H
#define GRAPHBASE_H

#include <string>
#include <vector>

/**
 * @brief An abstract base class defining the interface for a graph data structure.
 *
 * This class provides a set of pure virtual functions that must be implemented by
 * any concrete graph class that inherits from it. It establishes a contract for
 * basic graph operations such as adding/removing vertices and edges, and for
 * pathfinding algorithms. This allows for different graph implementations to be
 * used interchangeably.
 */
class GraphBase {
public:
    /**
     * @brief Virtual destructor for the GraphBase class.
     *
     * Ensures that the destructors of derived classes are called correctly when
     * an object is deleted through a pointer to the base class.
     */
    virtual ~GraphBase() {}

    /**
     * @brief Adds a vertex to the graph.
     *
     * This is a pure virtual function that must be implemented by derived classes.
     * It is intended to add a new vertex, identified by a unique label, to the graph.
     *
     * @param label A string representing the unique label of the vertex to be added.
     */
    virtual void addVertex(std::string label) = 0;

    /**
     * @brief Removes a vertex from the graph.
     *
     * This is a pure virtual function for removing a vertex, specified by its label,
     * from the graph. Any edges connected to this vertex should also be removed.
     *
     * @param label The label of the vertex to be removed.
     */
    virtual void removeVertex(std::string label) = 0;

    /**
     * @brief Adds a directed edge between two vertices.
     *
     * This pure virtual function is for adding an edge from a source vertex to a
     * destination vertex. The edge has a weight, which represents the distance
     * or cost of traversing it.
     *
     * @param label1 The label of the source vertex.
     * @param label2 The label of the destination vertex.
     * @param distance The weight or distance of the edge.
     */
    virtual void addEdge(std::string label1, std::string label2,
                         unsigned long distance) = 0;

    /**
     * @brief Removes the edge between two vertices.
     *
     * A pure virtual function for removing the edge from a source vertex to a
     * destination vertex.
     *
     * @param label1 The label of the source vertex.
     * @param label2 The label of the destination vertex.
     */
    virtual void removeEdge(std::string label1, std::string label2) = 0;

    /**
     * @brief Finds the shortest path between two vertices.
     *
     * This pure virtual function should implement an algorithm to find the shortest
     * path from a starting vertex to an ending vertex. The path is returned as a
     * vector of vertex labels, and the total distance of the path is returned.
     *
     * @param startLabel The label of the starting vertex.
     * @param endLabel The label of the ending vertex.
     * @param path A reference to a vector of strings, which will be populated with
     *             the labels of the vertices in the shortest path.
     * @return unsigned long The total distance of the shortest path. If no path
     *                     is found, this should return a value indicating that,
     *                     such as the maximum possible unsigned long.
     */
    virtual unsigned long shortestPath(std::string startLabel,
                                       std::string endLabel,
                                       std::vector<std::string> &path) = 0;
};

#endif