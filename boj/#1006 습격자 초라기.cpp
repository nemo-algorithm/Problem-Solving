#include<bits/stdc++.h>
using namespace std;

int T, N, W;
int enemy[10002][2];
int dp[10002][3];
int ans;
int init_first[4] = {0, 1, 1, 1}, init_second[4] = {0, 1, 2, 0};

int get_ans(int i) {
    if (i == 0) return dp[N][0];
    if (i == 1 && enemy[1][0] + enemy[N][0] <= W) return dp[N][2] + 1;
    if (i == 2 && enemy[1][1] + enemy[N][1] <= W) return dp[N][1] + 1;
    if (i == 3 && enemy[1][0] + enemy[N][0] <= W && enemy[1][1] + enemy[N][1] <= W) return dp[N-1][0] + 2;
    return 1e9;
}

int main () {
    cin >> T;
    while (T--) {
        cin >> N >> W;
        for (int i=1; i<=N; i++) cin >> enemy[i][0];
        for (int i=1; i<=N; i++) cin >> enemy[i][1];
        enemy[0][0] = enemy[0][1] = enemy[N+1][0] = enemy[N+1][1] = 1e9;
        ans = 1e9;

        for (int c=0; c<4; c++) {
            memset(dp, 0x3f, sizeof(dp));
            dp[init_first[c]][init_second[c]] = 0;
            for (int i=1; i<=N; i++) {
                dp[i][0] = min(dp[i][0], dp[i - 1][0] + 2);
                dp[i][1] = min(dp[i][1], dp[i - 1][0] + 1);
                dp[i][1] = min(dp[i][1], dp[i - 1][1] + 2);
                dp[i][1] = min(dp[i][1], dp[i - 1][2] + 2);
                dp[i][2] = min(dp[i][2], dp[i - 1][0] + 1);
                dp[i][2] = min(dp[i][2], dp[i - 1][1] + 2);
                dp[i][2] = min(dp[i][2], dp[i - 1][2] + 2);
                if (enemy[i][0] + enemy[i][1] <= W) dp[i][0] = min(dp[i][0], dp[i - 1][0] + 1);
                if (enemy[i][0] + enemy[i - 1][0] <= W) dp[i][1] = min(dp[i][1], dp[i - 1][2] + 1);
                if (enemy[i][1] + enemy[i - 1][1] <= W) dp[i][2] = min(dp[i][2], dp[i - 1][1] + 1);
                if (i > 1 && enemy[i][0] + enemy[i - 1][0] <= W && enemy[i][1] + enemy[i - 1][1] <= W) dp[i][0] = min(dp[i][0], dp[i - 2][0] + 2);
                dp[i][0] = min(dp[i][0], dp[i][1] + 1);
                dp[i][0] = min(dp[i][0], dp[i][2] + 1);
            }
            ans = min(ans, get_ans(c));
        }

        cout << ans << '\n';
    }
}
