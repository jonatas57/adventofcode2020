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

ll parse(string& s, int& pos) {
  ll ans = 0;
  ll x = 0;
  bool add = true;
  for (;;pos++) {
    if (s[pos] == ' ') continue;
    if (isdigit(s[pos])) {
      x *= 10;
      x += s[pos] - '0';
    }
    else if (s[pos] == '(') {
      pos++;
      x = parse(s, pos);
    }
    else {
      if (add) ans += x;
      else ans *= x;
      x = 0;
      if (s[pos] == '+') add = true;
      else if (s[pos] == '*') add = false;
      else return ans;
    }
  }
  return ans;
}

int main() {
  ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);

  string s;
  ll ans = 0;
  while (getline(cin, s)) {
    int pos = 0;
    ans += parse(s, pos);
  }
  cout << ans << endl;
  return 0;
}

