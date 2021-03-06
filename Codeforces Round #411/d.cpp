#include <bits/stdc++.h>

using namespace std;

const int N = 1e5 + 5;
const int MAGIC = 320;

int par[N], sz[N], add[N], up[N];
vector<int> edge[N], col[N];
vector<long long> d[N];
int id[N];

int find(int u) {
  return par[u] = (par[u] == u? u : find(par[u]));
}

void merge(int u, int v) {
  sz[find(v)] += sz[find(u)];
  par[find(u)] = find(v);
}

double dp[MAGIC][MAGIC];

void dfs(int now, int bef) {
  for (auto it : edge[now]) if (it != bef) {
    dfs(it, now);
    add[now] = max(add[now], add[it] + 1);
  }
}

void dfs_sub(int now, int bef) {
  int last = up[now] + 1;
  for (auto it : edge[now]) if (it != bef) {
    up[it] = max(up[it], last);
    last = max(last, add[it] + 2);
  }
  last = up[now] + 1;
  for (int i = (int) edge[now].size() - 1; i >= 0; i--) if (edge[now][i] != bef){
    auto it = edge[now][i];
    up[it] = max(up[it], last);
    last = max(last, add[it] + 2);
  }
  add[now] = max(add[now], up[now]);
  //printf("add %d %d\n", now, add[now]);
  col[find(now)].push_back(add[now]);
  for (auto it : edge[now]) if (it != bef) dfs_sub(it, now);
}

// asumsi component u selalu kecil, v selalu par dsu
long long solve(int u, int v, int bef = 0) {
  int root = find(u);
  int best = max(col[root].back(), col[v].back());
  long long ret = 0;
  int p = upper_bound(col[v].begin(), col[v].end(), best - add[u] - 1) - col[v].begin();
  ret += 1LL * best * p;
  if (p < col[v].size()) ret += d[v][p] + 1LL * (col[v].size() - p) * (1 + add[u]);
  for (auto it : edge[u]) if (it != bef) ret += solve(it, v, u);
  return ret;
}

int main() {
  for (int i = 0; i < N; i++) par[i] = i, sz[i] = 1;
  
  int n, m, q;
  scanf("%d %d %d", &n, &m, &q);
  for (int i = 0; i < m; i++) {
    int u, v;
    scanf("%d %d", &u, &v);
    edge[u].push_back(v);
    edge[v].push_back(u);
    merge(u, v);
  }
  vector<int> big;
  for (int i = 1; i <= n; i++) if (i == find(i)) {
    dfs(i, 0);
    dfs_sub(i, 0);
    sort(col[i].begin(), col[i].end());
    d[i].resize(col[i].size());
    for (int j = col[i].size() - 1; j >= 0; j--) {
      if (j+1 < col[i].size()) d[i][j] = d[i][j+1];
      d[i][j] += col[i][j];
    }
    if (sz[i] > MAGIC) {
      big.push_back(i);
    }
  }
  for (int i = 0; i < big.size(); i++) id[big[i]] = i;
  for (int i = 0; i < big.size(); i++) {
    for (int j = i + 1; j < big.size(); j++) {
      int l = (sz[big[i]] < sz[big[j]]? big[i] : big[j]);
      int r = (l == big[i]? big[j] : big[i]);
      dp[i][j] = dp[j][i] = (double) solve(l, r) / sz[big[i]] / sz[big[j]];
    }
  }
  while (q--) {
    int u, v;
    scanf("%d %d", &u, &v);
    u = find(u);
    v = find(v);
    if (u == v) {
      puts("-1");
      continue;
    }
    if (sz[u] > MAGIC && sz[v] > MAGIC) {
      printf("%.15f\n", dp[id[u]][id[v]]);
      continue;
    }
    int l = (sz[u] < sz[v]? u : v);
    int r = (l == u? v : u);
    printf("%.15f\n", (double) solve(l, r) / sz[l] / sz[r]);
  }
  return 0;
}
