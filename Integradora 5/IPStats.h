#ifndef _IP_STATS_H
#define _IP_STATS_H

#include <string>

struct IPStats {
  std::string ip;
  int outgoingLinks;
  int incomingLinks;

  IPStats() {} 

  IPStats(const std::string &ipValue, int outgoingLinksValue,
          int incomingLinksValue)
      : ip(ipValue), outgoingLinks(outgoingLinksValue),
        incomingLinks(incomingLinksValue) {}

  int getOutgoingLinks() const {
    return outgoingLinks;
  }
  
  int getIncomingLinks() const {
    return incomingLinks;
  }
};

#endif // _IP_STATS_H
