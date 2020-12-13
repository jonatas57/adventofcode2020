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

const double EPS = 1e-7;
const double PI = acos(-1);

ll xp(ll b, ll e, ll mod = LLONG_MAX) {
  if (e == 0) return 1;
  ll c = xp(b, e >> 1, mod);
  c = c * c % mod;
  if (e & 1) c = c * b % mod;
  return c;
}

ll tot(ll x) {
  ll ans = 1;
  for (ll i = 2;i * i <= x;i++) {
    ll cnt = 0;
    while (x % i == 0) {
      x /= i;
      cnt++;
    }
    if (cnt) {
      ans *= xp(i, cnt) - xp(i, cnt - 1);
    }
  }
  if (x > 1) ans *= x - 1;
  return ans;
}

ll inv(ll x, ll mod) {
  return xp(x, tot(mod) - 1, mod);
}

ll chinese(vector<ii>& mods) {
  __int128 N = 1;
  each(p, mods) N *= p.second;
  vector<ll> y;
  __int128 ans = 0;
  for (auto& [a, mod] : mods) {
    __int128 x = (N / mod) * a % N;
    x = x * inv(N / mod, mod) % N;
    ans += x;
    ans %= N;
  }
  return (ll)ans;
}

int main() {
  ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);

  int t;
  cin >> t;
  int id = 0;
  vector<ii> ids;
  string s;
  cin >> s;
  int div;
  for (int i = 0, j = 0;;i++) {
    if (isdigit(s[i])) {
      id *= 10;
      id += s[i] - '0';
    }
    else if (s[i] != 'x') {
      if (id) {
        if (j) ids.emplace_back((id + j % id) % id, id);
        else div = id;
      }
      if (s[i] == ',') j--;
      id = 0;
      if (!s[i]) break;
    }
  }
  ll mmc = 1;
  each(p, ids) {
    mmc = lcm(mmc, p.second);
  }
  ll ans = chinese(ids);
  loop(div + 1) {
    if ((ans + i * mmc) % div == 0) {
      ans += i * mmc;
      break;
    }
  }
  cout << ans << endl;
  return 0;
}

