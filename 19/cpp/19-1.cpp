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

struct either {
  bool ischar;
  char c;
  list<vi> rs;
  either(char c) : ischar(true), c(c) {}
  either() : ischar(false) {}
  void add(vi& v) {
    rs.push_front(v);
  }
};

map<int, either> rules;
pair<bool, int> check(string& s, int pos, int id) {
  if (rules[id].ischar) return {s[pos] == rules[id].c, pos + 1};
  each(v, rules[id].rs) {
    int np = pos;
    bool ok = true;
    each(x, v) {
      tie(ok, np) = check(s, np, x);
      if (!ok) break;
    }
    if (ok) return {true, np};
  }
  return {false, -1};
}

int main() {
  ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);

  string s;
  while (getline(cin, s) and !s.empty()) {
    int x = 0, id;
    vi v;
    for (int i = 0;;i++) {
      char c = s[i];
      if (isdigit(c)) {
        x *= 10;
        x += c - '0';
      }
      else {
        if (c == ':') {
          id = x;
        }
        else if (isalpha(c)) {
          rules[id] = either(c);
        }
        else if (c == '|') {
          rules[id].add(v);
          v.clear();
        }
        else if ((c == ' ' or !c) and x) {
          v.push_back(x);
        }
        if (!s[i]) {
          if (!v.empty()) rules[id].add(v);
          break;
        }
        x = 0;
      }
    }
  }
  int ans = 0;
  while (getline(cin, s)) {
    auto [ok, last] = check(s, 0, 0);
    if (ok and !s[last]) {
      ans++;
    }
  }
  cout << ans << endl;
  return 0;
}

