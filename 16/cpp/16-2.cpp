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
    if (b.back().second >= a[i].first) b.back().second = max(b.back().second, a[i].second);
    else b.push_back(a[i]);
  }
  a.swap(b);
}

vi getTicket(string& s) {
  int x = 0;
  vi ticket;
  for (int i = 0;;i++) {
    if (isdigit(s[i])) {
      x *= 10;
      x += s[i] - '0';
    }
    else {
      ticket.push_back(x);
      x = 0;
    }
    if (!s[i]) break;
  }
  return ticket;
}

int main() {
  ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);

  vector<ii> valid;
  string s;
  map<string, vector<ii>> fields;
  while (getline(cin, s) and !s.empty()) {
    size_t p = s.find(':');
    string field = s.substr(0, p);
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
        else if (x and y) valid.emplace_back(x, y), fields[field].emplace_back(x, y), x = y = 0, f = true;
        if (!s[i]) {
          break;
        }
      }
    }
  }
  sort(iter(valid));
  merge(valid);
  while (getline(cin, s) and (s.empty() or s[0] != 'y'));
  getline(cin, s);
  vi myTicket = getTicket(s);
  while (getline(cin, s) and (s.empty() or s[0] != 'n'));
  vector<vi> tickets;
  while (getline(cin, s)) {
    vi ticket = getTicket(s);
    bool isvalid = true;
    each(x, ticket) {
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
      if (!ok) isvalid = false;
    }
    if (isvalid) tickets.push_back(ticket);
  }
  assert(!tickets.empty());
  int n = tickets[0].size();
  vector<set<string>> possibles(n);
  loop(n) {
    for (auto& [f, inter] : fields) {
      bool ok = true;
      each(t, tickets) {
        bool ok2 = false;
        for (auto& [l, r] : inter) {
          if (l <= t[i] and t[i] <= r) ok2 = true;
        }
        if (!ok2) ok = false;
      }
      if (ok) possibles[i].insert(f);
    }
  }
  map<string, int> ids;
  for (int done = 0;done < n;) {
    string toremove;
    int id = 0;
    each(p, possibles) {
      if (p.size() == 1) {
        toremove = *p.begin();
        ids[toremove] = id;
        done++;
        break;
      }
      id++;
    }
    each(p, possibles) {
      p.erase(toremove);
    }
  }
  ll ans = 1;
  for (auto& [f, id] : ids) {
    if (f[0] == 'd' and f[1] == 'e') {
      ans *= (ll)myTicket[id];
    }
  }
  cout << ans << endl;
  return 0;
}

