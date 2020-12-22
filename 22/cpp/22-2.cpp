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

struct player {
  int sz;
  deque<int> deck;
  player() : sz(0) {}
  int draw() {
    int x = deck.front();
    deck.pop_front();
    sz--;
    return x;
  }
  void addCard(int c) {
    deck.push_back(c);
    sz++;
  }
  void addCards(int w, int l) {
    deck.push_back(w);
    deck.push_back(l);
    sz += 2;
  }
  bool empty() {
    return deck.empty();
  }
  int size() {
    return sz;
  }
  bool operator<(const player& p) const {
    return deck < p.deck;
  }
};

bool solve(vector<player>& ps) {
  bool p1win = true;
  set<vector<player>> used;
  while (ps[0].size() and ps[1].size()) {
    if (!used.insert(ps).second) break;
    int x = ps[0].draw();
    int y = ps[1].draw();
    int w = 0;
    if (x <= ps[0].size() and y <= ps[1].size()) {
      vector<player> ps2(2);
      for (int i = 0;i < x and i < ps[0].size();i++) ps2[0].addCard(ps[0].deck[i]);
      for (int i = 0;i < y and i < ps[1].size();i++) ps2[1].addCard(ps[1].deck[i]);
      if (!solve(ps2)) {
        w = 1;
        swap(x, y);
      }
    }
    else if (x < y) {
      w = 1;
      swap(x, y);
    }
    ps[w].addCards(x, y);
  }
  if (ps[0].empty()) p1win = false;
  return p1win;
}

int main() {
  ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);

  vector<player> ps(2);
  string s;
  for (int i = 0;getline(cin, s);) {
    if (s.empty()) i++;
    else if (isdigit(s[0])) ps[i].addCard(stoi(s));
  }
  solve(ps);
  int ans = 0;
  int w = ps[0].empty();
  for (int i = ps[w].size();!ps[w].empty();i--) {
    ans += ps[w].draw() * i;
  }
  cout << ans << endl;
  return 0;
}

