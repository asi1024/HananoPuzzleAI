#pragma once

#include <queue>
#include <set>
#include <utility>

#include "io.cpp"

#include "def.cpp"
#include "util.cpp"

using Data = std::pair<Stage, Records>;

struct Info {
  Records records;
  int count;
  Info (Records a, int b) : records(a), count(b) {}
};

Info solve(Stage st) {
  std::set<unsigned long long> searched;
  std::queue<Data> que;
  int cnt = 0;
  que.push(std::make_pair(st, Records()));
  searched.insert(st.hash());
  while (!que.empty()) {
    ++cnt;
    if (cnt % 1000 == 0) std::cerr << "Nodes: " << cnt << std::endl;
    Stage s = que.front().first;
    Records r = que.front().second;
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
            r.push_back(Record(i, j));
            if (ns.rest == 0) return Info(r, cnt);
            que.push(make_pair(ns, r));
            r.pop_back();
          }
          ns = s;
        }
      }
    }
  }
  return Info(Records(), cnt);
}
