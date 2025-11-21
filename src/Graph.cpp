#include "Graph.hpp"
#include "PriorityQueue.hpp"
#include <algorithm>
#include <iostream>
#include <limits>

// Helper struct for Dijkstra's Priority Queue
// Must define comparison operators for the custom PriorityQueue to work
struct DijkstraNode {
  unsigned long distance;
  std::string vertexLabel;

  // Overload < operator for Min-Heap logic
  // The PriorityQueue is a Min-Heap based on value, so we want smaller distance
  // to be "smaller"
  bool operator<(const DijkstraNode &other) const {
    return distance < other.distance;
  }

  // Overload > operator because the heap implementation might use it
  bool operator>(const DijkstraNode &other) const {
    return distance > other.distance;
  }
};

Graph::Graph() {}

Graph::~Graph() { clearGraph(); }

void Graph::clearGraph() {
  for (auto &pair : vertices) {
    delete pair.second;
  }
  vertices.clear();
}

void Graph::addVertex(std::string label) {
  if (vertices.find(label) == vertices.end()) {
    vertices[label] = new Vertex(label);
  }
}

void Graph::removeVertex(std::string label) {
  auto it = vertices.find(label);
  if (it == vertices.end()) {
    return; // Vertex not found
  }

  // First, remove edges pointing TO this vertex from ALL other vertices
  // Since it's an undirected graph, if A has edge to B, B has edge to A.
  // We iterate through all vertices and remove edges pointing to 'label'.
  for (auto &pair : vertices) {
    Vertex *v = pair.second;
    // Using remove_if with a lambda to filter edges
    v->edges.remove_if(
        [&label](const Edge &e) { return e.destinationLabel == label; });
  }

  // Delete the vertex object itself
  delete it->second;
  vertices.erase(it);
}

void Graph::addEdge(std::string label1, std::string label2,
                    unsigned long distance, unsigned long actual_time,
                    unsigned long estimated_time) {
  // Check if both vertices exist
  auto it1 = vertices.find(label1);
  auto it2 = vertices.find(label2);

  if (it1 == vertices.end() || it2 == vertices.end()) {
    return; // One or both vertices do not exist
  }

  if (label1 == label2) {
    return; // Cannot have edge to itself
  }

  // Check if edge already exists to prevent duplicates
  Vertex *v1 = it1->second;
  Vertex *v2 = it2->second;

  bool exists = false;
  for (const auto &edge : v1->edges) {
    if (edge.destinationLabel == label2) {
      exists = true;
      break;
    }
  }

  if (!exists) {
    // Undirected graph: Add edge in both directions
    v1->edges.push_back(Edge(label2, distance, actual_time, estimated_time));
  }
}

void Graph::removeEdge(std::string label1, std::string label2) {
  auto it1 = vertices.find(label1);
  auto it2 = vertices.find(label2);

  if (it1 == vertices.end() || it2 == vertices.end()) {
    return;
  }

  Vertex *v1 = it1->second;
  Vertex *v2 = it2->second;

  // Remove edge from v1's list
  v1->edges.remove_if(
      [&label2](const Edge &e) { return e.destinationLabel == label2; });
}

unsigned long Graph::shortestPath(std::string startLabel, std::string endLabel,
                                  std::vector<std::string> &path) {
  path.clear();

  // Check if vertices exist
  if (vertices.find(startLabel) == vertices.end() ||
      vertices.find(endLabel) == vertices.end()) {
    return std::numeric_limits<unsigned long>::max(); // Error or unreachable
  }

  // Initialize distances to infinity
  std::map<std::string, unsigned long> distances;
  std::map<std::string, std::string> previous; // To reconstruct path

  for (auto const &[label, vertex] : vertices) {
    distances[label] = std::numeric_limits<unsigned long>::max();
  }

  distances[startLabel] = 0;

  // Custom Priority Queue
  PriorityQueue<DijkstraNode> pq;
  pq.push({0, startLabel});

  while (!pq.isEmpty()) {
    DijkstraNode current = pq.top();
    pq.pop();

    std::string uLabel = current.vertexLabel;
    unsigned long uDist = current.distance;

    // Optimization: If current distance is greater than already found shortest
    // distance, skip
    if (uDist > distances[uLabel]) {
      continue;
    }

    // If we reached the destination, we can stop (optional optimization)
    if (uLabel == endLabel) {
      break;
    }

    Vertex *uVertex = vertices[uLabel];

    // Iterate neighbors
    for (const auto &edge : uVertex->edges) {
      std::string vLabel = edge.destinationLabel;
      unsigned long distance = edge.distance;

      // Relaxation step
      if (distances[uLabel] != std::numeric_limits<unsigned long>::max() &&
          distances[uLabel] + distance < distances[vLabel]) {

        distances[vLabel] = distances[uLabel] + distance;
        previous[vLabel] = uLabel;

        pq.push({distances[vLabel], vLabel});
      }
    }
  }

  // Check if path exists
  if (distances[endLabel] == std::numeric_limits<unsigned long>::max()) {
    return std::numeric_limits<unsigned long>::max(); // Path not found
  }

  // Reconstruct path
  std::string curr = endLabel;
  while (curr != startLabel) {
    path.push_back(curr);
    curr = previous[curr];
  }
  path.push_back(startLabel);
  std::reverse(path.begin(), path.end());

  return distances[endLabel];
}
