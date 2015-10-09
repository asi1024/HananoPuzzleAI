#pragma once

#include "def.cpp"
#include "struct.cpp"

void Stage::input (std::istream &is) {
  int H, W;
  is >> H >> W;
  for (int i = 0; i < H; ++i) {
    std::string s;
    is >> s;
    assert ((int)s.size() == W);
    for (char c: s)
      assert (c == 'Y' || c == 'R' || c == 'B' || c == '#' || c == '.');
    board->push_back(s);
  }
  std::string type;
  while (is >> type) {
    assert (type == "S" || type == "B");
    if (type == "S") {
      std::string color, dir, y, x;
      is >> color >> dir >> y >> x;
      seeds.push_back(Seed(color, dir, stoi(y), stoi(x)));
    }
    else {
      std::string y, x, h, w;
      is >> y >> x >> h >> w;
      blocks.push_back(Block(stoi(y), stoi(x), stoi(h), stoi(w)));
    }
  }
  rest = seeds.size();
}

void Stage::output (std::ostream& os) const {
  std::vector<std::string> b = *(board);
  for (Seed s: seeds) {
    b[s.y][s.x] = (char)('0' + s.color);
    if (s.bloom) b[s.y + dy[s.dir]][s.x + dx[s.dir]] = (char)('0' + s.color);
  }
  for (Block s: blocks) {
    for (int i = 0; i < s.h; ++i)
      for (int j = 0; j < s.w; ++j)
        b[s.y + i][s.x + j] = 'x';
  }
  for (std::string s: b)
    os << s << std::endl;
}
