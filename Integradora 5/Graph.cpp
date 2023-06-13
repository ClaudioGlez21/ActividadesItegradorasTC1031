#include "Graph.h"

#include "HashTable.h"

Graph::Graph() { adjList.clear(); }

Graph::~Graph() { adjList.clear(); }

//Complejidad: O(n)
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

std::string Graph::getNodeIP(int node) const {
  auto it = nodeToIP.find(node);
  if (it != nodeToIP.end()) {
    return it->second;
  }
  return "";
}

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
    ipToNode[ips[i]] = nodeCounter;
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
    std::pair<int, int> outgoingIncident(destNode, weight);
    std::pair<int, int> incomingIncident(srcNode, weight);
    adjList[srcNode].addLast(outgoingIncident);
    adjList[destNode].addLast(incomingIncident); // Add incoming edge

  }

  inputFile.close();
}

// Complejidad O(n^2)
// Referencia: https://www.geeksforgeeks.org/graph-representations-using-set-hash/
void Graph::buildHashTable(HashTable<std::string, IPStats> &ipTable) {
  int numIPs = nodeToIP.size();
  int hashSize = numIPs * 2;
  ipTable.setMaxSize(hashSize);

  // Initialize incoming links count for each IP to 0
  std::map<std::string, int> incomingLinksCount;
  for (const auto &entry : nodeToIP) {
    incomingLinksCount[entry.second] = 0;
  }

  for (const auto &entry : adjList) {
    int srcNode = entry.first;
    const LinkedList<std::pair<int, int>> &incidents = entry.second;

    std::string srcIP = getNodeIP(srcNode);
    int outgoingLinks =
        incidents
            .getNumElements(); // Number of outgoing links from the source IP
    int incomingLinks = 0;     // Number of incoming links to the source IP

    NodeLinkedList<std::pair<int, int>> *current = incidents.getHead();
    while (current != nullptr) {
      std::pair<int, int> incident = current->getData();
      int destNode = incident.first;
      std::string destIP = getNodeIP(destNode);

      if (destIP != srcIP) {
        // Check if the destination IP is different from the source IP
        // Increment the incoming links count for the destination IP
        incomingLinksCount[destIP]++;
      }

      current = current->getNext();
    }

    // Get the incoming links count for the source IP
    incomingLinks = incomingLinksCount[srcIP];

    IPStats ipStats(srcIP, outgoingLinks, incomingLinks);
    ipTable.add(srcIP, ipStats);
  }
}

// Complejidad O(n log n)
void Graph::getIPSummary(const std::string &ip, HashTable<std::string, IPStats> &ipTable) {
  int index = ipTable.find(ip);
  if (index != -1) {
    std::cout << "IP Summary for " << ip << ":" << std::endl;

    // Retrieve IPStats from the HashTable
    IPStats ipStats = ipTable.getDataAt(index);
    int outgoingLinks = ipStats.getOutgoingLinks();
    int incomingLinks = ipStats.getIncomingLinks();

    std::cout << "Outgoing Links: " << outgoingLinks << std::endl;
    std::cout << "Incoming Links: " << incomingLinks << std::endl;

    std::cout << "IPs accessed from " << ip
              << " (in descending order):" << std::endl;

    // Create a vector to store accessed IPs
    std::vector<std::string> accessedIPs;

    // Iterate through the adjacency list
    for (const auto &entry : adjList) {
      int srcNode = entry.first;
      const LinkedList<std::pair<int, int>> &incidents = entry.second;

      std::string srcIP = nodeToIP[srcNode];

      // Iterate through the incidents of each node
      NodeLinkedList<std::pair<int, int>> *current = incidents.getHead();
      while (current != nullptr) {
        std::pair<int, int> incident = current->getData();
        int destNode = incident.first;
        std::string destIP = nodeToIP[destNode];

        if (srcIP == ip) {
          accessedIPs.push_back(destIP);
        }

        current = current->getNext();
      }
    }

    // Sort accessed IPs in descending order
    std::sort(accessedIPs.begin(), accessedIPs.end(),
              std::greater<std::string>());

    // Print accessed IPs
    for (const auto &accessedIP : accessedIPs) {
      std::cout << accessedIP << std::endl;
    }
  } else {
    std::cout << "IP not found" << std::endl;
  }
}
