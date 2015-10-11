#pragma once

#include "def.cpp"
#include "struct.cpp"

Unit Stage::at (int y, int x) const {
  char c = (*board)[y][x];
  if (c != '.') {
    if (c == '#') return Unit(BoardU, -1);
    return Unit(BoardU, colors.find(std::string(1, c)));
  }
  for (auto it = seeds.begin(); it != seeds.end(); ++it) {
    if ((y == it->y && x == it->x) ||
        (it->bloom && y == it->y + dy[it->dir] && x == it->x + dx[it->dir]))
      return Unit(SeedU, it - seeds.begin());
  }
  for (auto it = blocks.begin(); it != blocks.end(); ++it) {
    if (it->y <= y && y < it->y + it->h && it->x <= x && x < it->x + it->w)
      return Unit(BlockU, it - blocks.begin());
  }
  return Unit(Nothing, 0);
}

int Stage::under(Unit u) const {
  if (u.unit == BlockU) {
    Block s = blocks[u.pos];
    return s.y + s.h - 1;
  }
  else if (u.unit == SeedU) {
    Seed s = seeds[u.pos];
    return s.y + (s.bloom && s.dir == 3);
  }
  else return -1;
}

int Stage::width (Unit u) const {
  if (u.unit == Nothing) return 0;
  else if (u.unit == BoardU) return 0;
  else if (u.unit == SeedU) {
    Seed s = seeds[u.pos];
    return (!s.bloom || s.dir % 2 == 1) ? 1 : 2;
  }
  else {
    Block s = blocks[u.pos];
    return s.w;
  }
}
int Stage::height (Unit u) const {
  if (u.unit == Nothing) return 0;
  else if (u.unit == BoardU) return 0;
  else if (u.unit == SeedU) {
    Seed s = seeds[u.pos];
    return (!s.bloom || s.dir % 2 == 0) ? 1 : 2;
  }
  else {
    Block s = blocks[u.pos];
    return s.h;
  }
}

void Stage::force_move (Unit u, int dy, int dx) {
  if (u.unit == SeedU) {
    seeds[u.pos].y += dy;
    seeds[u.pos].x += dx;
  }
  else if (u.unit == BlockU) {
    blocks[u.pos].y += dy;
    blocks[u.pos].x += dx;
  }
}

bool Stage::can_move (Unit u, int dir) const {
  if (u.unit == Nothing) return true;
  if (u.unit == BoardU) return false;
  if (u.unit == SeedU) {
    Seed s = seeds[u.pos];
    int y = s.y, x = s.x, d = s.dir;
    if (!s.bloom) return can_move(at(y + dy[dir], x + dx[dir]), dir);
    if (dir == d) return can_move(at(y + dy[dir]*2, x + dx[dir]*2), dir);
    if ((dir + 2) % 4 == d) return can_move(at(y + dy[dir], x + dx[dir]), dir);
    return can_move(at(y + dy[dir], x + dx[dir]), dir)
      && can_move(at(y + dy[d] + dy[dir], x + dx[d] + dx[dir]), dir);
  }
  Block s = blocks[u.pos];
  int y = s.y, x = s.x, h = s.h, w = s.w;
  if (dir == 0) {
    for (int i = 0; i < h; ++i)
      if (!can_move(at(y + i, x + w), dir)) return false;
    return true;
  }
  if (dir == 1) {
    for (int i = 0; i < w; ++i)
      if (!can_move(at(y - 1, x + i), dir)) return false;
    return true;
  }
  if (dir == 2) {
    for (int i = 0; i < h; ++i)
      if (!can_move(at(y + i, x - 1), dir)) return false;
    return true;
  }
  if (dir == 3) {
    for (int i = 0; i < w; ++i)
      if (!can_move(at(y + h, x + i), dir)) return false;
    return true;
  }
  return false;
}

void Stage::move (Unit u, int dir) {
  if (u.unit == Nothing) return;
  if (u.unit == SeedU) {
    Seed &s = seeds[u.pos];
    int y = s.y, x = s.x, d = s.dir;
    //std::cout << y << " " << x << " " << u.pos << std::endl;
    if (!s.bloom) move(at(y + dy[dir], x + dx[dir]), dir);
    else if (dir == d) move(at(y + dy[dir]*2, x + dx[dir]*2), dir);
    else if ((dir + 2) % 4 == d) move(at(y + dy[dir], x + dx[dir]), dir);
    else {
      move(at(y + dy[dir], x + dx[dir]), dir);
      move(at(y + dy[d] + dy[dir], x + dx[d] + dx[dir]), dir);
    }
    s.y += dy[dir]; s.x += dx[dir];
    return;
  }
  assert (u.unit != BoardU);
  Block &s = blocks[u.pos];
  int y = s.y, x = s.x, h = s.h, w = s.w;
  if (dir == 0)
    for (int i = 0; i < h; ++i) move(at(y + i, x + w), dir);
  else if (dir == 1)
    for (int i = 0; i < w; ++i) move(at(y - 1, x + i), dir);
  else if (dir == 2)
    for (int i = 0; i < h; ++i) move(at(y + i, x - 1), dir);
  else if (dir == 3)
    for (int i = 0; i < w; ++i) move(at(y + h, x + i), dir);
  s.y += dy[dir]; s.x += dx[dir];
}

int Stage::can_bloom (const Seed &s) const {
  bool flag = false;
  for (int dir = 0; dir < 4; ++dir) {
    int y = s.y + dy[dir], x = s.x + dx[dir];
    Unit u = at(y, x);
    if (u.unit == BoardU && u.pos == s.color) { flag = true; break; }
    if (u.unit == SeedU) {
      Seed s2 = seeds[u.pos];
      if (s2.bloom && s.color == s2.color && (s2.y != y || s2.x != x)) {
        flag = true; break;
      }
    }
  }
  if (!flag) return 0;
  if (can_move(at(s.y + dy[s.dir], s.x + dx[s.dir]), s.dir)) return 1;
  if (can_move(at(s.y - dy[s.dir], s.x - dx[s.dir]), (s.dir + 2) % 4)) return 2;
  return 0;
}

void Stage::bloom (Seed &s, int sw) {
  if (sw == 1) {
    move(at(s.y + dy[s.dir], s.x + dx[s.dir]), s.dir);
  }
  else {
    move(at(s.y - dy[s.dir], s.x - dx[s.dir]), (s.dir + 2) % 4);
    force_move(at(s.y, s.x), -dy[s.dir], -dx[s.dir]);
  }
  s.bloom = true;
  --rest;
}

void Stage::fall () {
  for (;;) {
    std::vector<Unit> us;
    for (int i = 0; i < (int)seeds.size(); ++i) {
      if (can_move(Unit(SeedU, i), 3))
        us.push_back(Unit(SeedU, i));
    }
    for (int i = 0; i < (int)blocks.size(); ++i) {
      if (can_move(Unit(BlockU, i), 3))
        us.push_back(Unit(BlockU, i));
    }
    if (us.empty()) break;
    score += fall_time;
    for (Unit u: us) force_move(u, 1, 0);
  }   
}

bool Stage::swap (int y, int x) {
  if (y < 0 || y + 1 >= (int)board->size() ||
      x < 0 || x + 1 >= (int)(*board)[0].size())
    return false;
  Unit u1 = at(y, x), u2 = at(y, x+1);
  if (u1.unit == Nothing && u2.unit == Nothing) return false;
  if (u1.unit == BoardU || u2.unit == BoardU) return false;
  int h1 = height(u1), h2 = height(u2);
  int h = std::max(h1, h2);
  int t1 = under(u1), t2 = under(u2);
  //std::cout << t1 << " " << t2 << std::endl;
  //std::cout << h1 << " " << h2 << std::endl;
  if (u1.unit == Nothing) {
    for (int i = 0; i < h; ++i)
      if (at(t2-i, x).unit != Nothing) return false;
    force_move(u2, 0, -1);
  }
  else if (u2.unit == Nothing) {
    for (int i = 0; i < h; ++i)
      if (at(t1-i, x+1).unit != Nothing) return false;
    force_move(u1, 0, 1);
  }
  else {
    if (t1 != t2) return false;
    if (width(u1) != 1) return false;
    if (width(u2) != 1) return false;
    for (int i = h2; i < h; ++i)
      if (at(t2-i, x+1).unit != Nothing) return false;
    for (int i = h1; i < h; ++i)
      if (at(t1-i, x).unit != Nothing) return false;
    force_move(u1, 0, 1); force_move(u2, 0, -1);
  }

  score += swap_time;
  for (;;) {
    fall();
    bool flag = true;
    for (Seed &s: seeds) {
      if (!s.bloom) {
        int sw = can_bloom(s);
        if (sw != 0) { bloom(s, sw); flag = false; }
      }
    }
    if (flag) break;
    score += bloom_time;
  }
  records.push_back(Record(y, x));
  return true;
}

unsigned long long Stage::hash () {
  sort(begin(seeds), end(seeds));
  sort(begin(blocks), end(blocks));
  unsigned long long res = 78655989;
  for (Seed s: seeds) {
    res = res * 12345 + s.y + 138;
    res = res * 12345 + s.x + 138;
    res = res * 12345 + s.dir + 138;
    res = res * 12345 + s.color + 138;
    res = res * 12345 + s.bloom + 138;
  }
  for (Block s: blocks) {
    res = res * 54321 + s.y + 531;
    res = res * 54321 + s.x + 531;
    res = res * 54321 + s.h + 531;
    res = res * 54321 + s.w + 531;
  }
  return res;
}
