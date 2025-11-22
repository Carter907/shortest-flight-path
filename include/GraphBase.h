#ifndef GRAPHBASE_H
#define GRAPHBASE_H

#include <string>
#include <vector>

class GraphBase {
public:
  virtual ~GraphBase() {} // Virtual destructor for proper cleanup

  virtual void addVertex(std::string label) = 0;

  virtual void removeVertex(std::string label) = 0;

  virtual void addEdge(std::string label1, std::string label2,
                       unsigned long distance, unsigned long actual_time,
                       unsigned long estimated_time) = 0;

  virtual void removeEdge(std::string label1, std::string label2) = 0;

  virtual unsigned long shortestPath(std::string startLabel,
                                     std::string endLabel,
                                     std::vector<std::string> &path) = 0;
};

#endif
