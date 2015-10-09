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
  std::set<unsigned long long> searched;
  std::queue<Stage> que;
  int cnt = 0;
  que.push(st);
  searched.insert(st.hash());
  while (!que.empty()) {
    ++cnt;
    if (cnt % 100000 == 0) std::cerr << "Nodes: " << cnt << std::endl;
    Stage s = que.front();
    //s.output(std::cout);
    //for (Record x: r) std::cout << "(" << x.y << ", " << x.x << ") ";
    //std::cout << std::endl;
    Stage ns = s;
    que.pop();
    for (int i = 1; i < 9; ++i) {
      for (int j = 1; j < 12; ++j) {
        if (ns.swap(i, j)) {
          unsigned long long h = ns.hash();
          if (!searched.count(h)) {
            searched.insert(h);
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
