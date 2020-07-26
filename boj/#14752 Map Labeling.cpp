//Map Labeling
#include <bits/stdc++.h>
#define INF 2e9
using namespace std;
using ll = long long;
int n;
struct st { int x, length; }arr[1<<15];
int dp[1<<15][2];
int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    cin>>n;
    for(int i=1;i<=n;i++) dp[i][0]=n-1, dp[i][1]=INF;
    for(int i=1;i<=n;i++) cin>>arr[i].x;
    for(int i=1;i<=n;i++) cin>>arr[i].length;
    sort(arr+1,arr+n+1,[&](st a, st b) { return a.x<b.x; });
    for(int i=1;i<=n;i++){
        int now=arr[i].x, cnt=0;
        for(int j=i+1;j<=n;j++){
            if(now<=arr[j].x && now+arr[j].length>arr[j].x) cnt++;
            dp[j][1]=min(dp[j][1],dp[i][0]-cnt);
            now += arr[j].length;
            if(now<=arr[j].x){
                dp[j][0]=min(dp[j][0],dp[i][0]-cnt-1);
            }
        }
    }
    cout<<min(dp[n][0],dp[n][1]);
}