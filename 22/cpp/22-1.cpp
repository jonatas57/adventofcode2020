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

  vector<list<int>> ps(2);
  string s;
  for (int i = 0;getline(cin, s);) {
    if (s.empty()) i++;
    else if (isdigit(s[0])) ps[i].push_back(stoi(s));
  }
  while (!ps[0].empty() and !ps[1].empty()) {
    int x = ps[0].front(), y = ps[1].front();
    ps[0].pop_front();
    ps[1].pop_front();
    int w = 0;
    if (x < y) {
      w = 1;
      swap(x, y);
    }
    ps[w].push_back(x);
    ps[w].push_back(y);
  }
  int ans = 0;
  int w = ps[0].empty();
  for (int i = 1;!ps[w].empty();i++) {
    ans += ps[w].back() * i;
    ps[w].pop_back();
  }
  cout << ans << endl;
  return 0;
}

