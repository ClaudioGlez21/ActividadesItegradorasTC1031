// Esta clase permite representar grafos dirigidos ponderados
#ifndef _GRAPH_H_
#define _GRAPH_H_

#include "LinkedList.h"
#include "QueueLinkedList.h"

#include <algorithm>
#include <climits>
#include <fstream>
#include <iostream>
#include <limits>
#include <map>
#include <queue>
#include <sstream>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

#define INF 0x3f3f3f3f

class Graph {
private:
  int numNodes;
  int numEdges;

  std::map<int, LinkedList<std::pair<int, int>>> adjList;
  std::map<int, std::string> nodeToIP;
  std::map<std::string, int> ipToNode;
  void split(std::string line, std::vector<int> &res);

public:
  Graph();
  ~Graph();

  void lectura(const std::string &filename);
  void grados();
  void topGrados();
  int findBootMasterNode();
  std::string findBootMasterIP();
  std::string getNodeIP(int node) const;
  void dijkstraAlgorithm(int bootMasterNode);
  std::string getLeastEffortIP(int bootMasterNode);
};

#endif // __GRAPH_H_