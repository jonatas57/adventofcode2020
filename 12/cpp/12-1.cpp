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

  int x = 0, y = 0, dir = 0;
  string s;
  while (cin >> s) {
    char op = s[0];
    int st = stoi(s.substr(1));
    if (op == 'N') y += st;
    else if (op == 'S') y -= st;
    else if (op == 'E') x += st;
    else if (op == 'W') x -= st;
    else if (op == 'L') dir = (4 + dir - st / 90) % 4;
    else if (op == 'R') dir = (dir + st / 90) % 4;
    else if (op == 'F') {
      x += st * ((dir == 0) - (dir == 2));
      y += st * ((dir == 3) - (dir == 1));
    }
  }
  cout << abs(x) + abs(y) << endl;
  return 0;
}

