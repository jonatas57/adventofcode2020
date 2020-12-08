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

vb used;
int dfs(vector<pair<string, int>>& ops, int init, int pos, int sz, bool ch = false) {
  if (pos >= sz) return init;
  if (used[pos]) return -INF;
  used[pos] = true;
  int ret;
  if (ops[pos].first[0] == 'a') {
    ret = dfs(ops, init + ops[pos].second, pos + 1, sz, ch);
  }
  else {
    ret = dfs(ops, init, pos + (ops[pos].first[0] == 'n' ? 1 : ops[pos].second), sz, ch);
    if (ret == -INF and !ch) {
      ret = dfs(ops, init, pos + (ops[pos].first[0] == 'n' ? ops[pos].second : 1), sz, true);
    }
  }
  used[pos] = false;
  return ret;
}

int main() {
  ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);

  vector<pair<string, int>> ops;
  string s;
  int n;
  while (cin >> s >> n) ops.emplace_back(s, n);
  int sz = ops.size();
  used.assign(sz, false);
  cout << dfs(ops, 0, 0, sz) << endl;
  return 0;
}

