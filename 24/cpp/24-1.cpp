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
  int cnt = 0;
  map<ii, bool> state;
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
    if ((state[pos] = !state[pos])) cnt++;
    else cnt--;
  }
  cout << cnt << endl;
  return 0;
}
/*
000
001
010
011
100
101
*/
