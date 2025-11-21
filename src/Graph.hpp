#ifndef GRAPH_H
#define GRAPH_H

#include "GraphBase.hpp"
#include <limits>
#include <list>
#include <map>
#include <string>
#include <tuple>
#include <vector>

class Graph : public GraphBase {
private:
  // Internal helper structures
  // MUST be defined BEFORE usage in the map so the compiler knows the correct
  // type
  struct Edge {
    std::string destinationLabel; // The label of the vertex this edge points to
    unsigned long distance;
    unsigned long actual_time;
    unsigned long estimated_time;

    Edge(std::string dest, unsigned long dis, unsigned long at,
         unsigned long est)
        : destinationLabel(dest), distance(dis), actual_time(at),
          estimated_time(est) {}
  };

  struct Vertex {
    std::string label;
    std::list<Edge> edges; // List of edges connecting to other vertices

    Vertex(std::string l) : label(l) {}
  };

  // Adjacency list: Map label to Vertex pointer for O(1) or O(log n) access
  // Now 'Vertex*' correctly refers to the struct defined above
  std::map<std::string, Vertex *> vertices;

  // Helper to help clean up memory
  void clearGraph();

public:
  Graph();
  ~Graph(); // Destructor required by instructions

  void addVertex(std::string label) override;
  void removeVertex(std::string label) override;
  void addEdge(std::string label1, std::string label2, unsigned long distance,
               unsigned long actual_time,
               unsigned long estimated_time) override;
  void removeEdge(std::string label1, std::string label2) override;
  unsigned long shortestPath(std::string startLabel, std::string endLabel,
                             std::vector<std::string> &path) override;
};

#endif
