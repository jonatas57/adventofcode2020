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

ll read(string& s, int p) {
  ll x = 0;
  for (int i = p;s[i] and isdigit(s[i]);i++) {
    x *= 10;
    x += s[i] - '0';
  }
  return x;
}

int main() {
  ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);

  map<ll, ll> memo;
  ll ones = 0, zeros = 0;
  string s;
  int cnt;
  vector<ll> vs;
  while (getline(cin, s)) {
    if (s[1] == 'a') {
      ones = zeros = 0;
      cnt = 0;
      vs.clear();
      for (ll i = 7, j = (1ll << 35);s[i];i++, j >>= 1) {
        ones <<= 1;
        zeros <<= 1;
        if (s[i] == '1') ones |= 1;
        if (s[i] != 'X') zeros |= 1;
        else vs.push_back(j), cnt++;
      }
    }
    else {
      ll pos = (read(s, 4) & zeros) | ones;
      ll x = read(s, s.find_last_of(' ') + 1);
      for (ll i = 0;i < (1ll << cnt);i++) {
        ll del = 0;
        for (ll j = 1, k = 0;k < cnt;j <<= 1, k++) if (i & j) del |= vs[k];
        memo[pos | del] = x;
      }
    }
  }
  ll ans = 0;
  for (auto& [k, v] : memo) ans += v;
  cout << ans << endl;
  return 0;
}

