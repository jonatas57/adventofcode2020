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

int main() {
  ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);

  string s;
  vector<vector<string>> st(25, vector<string>(25, string(25, '.')));
  map<int, map<int, map<int, bool>>> state;
  map<int, map<int, map<int, int>>> cnt;
  for (int i = 0;cin >> s;i++) {
    for (int j = 0;s[j];j++) {
      state[0][i][j] = s[j] == '#';
    }
  }
  loop(6) {
    for (auto& [x, m] : state) for (auto& [y, m2] : m) for (auto& [z, act] : m2) {
      cnt[x][y][z];
      if (!act) {
        continue;
      }
      for (int i = -1;i <= 1;i++) for (int j = -1;j <= 1;j++) for (int k = -1;k <= 1;k++) {
        if (i | j | k) cnt[x + i][y + j][z + k]++;
      }
    }
    for (auto& [x, m] : cnt) for (auto& [y, m2] : m) for (auto& [z, act] : m2) {
      if (state[x][y][z]) {
        if (cnt[x][y][z] == 2 or cnt[x][y][z] == 3) state[x][y][z] = true;
        else state[x][y][z] = false;
      }
      else {
        if (cnt[x][y][z] == 3) state[x][y][z] = true;
        else state[x][y][z] = false;
      }
    }
    cnt.clear();
  }
  int ans = 0;
  each(p, state) each(q, p.second) each(m, q.second) ans += m.second;
  cout << ans << endl;
  return 0;
}

