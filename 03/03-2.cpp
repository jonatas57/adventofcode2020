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

  vector<string> mp;
  string s;
  while (cin >> s) mp.push_back(s);
  int n = mp.size();
  int m = mp[0].length();
  vector<ii> ss = {{1, 1}, {3, 1}, {5, 1}, {7, 1}, {1, 2}};
  ll ans = 1;
  for (auto [x, y] : ss) {
    ll cnt = 0;
    for (int i = 0, j = 0;i < n;i += y, j += x) {
      if (mp[i][j % m] == '#') cnt++;
    }
    ans *= cnt;
  }
  cout << ans << endl;
  return 0;
}

