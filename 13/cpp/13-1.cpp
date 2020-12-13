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

  int t;
  cin >> t;
  stringstream ss;
  int id = 0;
  vector<ll> ids;
  string s;
  cin >> s;
  for (int i = 0;;i++) {
    if (isdigit(s[i])) {
      id *= 10;
      id += s[i] - '0';
    }
    else if (s[i] != 'x') {
      if (id) ids.push_back(id);
      id = 0;
      if (!s[i]) break;
    }
  }
  int ans = INF, bus;
  each(x, ids) {
    int wait = (x - t % x) % x;
    if (ans > wait) {
      ans = wait;
      bus = x;
    }
  }
  cout << ans * bus << endl;
  return 0;
}

