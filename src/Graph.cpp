#include "../include/Graph.h"
#include "../include/PriorityQueue.h"
#include <algorithm>
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
    return;
  }

  for (auto &pair : vertices) {
    Vertex *v = pair.second;
    v->edges.remove_if(
        [&label](const Edge &e) { return e.destinationLabel == label; });
  }

  delete it->second;
  vertices.erase(it);
}

void Graph::addEdge(std::string label1, std::string label2,
                    unsigned long distance) {
  auto it1 = vertices.find(label1);
  auto it2 = vertices.find(label2);

  if (it1 == vertices.end() || it2 == vertices.end()) {
    return;
  }

  if (label1 == label2) {
    return;
  }

  Vertex *v1 = it1->second;
  Vertex *v2 = it2->second;

  auto edge_it1 =
      std::find_if(v1->edges.begin(), v1->edges.end(),
                   [&](const Edge &e) { return e.destinationLabel == label2; });

  if (edge_it1 != v1->edges.end()) {
    if (distance < edge_it1->distance) {
      edge_it1->distance = distance;
    }
  } else {
    v1->edges.push_back(Edge(label2, distance));
  }

  auto edge_it2 =
      std::find_if(v2->edges.begin(), v2->edges.end(),
                   [&](const Edge &e) { return e.destinationLabel == label1; });

  if (edge_it2 != v2->edges.end()) {
    if (distance < edge_it2->distance) {
      edge_it2->distance = distance;
    }
  } else {
    v2->edges.push_back(Edge(label1, distance));
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

  v1->edges.remove_if(
      [&label2](const Edge &e) { return e.destinationLabel == label2; });

  v2->edges.remove_if(
      [&label1](const Edge &e) { return e.destinationLabel == label1; });
}

unsigned long Graph::shortestPath(std::string startLabel, std::string endLabel,
                                  std::vector<std::string> &path) {
  path.clear();

  if (vertices.find(startLabel) == vertices.end() ||
      vertices.find(endLabel) == vertices.end()) {
    return std::numeric_limits<unsigned long>::max();
  }

  std::map<std::string, unsigned long> distances;
  std::map<std::string, std::string> previous;

  for (auto const &[label, vertex] : vertices) {
    distances[label] = std::numeric_limits<unsigned long>::max();
  }

  distances[startLabel] = 0;

  PriorityQueue<DijkstraNode> pq;
  pq.push({0, startLabel});

  while (!pq.isEmpty()) {
    DijkstraNode current = pq.top();
    pq.pop();

    std::string uLabel = current.vertexLabel;
    unsigned long uDist = current.distance;

    if (uDist > distances[uLabel]) {
      continue;
    }

    if (uLabel == endLabel) {
      break;
    }

    Vertex *uVertex = vertices[uLabel];

    for (const auto &edge : uVertex->edges) {
      std::string vLabel = edge.destinationLabel;
      unsigned long distance = edge.distance;

      if (distances[uLabel] != std::numeric_limits<unsigned long>::max() &&
          distances[uLabel] + distance < distances[vLabel]) {

        distances[vLabel] = distances[uLabel] + distance;
        previous[vLabel] = uLabel;

        pq.push({distances[vLabel], vLabel});
      }
    }
  }

  if (distances[endLabel] == std::numeric_limits<unsigned long>::max()) {
    return std::numeric_limits<unsigned long>::max();
  }

  std::string curr = endLabel;
  while (curr != startLabel) {
    path.push_back(curr);
    curr = previous[curr];
  }
  path.push_back(startLabel);
  std::reverse(path.begin(), path.end());

  return distances[endLabel];
}

std::vector<Graph::Edge> Graph::getEdges() const {
  std::vector<Graph::Edge> all_edges;
  for (const auto &pair : vertices) {
    const Vertex *v = pair.second;
    for (const auto &edge : v->edges) {
      all_edges.push_back(edge);
    }
  }
  return all_edges;
}