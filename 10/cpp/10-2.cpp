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

  int x;
  vi a(1, 0);
  while (cin >> x) a.push_back(x);
  sort(iter(a));
  a.push_back(a.back() + 3);
  vector<ll> dp(a.size(), 0);
  dp[0] = 1;
  for (int i = 1;i < a.size();i++) {
    for (int j = i - 1;j >= i - 3 and j >= 0;j--) {
      if (a[i] - a[j] <= 3) dp[i] += dp[j];
    }
  }
  cout << dp.back() << endl;
  return 0;
}

