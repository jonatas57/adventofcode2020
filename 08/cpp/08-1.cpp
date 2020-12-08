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

  int init = 0;
  vector<pair<string, int>> ops;
  string s;
  int n;
  while (cin >> s >> n) ops.emplace_back(s, n);
  vb used(ops.size(), false);
  for (int i = 0;!used[i];) {
    used[i] = true;/*@*/
    cerr << ops[i].first << " " << ops[i].second << ": ";/*@*/
    if (ops[i].first[0] == 'a') {
      init += ops[i].second;
      i++;
    }
    else if (ops[i].first[0] == 'j') {
      i += ops[i].second;
    }
    else i++;/*@*/
      cerr << "i -> " << i << endl;/*@*/
  }
  cout << init << endl;
  return 0;
}

