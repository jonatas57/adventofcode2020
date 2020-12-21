#include <bits/stdc++.h>

using namespace std;

typedef long long          ll;
typedef unsigned long long ull;
typedef vector<int>         vi;
typedef vector<bool>       vb;
typedef map<int, int>      mii;
typedef pair<int, int>     ii;

#define INF                0x3f3f3f3f
#define INFLL              0x3f3f3f3f3f3f3f3f
#define each(x, s)         for(auto& x : s)
#define loop(x)            for(int i = 0;i < x;i++)
#define vloop(v, x)        for(int v = 0;v < x;v++)
#define avg(l, r)          l + (r - l) / 2
#define iter(a)            a.begin(), a.end()
#define riter(a)           a.rbegin(), a.rend()
#define endl               "\n"

const ll mod = 1000000007;
const double EPS = 1e-7;
const double PI = acos(-1);

void add(char c, int& x) {
  x <<= 1;
  x |= c == '#';
}

map<int, bool> used;
vector<vector<ll>> ans;
int sz, w, l;

bitset<96> inv(bitset<96> x, int len) {
  bitset<96> y = 0;
  loop(len) {
    y <<= 1;
    y.set(0, y[0] | x[0]);
    x >>= 1;
  }
  return y;
}

int inv(int x, int len) {
  return inv(bitset<96>(x), len).to_ulong();
}

struct tile {
  int id;
  int rot;
  vi edges;
  bool flipped;
  vector<bitset<96>> image;
  int fliplen;
  bool es;
  tile() {}
  tile(int id, vector<string>& ss, bool es = true) : id(id), rot(0), edges(4, 0), flipped(false), fliplen(ss.size()), es(es) {
    each(c, ss[0]) add(c, edges[0]);
    each(v, ss) {
      add(v.back(), edges[1]);
      add(v[0], edges[3]);
    }
    each(c, ss.back()) add(c, edges[2]);
    each(s, ss) {
      bitset<96> x = 0;
      each(c, s) {
        x <<= 1;
        x |= c == '#';
      }
      image.push_back(x);
    }
  }
  tile(vector<bitset<96>>& img) : id(0), rot(0), flipped(false), image(img), fliplen(img.size()), es(false) {}
  void rotate() {
    rot = (rot + 1) % 4;
    if (es) {
      int tmp = edges[3];
      edges[3] = edges[2];
      edges[2] = inv(edges[1], fliplen);
      edges[1] = edges[0];
      edges[0] = inv(tmp, fliplen);
    }
    vector<bitset<96>> newimage;
    bitset<96> m;
    m[fliplen - 1] = 1;
    loop(l) {
      bitset<96> x = 0;
      for (int j = fliplen - 1;j >= 0;j--) {
        x <<= 1;
        x |= (m & image[j]).any();
      }
      newimage.push_back(x);
      m >>= 1;
    }
    image.swap(newimage);
  }
  void flip() {
    if (es) {
      swap(edges[1], edges[3]);
      edges[0] = inv(edges[0], fliplen);
      edges[2] = inv(edges[2], fliplen);
    }
    flipped = !flipped;
    each(x, image) {
      x = inv(x, fliplen);
    }
  }
};

bool solve(map<int, tile>& ts, int x = 0, int y = 0) {
  if (x == w) return true;
  for (auto& [id, t] : ts) {
    if (used[id]) continue;
    used[id] = true;
    loop(2) {
      loop(4) {
        if ((!x or ts[ans[x - 1][y]].edges[2] == t.edges[0]) and (!y or ts[ans[x][y - 1]].edges[1] == t.edges[3])) {
          ans[x][y] = id;
          int nx = x + (y == w - 1), ny = y == w - 1 ? 0 : y + 1;
          if (solve(ts, nx, ny)) return true;
        }
        t.rotate();
      }
      t.flip();
    }
    ans[x][y] = -1;
    used[id] = false;
  }
  return false;
}

int main() {
  ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);

  map<int, tile> ts;
  string s;
  while (true) {
    int id;
    vector<string> t;
    bool eof;
    while ((eof = (bool)getline(cin, s)) and !s.empty()) {
      if (s[0] == 'T') {
        stringstream ss;
        ss << s;
        ss >> s >> id;
      }
      else {
        t.push_back(s);
      }
    }
    ts[id] = tile(id, t);
    if (!eof) {
      sz = t.size();
      break;
    }
  }
  
  w = sqrt(ts.size()) + EPS;
  l = w * sz;
  ans.resize(w, vector<ll>(w, -1));
  solve(ts);

  vector<bitset<96>> lake;
  bitset<96> mask((1 << (sz - 1)) - 1);
  each(v, ans) {
    for (int i = 1;i < sz - 1;i++) {
      bitset<96> x = 0;
      each(y, v) {
        x <<= sz - 2;
        x |= (ts[y].image[i] & mask) >> 1;
      }
      lake.push_back(x);
    }
  }
  tile finaltile(lake);
  vector<bitset<96>> monster = {0b00000000000000000010,
                                0b10000110000110000111,
                                0b01001001001001001000};

  l = w * (sz - 2);
  bool found = false;
  vector<bitset<96>> finalImage;
  loop(2) {
    if (found) break;
    loop(4) {
      vector<bitset<96>> woMonster = finaltile.image;
      loop(l - 2) {
        vector<bitset<96>> aux = monster;
        vloop(j, l - 19) {
          bool ok = true;
          vloop(k, 3) {
            ok &= (finaltile.image[i + k] & aux[k]) == aux[k];
          }
          if (ok) {
            vloop(k, 3) {
              woMonster[i + k] &= (monster[k] << j).flip();
            }
            found = true;
          }
          each(x, aux) x <<= 1;
        }
      }
      if (found) {
        finalImage = woMonster;
        break;
      }
      finaltile.rotate();
    }
    finaltile.flip();
  }
  int ans = 0;
  each(bs, finalImage) {
    ans += bs.count();/*@*/
    cerr << bs.to_string() << endl;/*@*/
  }
  cout << ans << endl;
  return 0;
}

