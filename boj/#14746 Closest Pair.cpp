//Closest Pair
#include<bits/stdc++.h>
#define INF 1e9
using ll = long long;
using namespace std;
ll n,m,c1,c2;
ll a[500005], b[500005];
ll ans=INF, cnt=0;
int main(){
    ios_base::sync_with_stdio(0); cin.tie(0);
    cin>>n>>m;
    cin>>c1>>c2;
    for(int i=1;i<=n;i++) cin>>a[i];
    for(int i=1;i<=m;i++) cin>>b[i];
    sort(a+1,a+n+1);
    sort(b+1,b+m+1);
    a[0]=b[0]=-2e9; a[n+1]=b[m+1]=2e9;

    for(int i=1;i<=n;i++){
        ll ldx, rdx, dis;
        rdx = (lower_bound(b,b+m+2,a[i])-b);
        ldx = rdx-1;

        if(ldx == 0 || ldx == m+1);
        else{
            dis = a[i]-b[ldx];
            if(dis<ans){
                ans = dis;
                cnt = 1;
            }
            else if(dis==ans) cnt++;
        }
        if(rdx==0 || rdx==m+1);
        else{
            dis = b[rdx]-a[i];
            if(dis<ans){
                ans = dis;
                cnt = 1;
            }
            else if(dis==ans) cnt++;
        }

    }
    cout<<ans+abs(c1-c2)<<' '<<cnt;
}
