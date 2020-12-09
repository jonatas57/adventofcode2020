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
  vector<ll> a;
  while (cin >> x) a.push_back(x);
  int sz = a.size();
  ll inv;
  for (int i = 25;i < sz;i++) {
    bool ok = false;
    for (int j = i - 25;j < i;j++) {
      for (int k = j + 1;k < i;k++) {
        if (a[j] + a[k] == a[i]) ok = true;
      }
    }
    if (!ok) {
      inv = a[i];
      break;
    }
  }
  ll sum = 0;
  ll l = INF, r = 0;
  for (int i = 0, j = 0;j < sz;) {
    if (sum < inv) sum += a[j++];
    else if (sum > inv) sum -= a[i++];
    else {
      for (int k = i;k < j;k++) {
        l = min(l, a[k]);
        r = max(r, a[k]);
      }
      cout << l + r << endl;
      break;
    }
  }
  return 0;
}

