/*

With our small shoulders next to each others,
we walked all alone
For a mere trivial matter, we burst in laughter
And also gazed for the same dreams
If I listen carefully, 
even now I still could hear
your voice is resounding 
in the middle of 
this orange-colored town

It's so boring, 
when you're nowhere
If I said I felt lonely, 
you'd laugh after me
But countless times, 

I've ensured
all things you left behind won't vanish, 
they'll continue to sparkling beautifully

I’ll smile in no time, 
if I remember, recall your smiling faces
Just like after rain sky,
relieves all troubles from my heart

I believe, 
we’ll be the same like those old days
still like innocent children
Run and dash away after the cycle of seasons
Face tomorrows of our own

If I was all alone, I felt uneasy
Sleepless nights, you were always by my side
kept telling me your story

What matters 
will you face from now on?
And also, 
what matters will I face from here?
Secretly, I try to entrust my tears
along with the setting down twilight
in the middle of this orange-colored town

In the midst of millions rays
was born a glimmer of love
Even though you’ve changed
or still the way you’re
You’re still yourself
Nothing to be worried of

It would be nice, 
if someday we’ve been adults
encountered ac
our dearest one,
brought along 
our irreplaceable families
and could meet again here, 
in this place

I’ll smile in no time, 
if I remember, recall your smiling faces
Just like after rain sky,
relieves all troubles from my heart

In the midst of millions rays
was born a glimmer of love
Run and dash away after the cycle of seasons
Face tomorrows of our own
Choose dreams of our own

*/

#include <bits/stdc++.h>

using namespace std;

const int N = 55;
const int T = 5105;

int f[N], s[N];
double p[N];
int n, r;
double dp[N][T];

double solve(double x) {
  for (int j = 0; j < T; j++) {
    if (j <= r) {
      dp[n][j] = 0;
    } else {
      dp[n][j] = x;
    }
  }
  for (int i = n - 1; i >= 0; i--) {
    for (int j = 0; j < T; j++) dp[i][j] = x;
    for (int j = 0; j <= r; j++) {
      dp[i][j] = p[i] * (f[i] + min(x, dp[i+1][j + f[i]]))
               + (1 - p[i]) * (s[i] + min(x, dp[i+1][j + s[i]]));
    }
  }
  return dp[0][0];
}

int main() {
  scanf("%d %d", &n, &r);
  for (int i = 0; i < n; i++) {
    scanf("%d %d %lf", f + i, s + i, p + i);
    p[i] /= 100;
  }
  double l = 0, r = 1e18;
  for (int iter = 0; iter < 150; iter++) {
    //printf("%.10f %.10f\n", l, r);
    double mid = (l + r) / 2;
    if (solve(mid) < mid) {
      r = mid;
    } else {
      l = mid;
    }
  }
  printf("%.15f\n", r);
  return 0;
}
