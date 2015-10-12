#pragma once

#include <iostream>
#include <vector>
#include <string>

#include "def.cpp"

struct Seed {
  int y, x, dir, color;
  bool bloom;
  Seed (std::string a, std::string b, int c, int d) : y(c), x(d), bloom(false) {
    color = colors.find(a);
    dir = dirs.find(b);
    assert (color != (int)std::string::npos && dir != (int)std::string::npos);
  }
  bool operator < (const Seed &rhs) const {
    return y == rhs.y ? x < rhs.x : y > rhs.y;
  }
};

struct Block {
  int y, x, h, w;
  Block (int a, int b, int c, int d) : y(a), x(b), h(c), w(d) {}
  bool operator < (const Block &rhs) const {
    return y == rhs.y ? x < rhs.x : y < rhs.y;
  }
};

struct Stage {
  int score, rest;
  std::vector<std::string> *board;
  std::vector<Seed> seeds;
  std::vector<Block> blocks;
  Records records;
  Stage () : score(0), rest(0) { board = new std::vector<std::string>; }
  void clear () { delete board; }
  void input (std::istream&);
  void output (std::ostream&) const;
  Unit at (int, int) const;
  int under (Unit) const;
  int width (Unit) const;
  int height (Unit) const;
  void force_move (Unit, int, int);
  bool can_move (Unit, int) const;
  void move (Unit, int);
  int can_bloom (const Seed&) const;
  void bloom (Seed&, int);
  void fall();
  bool swap (int, int);
  unsigned long long hash();
  bool operator < (const Stage &rhs) const { return score > rhs.score; }
};
