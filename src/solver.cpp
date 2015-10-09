#pragma once

#include <queue>
#include <set>
#include <utility>

#include "io.cpp"

#include "def.cpp"
#include "util.cpp"

struct Data {
  Records records;
  int count;
  Data (Records a, int b) : records(a), count(b) {}
};

Data solve(Stage st) {
  std::map<unsigned long long, int> dist;
  std::priority_queue<Stage> que;
  int cnt = 0;
  que.push(st);
  dist[st.hash()] = 0;
  while (!que.empty()) {
    Stage s = que.top();
    que.pop();
    if (s.score > dist[s.hash()]) continue;
    Stage ns = s;
    if (++cnt % 1000000 == 0)
      std::cerr << "Nodes: " << cnt << std::endl;
    for (int i = 1; i < 9; ++i) {
      for (int j = 1; j < 12; ++j) {
        if (ns.swap(i, j)) {
          unsigned long long h = ns.hash();
          if (!dist.count(h) || dist[h] > ns.score) {
            dist[h] = ns.score;
            if (ns.rest == 0) return Data(ns.records, cnt);
            que.push(ns);
          }
          ns = s;
        }
      }
    }
  }
  return Data(Records(), cnt);
}
