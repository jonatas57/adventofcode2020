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

struct graph {
  int size;
  vector<list<int>> adj;
  vb used;
  graph() : size(0) {}
  void addEdge(int a, int b) {
    adj[a].push_back(b);
    adj[b].push_back(a);
  }
  int addNode() {
    adj.emplace_back();
    used.push_back(false);
    return size++;
  }
};

int main() {
  ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);

  vector<string> a;
  string s;
  while (cin >> s) a.push_back(s);
  int h = a.size(), w = a[0].length();
  graph g;
  vi d1(h + w - 1, -1), d2(h + w - 1, -1), vert(w, -1);
  loop(h) {
    int hor = -1;
    vloop(j, w) {
      if (a[i][j] == '.') continue;
      int u = g.addNode();
      int u1 = h - 1 - i + j, u2 = i + j;
      if (d1[u1] != -1) g.addEdge(u, d1[u1]);
      if (d2[u2] != -1) g.addEdge(u, d2[u2]);
      if (vert[j] != -1) g.addEdge(u, vert[j]);
      if (hor != -1) g.addEdge(u, hor);
      hor = vert[j] = d1[u1] = d2[u2] = u;
    }
  }

  bool modified;
  vb used(g.size, false);
  do {
    modified = false;
    loop(g.size) {
      int cnt = 0;
      each(v, g.adj[i]) {
        if (g.used[v]) cnt++;
      }
      if (g.used[i] and cnt >= 5) used[i] = false, modified = true;
      else if (!g.used[i] and cnt == 0) used[i] = true, modified = true;
      else used[i] = g.used[i];
    }
    g.used.swap(used);
  } while (modified);
  int ans = 0;
  loop(g.size) ans += g.used[i];
  cout << ans << endl;
  return 0;
}

