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

void rotate(int& x, int& y, int z) {
  if (z < 0) z += 4;
  loop(z) {
    swap(x, y);
    x = -x;
  }
}

int main() {
  ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);

  int x = 0, y = 0;
  int wx = 10, wy = 1;
  string s;
  while (cin >> s) {
    char op = s[0];
    int st = stoi(s.substr(1));
    if (op == 'N') wy += st;
    else if (op == 'S') wy -= st;
    else if (op == 'E') wx += st;
    else if (op == 'W') wx -= st;
    else if (op == 'L') rotate(wx, wy, st / 90);
    else if (op == 'R') rotate(wx, wy, -st / 90);
    else if (op == 'F') {
      x += st * wx;
      y += st * wy;
    }
  }
  cout << abs(x) + abs(y) << endl;
  return 0;
}

