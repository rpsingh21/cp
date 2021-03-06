/*

Our shadows stretch out on the pavement
As I walk in the twilight with you
If we could be together like this forever
Holding hands
It's almost enough to make me cry

The wind grows colder
I can smell winter
Soon the season will come to this town
When I can get close to you

This moment
When the two of us cuddle up
To gaze at the first snow flower of the year
Is overflowing with happiness

It's not dependence or weakness
I just love you
I thought so with all my heart

I feel like when I'm with you
I can overcome anything
I pray that these days
Will continue forever

The wind rattled the window
The night shakes you awake
I will change any sorrow
Into a smile

The snow flowers fell
Outside the window
Unceasing
And colored our town
I realized that love means
Wanting to do something
For someone else

If I should lose you
I'll become a star and shine on you
I'll be with you even on nights
When your smile is wet with tears

This moment
When the two of us cuddle up
To gaze at the first snow flower of the year
Is overflowing with happiness

It's not dependence or weakness
I just want to be like this
With you forever
I can honestly think that now

The pure white snow flowers
Bury this town
Softly drawing memories in our hearts
Together forever with you...

*/

#include <bits/stdc++.h>

using namespace std;

const int N = 35;

char s[N];
int pre[N];

int main() {
  int tc;
  scanf("%d", &tc);
  for (int tt = 1; tt <= tc; tt++) {
    int d;
    scanf("%d %s", &d, s);
    int n = strlen(s);
    int now = 0; long long damage = 0;
    for (int i = 0; i < n; i++) {
      if (s[i] == 'C') {
        now++;
      } else {
        damage += (1 << now);
        pre[i] = now;
      }
    }
    int ans = 0;
    while (damage > d) {
      bool ada = 0;
      for (int i = n - 1; i >= 1; i--) {
        if (s[i - 1] == 'C' && s[i] == 'S') {
          ada = 1;
          ans++;
          damage -= (1 << pre[i]);
          pre[i]--;
          damage += (1 << pre[i]);
          swap(pre[i], pre[i-1]);
          swap(s[i], s[i-1]);
          break;
        }
      }
      if (!ada) break;
    }
    printf("Case #%d: ", tt);
    if (d < damage) {
      puts("IMPOSSIBLE");
    } else {
      printf("%d\n", ans);
    }
  }

  return 0;
}
