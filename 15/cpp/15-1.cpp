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

  string s;
  cin >> s;
  stringstream ss;
  ss << s;
  vi a;
  int x;
  char c;
  mii lasts;
  int id = 1;
  do {
    ss >> x;
    a.push_back(x);
    lasts[x] = id++;
  } while (ss >> c);
  int next = 0;
  for (;id <= 2020;) {
    a.push_back(next);
    x = id - (lasts.count(next) ? lasts[next] : id);
    lasts[next] = id++;
    next = x;
  }
  cout << a[2019] << endl;
  return 0;
}

