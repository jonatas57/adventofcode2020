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
  map<string, int> conv;
  graph() : size(0) {}
  void addEdge(string x, string y) {
    int a = addNode(x);
    int b = addNode(y);
    adj[b].push_back(a);
  }
  int addNode(string s) {
    if (!conv.count(s)) {
      conv[s] = size++;
      adj.emplace_back();
    }
    return conv[s];
  }
};

vb vis;
int dfs(graph& g, int u, int p = -1) {
  vis[u] = true;
  int ans = 1;
  each(v, g.adj[u]) {
    if (v == p or vis[v]) continue;
    ans += dfs(g, v, u);
  }
  return ans;
}

int main() {
  ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);

  string s;
  graph g;
  while (getline(cin, s)) {
    stringstream ss;
    ss << s;
    string u, a, b, c;
    ss >> a >> b;
    u = a + b;
    ss >> a >> a;
    do {
      ss >> a >> a >> b >> c;
      g.addEdge(u, a + b);
    } while (c.back() == ',');
  }
  vis.assign(g.size, false);
  cout << dfs(g, g.conv["shinygold"]) - 1 << endl;
  return 0;
}

