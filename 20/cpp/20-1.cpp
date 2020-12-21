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
int sz, w, mask;

int inv(int x) {
  int y = 0;
  loop(sz) {
    y <<= 1;
    y |= x & 1;
    x >>= 1;
  }
  return y;
}

struct tile {
  int id;
  int rot;
  vi edges;
  bool flipped;
  tile() {}
  tile(int id, vector<string>& ss) : id(id), rot(0), edges(4, 0), flipped(false) {
    each(c, ss[0]) add(c, edges[0]);
    each(v, ss) {
      add(v.back(), edges[1]);
      add(v[0], edges[3]);
    }
    each(c, ss.back()) add(c, edges[2]);
  }
  void rotate() {
    rot = (rot + 1) % 4;
    int tmp = edges[3];
    edges[3] = edges[2];
    edges[2] = inv(edges[1]);
    edges[1] = edges[0];
    edges[0] = inv(tmp);
  }
  void flip() {
    swap(edges[1], edges[3]);
    edges[0] = inv(edges[0]);
    edges[2] = inv(edges[2]);
    flipped = !flipped;
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
  mask = (1 << w) - 1;
  ans.resize(w, vector<ll>(w, -1));
  solve(ts);
  ll prod = ans[0][0] * ans[0][w - 1] * ans[w - 1][0] * ans[w - 1][w - 1];
  cout << prod << endl;
  return 0;
}

