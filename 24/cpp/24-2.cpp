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
  int ans = 0;
  map<ii, bool> state;
  map<ii, int> cnt;
  while (cin >> s) {
    int x = 0, y = 0;
    int dir = 0;
    for (int i = 0;s[i];i++) {
      if (s[i] == 'n') dir |= 4;
      else if (s[i] == 's') dir |= 2;
      else {
        if (s[i] == 'e') dir |= 1;
        if (dir & 4) x++;
        if (dir & 2) x--;
        if (dir & 1 and !(dir & 4)) y++;
        if (!(dir & 1) and !(dir & 2)) y--;
        dir = 0;
      }
    }
    ii pos(x, y);
    cnt[pos];
    if ((state[pos] = !state[pos])) {
      ans++;
      for (int i = -1;i <= 1;i++) for (int j = -1;j <= 1;j++) {
        if (i == j) continue;
        cnt[make_pair(x + i, y + j)]++;
      }
    }
    else {
      ans--;
      for (int i = -1;i <= 1;i++) for (int j = -1;j <= 1;j++) {
        if (i == j) continue;
        cnt[make_pair(x + i, y + j)]--;
      }
    }
  }
  loop(100) {
    map<ii, int> cnt2;
    for (auto& [pos, q] : cnt) {
      cnt2[pos] += q;
      int del = 0;
      if (state[pos] and (q == 0 or q > 2)) state[pos] = false, del = -1, ans--;
      else if (!state[pos] and q == 2) state[pos] = true, del = 1, ans++;
      if (del) {
        auto [x, y] = pos;
        for (int i = -1;i <= 1;i++) for (int j = -1;j <= 1;j++) {
          if (i == j) continue;
          cnt2[make_pair(x + i, y + j)] += del;
        }
      }
    }
    cnt.swap(cnt2);
  }
  cout << ans << endl;
  return 0;
}
