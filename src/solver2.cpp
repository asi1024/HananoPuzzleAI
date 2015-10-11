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

int eval(const Stage &st) {
  int res = st.score;
  for (Seed s: st.seeds)
    res += s.y * (s.bloom ? 30 : 10);
  for (Block s: st.blocks)
    res += s.y * 10;
  return res;
}

Data solve(Stage st) {
  std::map<unsigned long long, int> dist;
  std::priority_queue<std::pair<int,Stage>> que;
  int cnt = 0;
  que.push(std::make_pair(eval(st), st));
  dist[st.hash()] = eval(st);
  while (!que.empty()) {
    int ev = -que.top().first;
    Stage s = que.top().second;
    que.pop();
    if (ev > dist[s.hash()]) continue;
    Stage ns = s;
    if (++cnt > 10000000) return Data(Records(), cnt);
    for (int i = 1; i < 9; ++i) {
      for (int j = 1; j < 12; ++j) {
        if (ns.swap(i, j)) {
          unsigned long long h = ns.hash();
          int nev = eval(ns);
          if (!dist.count(h) || dist[h] > nev) {
            dist[h] = nev;
            if (ns.rest == 0) return Data(ns.records, cnt);
            que.push(std::make_pair(-nev, ns));
          }
          ns = s;
        }
      }
    }
  }
  return Data(Records(), cnt);
}
