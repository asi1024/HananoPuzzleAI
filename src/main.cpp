#include <bits/stdc++.h>

#include "def.cpp"
#include "io.cpp"
#include "struct.cpp"
#include "solver.cpp"
#include "simulate.cpp"

void help() {
  std::cerr << "calc : TODO" << std::endl;
  std::cerr << "eval : TODO" << std::endl;
  exit(1);
}

const int def_score = 5000;

int main (int argc, char *argv[]) {
  if (argc == 1) {
    Stage st;
    st.input(std::cin);
    st.output(std::cout);
    Data res = solve(st);
    simulate(st, std::cout, res.records);
    std::cout << res.count << std::endl;
  }
  else if (strcmp(argv[1], "calc") == 0) {
    if (argc != 2) help();
    std::vector<std::string> problems;
    std::ifstream ifs("dat/LIST");
    std::string in;
    while (ifs >> in) problems.push_back(in);
    for (std::string i: problems) {
      std::ifstream ifs(("dat/" + i + ".dat").c_str());
      if (!ifs) std::cerr << "FILE NOT EXISTS -- " <<
                  "dat/" << i << ".dat" << std::endl;
      std::ofstream ofs(("asi1024/" + i).c_str());
      Stage st;
      st.input(ifs);
      Data res = solve(st);
      for (Record r: res.records) {
        ofs << r.y << " " << r.x << std::endl;
        st.swap(r.y, r.x);
      }
      std::cerr << i << "\t" << st.score <<
        "\t(Node: " << res.count << ")" << std::endl;
      st.clear();
    }
  }
  else if (strcmp(argv[1], "eval") == 0) {
    if (argc < 3) help();
    std::string path = argv[2];
    std::vector<std::string> problems;
    if (argc == 3) {
      for (int i = 1; i <= 50; ++i) {
        std::string s = std::to_string(i);
        if ((int)s.size() == 1) s = "0" + s;
        problems.push_back(s);
      }
    }
    else {
      problems.push_back(argv[3]);
    }
    for (std::string i: problems) {
      std::ifstream ifs1(("dat/" + i + ".dat").c_str());
      std::ifstream ifs2((path + "/" + i).c_str());
      if (!ifs1 || !ifs2) {
        std::cout << def_score << std::endl;
        continue;
      }
      Stage st;
      st.input(ifs1);
      int y, x;
      for (int j = 1; ifs2 >> y >> x; ++j) {
        if (!st.swap(y, x)) {
          std::cerr << "swap error at " << j << " in stage " << i << std::endl;
          return 0;
        }
        std::cerr << y << " " << x << std::endl;
        st.output(std::cerr);
      }
      std::cout << (st.rest == 0 ? st.score : def_score) << std::endl;
    }
  }
  return 0;
}
