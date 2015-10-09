#include <bits/stdc++.h>

#include "def.cpp"
#include "io.cpp"
#include "struct.cpp"
#include "solver.cpp"
#include "simulate.cpp"

int main (int argc, char *argv[]) {
  Stage st;
  st.input(std::cin);
  st.output(std::cout);
  Data res = solve(st);
  /*
  rec.clear();
  rec.push_back(Record(4, 3));
  rec.push_back(Record(8, 7));
  rec.push_back(Record(8, 6));
  rec.push_back(Record(8, 5));
  rec.push_back(Record(4, 4));
  rec.push_back(Record(4, 3));
  rec.push_back(Record(4, 4));
  rec.push_back(Record(5, 5));
  rec.push_back(Record(5, 6));
  rec.push_back(Record(6, 4));
  rec.push_back(Record(7, 3));
  rec.push_back(Record(8, 5));
  rec.push_back(Record(8, 6));
  rec.push_back(Record(8, 7));
  rec.push_back(Record(8, 8));
  rec.push_back(Record(7, 3));
  rec.push_back(Record(7, 4));
  rec.push_back(Record(8, 5));
  rec.push_back(Record(8, 6));
  rec.push_back(Record(8, 7));
  rec.push_back(Record(5, 7));
  rec.push_back(Record(6, 8));
  rec.push_back(Record(6, 9));
  rec.push_back(Record(7, 10));
  */
  /*
  Records rec;
  rec.clear();
  rec.push_back(Record(7, 10));
  rec.push_back(Record(4, 7));
  Data res = Data(rec, 0);
  */

  simulate(st, std::cout, res.records);
  std::cout << "Nodes: " << res.count << std::endl;
  st.clear();
  return 0;
}
