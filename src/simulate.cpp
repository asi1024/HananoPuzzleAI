#pragma once

#include "io.cpp"
#include "util.cpp"

int simulate(Stage st, std::ostream &os, const Records &rec) {
  st.output(os);
  for (Record r: rec) {
    bool f = st.swap(r.y, r.x);
    assert(f);
    st.output(os);
  }
  for (Record r: st.records)
    os << r.y << " " << r.x << std::endl;
  os << st.score << std::endl;
  return st.score;
}
