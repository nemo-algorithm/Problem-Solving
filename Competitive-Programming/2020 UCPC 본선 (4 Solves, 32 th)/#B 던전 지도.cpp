#include<bits/stdc++.h>
using namespace std;
using ll = long long;
ll n, m, k;
string s[30];
string jido;
ll ans;
ll arr[30][200022];
int main(){
    ios_base::sync_with_stdio(0); cin.tie(0);
    cin>>n>>m>>k;
    for(int i=1; i<=k; i++) cin>>s[i];
    cin>>jido;
    for(int i=1; i<=k; i++) {
        int u = m;
        for(int j=m-1; j>=0; j--) {
            if(s[i][j] == 'U') u = j;
            arr[i][j] = u;
        }
    }
    ll head = m-1, tail = lower_bound(arr[jido[n-1]-'A'+1], arr[jido[n-1]-'A'+1] + m, m-1) - arr[jido[n-1]-'A'+1];
    ans += head - tail + 1;
    for(int i=n-2; i>=0; i--) {
        head = lower_bound(arr[jido[i]-'A'+1], arr[jido[i]-'A'+1]+m, head + 1) - arr[jido[i]-'A'+1]-1;
        tail = lower_bound(arr[jido[i]-'A'+1], arr[jido[i]-'A'+1]+m, tail) - arr[jido[i]-'A'+1];
        ans += head - tail + 1;
    }
    cout<<ans;
}