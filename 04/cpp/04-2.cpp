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

bool checkNum(string s, string l, string r) {
  if (s.empty()) return false;
  if (s.length() != l.length()) return false;
  each(c, s) if (!isdigit(c)) return false;
  return l <= s and s <= r;
}

bool checkHei(string s) {
  if (s.empty()) return false;
  int idx = 0;
  for (;s[idx] and isdigit(s[idx]);idx++);
  string t = s.substr(idx);
  string n = s.substr(0, idx);
  return (t == "in" and checkNum(n, "59", "76")) or (t == "cm" and checkNum(n, "150", "193"));
}

bool checkCol(string s) {
  if (s.empty()) return false;
  if (s[0] != '#') return false;
  for (int i = 1;s[i];i++) if (!isdigit(s[i]) and (!islower(s[i]) or s[i] > 'f')) return false;
  return true;
}

set<string> valCol = {"amb", "blu", "brn", "gry", "grn", "hzl", "oth"};
bool checkEye(string s) {
  return valCol.count(s);
}

bool isvalid(map<string, string>& p) {
  bool valid = checkNum(p["byr"], "1920", "2002");
  valid &= checkNum(p["iyr"], "2010", "2020");
  valid &= checkNum(p["eyr"], "2020", "2030");
  valid &= checkHei(p["hgt"]);
  valid &= checkCol(p["hcl"]);
  valid &= checkEye(p["ecl"]);
  valid &= checkNum(p["pid"], "000000000", "999999999");
  return valid;
}

int main() {
  ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);

  string s;
  vector<map<string, string>> pass;
  map<string, string> at;
  while (getline(cin, s)) {
    if (s.empty()) {
      pass.push_back(at);
      at.clear();
    }
    else {
      stringstream ss;
      ss << s;
      string t;
      while (ss >> t) {
        size_t x = t.find(':');
        at[t.substr(0, x)] = t.substr(x + 1);
      }
    }
  }
  if (!at.empty()) pass.push_back(at);
  int ans = 0;
  for (auto& p : pass) {
    if (isvalid(p)) ans++;
  }
  cout << ans << endl;
  return 0;
}

