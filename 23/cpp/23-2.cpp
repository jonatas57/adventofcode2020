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

struct node {
  ll val;
  bool rem;
  node *next, *prev;
  node(ll v) : val(v), rem(false), next(this), prev(this) {}
};

node* insert(node* n, node* cs) {
  if (!cs) return n;
  n->prev = cs->prev;
  n->next = cs;
  cs->prev->next = n;
  cs->prev = n;
  return cs;
}

void insert(node* l, node* r, node* cs) {
  r->next = cs->next;
  l->prev = cs;
  cs->next = l;
  r->next->prev = r;
  l = l->prev;
  do {
    l = l->next;
    l->rem = false;
  } while (l != r);
}

pair<node*, node*> getNext(node* n, int x) {
  node *l = n->next, *r = n;
  loop(x) {
    r = r->next;
    r->rem = true;
  }
  l->prev->next = r->next;
  r->next->prev = l->prev;
  l->prev = r->next = nullptr;
  return {l, r};
}

int main() {
  ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);

  const int N = 1000000;
  string s;
  cin >> s;
  vector<node*> ids(N + 1, nullptr);
  node* cs = nullptr;
  each(c, s) {
    node* n = new node(c - '0');
    cs = insert(n, cs);
    ids[c - '0'] = n;
  }
  for (int i = 10;i <= N;i++) {
    node* n = new node(i);
    cs = insert(n, cs);
    ids[i] = n;
  }
  node* cur = cs;
  loop(10000000) {
    auto [l, r] = getNext(cur, 3);
    int dc = (cur->val + N - 2) % N + 1;
    while (ids[dc]->rem) {
      dc--;
      if (!dc) dc = N;
    }
    insert(l, r, ids[dc]);
    cur = cur->next;
  }
  node* x = ids[1]->next, *y = x->next;
  cout << x->val * y->val << endl;
  return 0;
}

