#pragma once

#include <string>

const std::string colors = "RBY", dirs = "RULD";

const int dx[4] = {1, 0, -1, 0};
const int dy[4] = {0, -1, 0, 1};

using Cost = int;

const Cost fall_time = 2;
const Cost swap_time = 10;
const Cost bloom_time = 35;

enum UnitT { Nothing, BoardU, SeedU, BlockU, };

struct Unit {
  UnitT unit;
  int pos;
  Unit (UnitT a, int b) : unit(a), pos(b) {}
};

struct Record {
  int y, x;
  Record (int y, int x) : y(y), x(x) {}
};

using Records = std::vector<Record>;
