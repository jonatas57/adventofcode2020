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

void merge(vector<ii>& a) {
  int n = a.size();
  vector<ii> b(1, a[0]);
  for (int i = 1;i < n;i++) {
    if (b.back().second >= a[i].first) b.back().second = a[i].second;
    else b.push_back(a[i]);
  }
  a.swap(b);
}

int main() {
  ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);

  vector<ii> valid;
  string s;
  while (getline(cin, s) and !s.empty()) {
    size_t p = s.find(':');
    int x = 0, y = 0;
    bool f = true;
    for (size_t i = p + 2;;i++) {
      if (isdigit(s[i])) {
        if (f) x *= 10, x += s[i] - '0';
        else y *= 10, y += s[i] - '0';
      }
      else if (!x and !y) continue;
      else {
        if (f) f = false;
        else if (x and y) valid.emplace_back(x, y), x = y = 0, f = true;
        if (!s[i]) {
          break;
        }
      }
    }
  }
  sort(iter(valid));
  merge(valid);
  while (getline(cin, s) and (s.empty() or s[0] != 'n'));
  int ans = 0;
  while (getline(cin, s)) {
    int x = 0;
    for (int i = 0;;i++) {
      if (isdigit(s[i])) {
        x *= 10;
        x += s[i] - '0';
      }
      else {
        bool ok = false;
        for (auto& [l, r] : valid) {
          if (l > x) {
            break;
          }
          else if (r >= x) {
            ok = true;
            break;
          }
        }
        if (!ok) {
          ans += x;
        }
        x = 0;
      }
      if (!s[i]) break;
    }
  }
  cout << ans << endl;
  return 0;
}

