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

  vector<string> a;
  string s;
  while (cin >> s) a.push_back(s);
  vector<string> b = a;
  int h = a.size(), w = a[0].length();
  bool modified;
  do {
    modified = false;
    for (int i = 0;i < h;i++) {
      for (int j = 0;j < w;j++) {
        if (a[i][j] == '.') continue;
        int cnt = 0;
        for (int x = -1;x <= 1;x++) {
          if (i + x < 0 or i + x >= h) continue;
          for (int y = -1;y <= 1;y++) {
            if (j + y < 0 or j + y >= w or (x | y) == 0) continue;
            if (a[i + x][j + y] == '#') cnt++;
          }
        }
        if (a[i][j] == 'L' and cnt == 0) b[i][j] = '#', modified = true;
        else if (a[i][j] == '#' and cnt >= 4) b[i][j] = 'L', modified = true;
        else b[i][j] = a[i][j];
      }
    }
    a.swap(b);
  } while (modified);
  int ans = 0;
  each(s, a) each(c, s) if (c == '#') ans++;
  cout << ans << endl;
  return 0;
}

