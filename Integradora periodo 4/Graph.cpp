#include "Graph.h"

Graph::Graph() { adjList.clear(); }

Graph::~Graph() { adjList.clear(); }

void Graph::split(std::string line, std::vector<int> &res) {
  size_t strPos = line.find(" ");
  size_t lastPos = 0;
  while (strPos != std::string::npos) {
    res.push_back(stoi(line.substr(lastPos, strPos - lastPos)));
    lastPos = strPos + 1;
    strPos = line.find(" ", lastPos);
  }
  res.push_back(stoi(line.substr(lastPos, line.size() - lastPos)));
}

// Complejidad computacional: O(1)
std::string Graph::getNodeIP(int node) const {
  auto it = nodeToIP.find(node);
  if (it != nodeToIP.end()) {
    return it->second;
  }
  return "";
}

//Complejidad computacional: O(n)
void Graph::lectura(const std::string &filename) {
  std::ifstream inputFile(filename);
  if (!inputFile) {
    std::cout << "Failed to open the file: " << filename << std::endl;
    return;
  }

  int numIPs;
  inputFile >> numIPs;
  inputFile.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

  std::vector<std::string> ips(numIPs);
  std::map<std::string, int> ipToNode; 
  int nodeCounter = 1; 

  for (int i = 0; i < numIPs; ++i) {
    std::getline(inputFile, ips[i]);
    std::size_t pos = ips[i].find(':');
    if (pos != std::string::npos) {
      ips[i] = ips[i].substr(0, pos);
    }
    ipToNode[ips[i]] =
        nodeCounter;
    ++nodeCounter;
  }

  // Update nodeToIP map with IP-to-node mapping
  for (const auto &entry : ipToNode) {
    nodeToIP[entry.second] = entry.first;
  }

  std::string line;
  while (std::getline(inputFile, line)) {
    std::istringstream iss(line);
    std::string month, day, time, srcIP, destIP;
    int weight;
    std::string reason;

    iss >> month >> day >> time >> srcIP >> destIP >> weight;
    // Remove the port from the IP addresses
    std::size_t srcPos = srcIP.find(':');
    if (srcPos != std::string::npos) {
      srcIP = srcIP.substr(0, srcPos);
    }
    std::size_t destPos = destIP.find(':');
    if (destPos != std::string::npos) {
      destIP = destIP.substr(0, destPos);
    }

    int srcNode = ipToNode[srcIP];
    int destNode = ipToNode[destIP];
    std::pair<int, int> incident(destNode, weight);
    adjList[srcNode].addLast(incident);
  }

  inputFile.close();
}

//Complejidad computacional: O(n)
// Referencias para el desarrollo del método
// https://www.geeksforgeeks.org/depth-first-search-or-dfs-for-a-graph/
// https://www.geeksforgeeks.org/print-nodes-having-maximum-and-minimum-degrees/
void Graph::grados() {
  std::ofstream outputFile("grados_ips.txt");
  if (!outputFile) {
    std::cout << "Failed to open the file: grados_ips.txt" << std::endl;
    return;
  }

  for (const auto &entry : adjList) {
    int node = entry.first;
    const LinkedList<std::pair<int, int>> &incidents = entry.second;
    int outDegree = incidents.getNumElements();

    std::string ip = nodeToIP[node];

    outputFile << "IP: " << ip << " - " << outDegree << std::endl;
  }

  outputFile.close();
}

//Complejidad computacional: O(n log n)
void Graph::topGrados() {
  std::vector<std::pair<int, int>> outDegrees;

  for (const auto &entry : adjList) {
    int node = entry.first;
    const LinkedList<std::pair<int, int>> &incidents = entry.second;
    int outDegree = incidents.getNumElements();

    std::string ip = nodeToIP[node];

    outDegrees.push_back(std::make_pair(node, outDegree));
  }

  std::sort(outDegrees.begin(), outDegrees.end(),
            [](const std::pair<int, int> &a, const std::pair<int, int> &b) {
              return a.second > b.second;
            });

  std::ofstream outputFile("mayores_grados_ips.txt");
  if (!outputFile) {
    std::cout << "Failed to open the file: mayores_grados_ips.txt" << std::endl;
    return;
  }

  for (int i = 0; i < 5 && i < outDegrees.size(); ++i) {
    int node = outDegrees[i].first;
    std::string ip = nodeToIP[node]; // Get the IP corresponding to the node

    outputFile << "IP: " << ip << " - " << outDegrees[i].second << std::endl;
  }

  outputFile.close();
}

//Complejidad computacional: O(n)
// Referencias para la implementacion del metodo:
//https://www.geeksforgeeks.org/extracting-ip-address-from-a-given-string-using-regular-expressions/
std::string Graph::findBootMasterIP() {
  int bootMasterNode = -1;
  int maxOutDegree = std::numeric_limits<int>::min();

  for (const auto &entry : adjList) {
    int node = entry.first;
    const LinkedList<std::pair<int, int>> &incidents = entry.second;
    int outDegree = incidents.getNumElements();

    if (outDegree > maxOutDegree) {
      maxOutDegree = outDegree;
      bootMasterNode = node;
    }
  }

  // Retrieve the IP address of the boot master node
  if (bootMasterNode != -1) {
    return nodeToIP[bootMasterNode];
  } else {
    return ""; // Return an empty string if boot master not found
  }
}

// Referencias para la implementacion del metodo:
//https://www.geeksforgeeks.org/extracting-ip-address-from-a-given-string-using-regular-expressions/
//Complejidad computacional: O(n)
int Graph::findBootMasterNode() {
  int bootMasterNode = -1;
  int maxOutDegree = std::numeric_limits<int>::min();

  for (const auto &entry : adjList) {
    int node = entry.first;
    const LinkedList<std::pair<int, int>> &incidents = entry.second;
    int outDegree = incidents.getNumElements();

    if (outDegree > maxOutDegree) {
      maxOutDegree = outDegree;
      bootMasterNode = node;
    }
  }

  return bootMasterNode;
}

// Referencias para la implementacion del metodo:
//https://www.geeksforgeeks.org/c-program-for-dijkstras-shortest-path-algorithm-greedy-algo-7/
//Complejidad computacional: O((n + m) log n)
void Graph::dijkstraAlgorithm(int bootMasterNode) {
  std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>, std::greater<std::pair<int, int>>> pq;

  std::map<int, int> distances;

  for (const auto& entry : adjList) {
    int node = entry.first;
    if (node == bootMasterNode)
      distances[node] = 0;
    else
      distances[node] = INF;
  }

  pq.push(std::make_pair(0, bootMasterNode));

  while (!pq.empty()) {
    int nodeU = pq.top().second;
    pq.pop();

    const LinkedList<std::pair<int, int>>& neighbors = adjList[nodeU];

    NodeLinkedList<std::pair<int, int>>* ptr = neighbors.getHead();
    while (ptr != nullptr) {
      int nodeV = ptr->data.first; 
      int weight = ptr->data.second;  

      int newDistance = distances[nodeU] + weight;

      if (newDistance < distances[nodeV]) {
        distances[nodeV] = newDistance;
        pq.push(std::make_pair(newDistance, nodeV));
      }

      ptr = ptr->next;
    }
  }

  std::ofstream outputFile("distancia_bootmaster.txt");
  if (outputFile.is_open()) {
    for (const auto& entry : distances) {
      int node = entry.first;
      int distance = entry.second;
      std::string ip = getNodeIP(node);
      outputFile << ip << " " << distance << std::endl;
    }
    outputFile.close();
  } else {
    std::cout << "Unable to open the output file." << std::endl;
  }
}


// Referencia para la implemntación del metodo
// https://stackoverflow.com/questions/42100055/stdpriority-queue-with-stdpairint-int
//Complejidad computacional: O((n+m) log n)
std::string Graph::getLeastEffortIP(int bootMasterNode) {
  std::string leastEffortIP;

  std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>, std::greater<std::pair<int, int>>> pq;

  std::map<int, int> distances;

  for (const auto& entry : adjList) {
    int node = entry.first;
    if (node == bootMasterNode)
      distances[node] = 0;
    else
      distances[node] = INF;
  }

  pq.push(std::make_pair(0, bootMasterNode));

  while (!pq.empty()) {
    int nodeU = pq.top().second;
    pq.pop();

    const LinkedList<std::pair<int, int>>& neighbors = adjList[nodeU];

    NodeLinkedList<std::pair<int, int>>* ptr = neighbors.getHead();
    while (ptr != nullptr) {
      int nodeV = ptr->data.first;  
      int weight = ptr->data.second; 

      int newDistance = distances[nodeU] + weight;

      if (newDistance < distances[nodeV]) {
        distances[nodeV] = newDistance;
        pq.push(std::make_pair(newDistance, nodeV));
      }

      ptr = ptr->next;
    }
  }

  int minDistance = INF;
  for (const auto& entry : distances) {
    int node = entry.first;
    int distance = entry.second;
    if (distance < minDistance) {
      minDistance = distance;
      leastEffortIP = getNodeIP(node);
    }
  }

  return leastEffortIP;
}