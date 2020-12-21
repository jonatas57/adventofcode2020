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

set<int> intersect(set<int>& a, set<int>& b) {
  set<int> c;
  for (auto i = a.begin(), j = b.begin();i != a.end() && j != b.end();) {
    if (*i == *j) {
      c.insert(*i);
      i++;
      j++;
    }
    else if (*i > *j) j++;
    else i++;
  }
  return c;
}

set<int> solve(vector<set<int>>& aux) {
  set<int> ans;
  each(ign, aux) {
    int torem;
    each(s, aux) {
      if (s.size() == 1) {
        torem = *s.begin();
        break;
      }
    }
    each(s, aux) s.erase(torem);
    ans.insert(torem);
  }
  return ans;
}

int main() {
  ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);

  string s;
  vector<set<int>> ings, as;
  set<int> allergenes;
  map<string, int> id;
  int nextid = 0;
  while (getline(cin, s)) {
    stringstream ss;
    ss << s;
    string t;
    bool isallerg = false;
    set<int> ing, a;
    while (ss >> t) {
      if (t[0] == '(') isallerg = true;
      else {
        if (isallerg) t = t.substr(0, t.size() - 1);
        int x = id.count(t) ? id[t] : id[t] = nextid++;
        if (isallerg) a.insert(x), allergenes.insert(x);
        else ing.insert(x);
      }
    }
    ings.push_back(ing);
    as.push_back(a);
  }

  int sz = ings.size();
  vector<set<int>> aux;
  each(x, allergenes) {
    set<int> alIngs;
    loop(sz) {
      if (!as[i].count(x)) continue;
      if (alIngs.empty()) alIngs = ings[i];
      else intersect(alIngs, ings[i]).swap(alIngs);
    }
    aux.emplace_back(alIngs);
  }
  set<int> is = solve(aux);
  int ans = 0;
  each(v, ings) {
    each(x, v) ans += !is.count(x);
  }
  cout << ans << endl;
  return 0;
}

