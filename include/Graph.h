#ifndef GRAPH_H
#define GRAPH_H

#include "GraphBase.h"
#include <limits>
#include <list>
#include <map>
#include <string>
#include <tuple>
#include <vector>

class Graph : public GraphBase {
public:
  // Public nested structs for Vertex and Edge
  struct Edge {
    std::string destinationLabel;
    unsigned long distance;

    Edge(std::string dest, unsigned long dis)
        : destinationLabel(dest), distance(dis) {}

    // Accessor functions for Edge
    std::string getDestinationLabel() const { return destinationLabel; }
    unsigned long getDistance() const { return distance; }
  };

  struct Vertex {
    std::string label;
    std::list<Edge> edges;

    Vertex(std::string l) : label(l) {}

    // Accessor functions for Vertex
    std::string getLabel() const { return label; }
    const std::list<Edge> &getEdges() const { return edges; }
  };

private:
  std::map<std::string, Vertex *> vertices;
  void clearGraph();

public:
  Graph();
  ~Graph(); // Destructor required by instructions

  void addVertex(std::string label) override;
  void removeVertex(std::string label) override;
  void addEdge(std::string label1, std::string label2,
               unsigned long distance) override;
  void removeEdge(std::string label1, std::string label2) override;
  unsigned long shortestPath(std::string startLabel, std::string endLabel,
                             std::vector<std::string> &path) override;

  // Accessor functions for Graph
  const std::map<std::string, Vertex *> &getVertices() const {
    return vertices;
  }
  std::vector<Edge> getEdges() const;
};

#endif
