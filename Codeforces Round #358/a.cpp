#include <bits/stdc++.h>

using namespace std;

int cnt[5];

int main() {
  int n, m;
  scanf("%d %d", &n, &m);
  for(int i = 1; i <= m; i++) cnt[i % 5]++;
  long long ans = 0;
  for(int i = 1; i <= n; i++) {
    ans += cnt[(5 - (i % 5)) % 5];
  }
  cout << ans << endl;
  return 0;
}
