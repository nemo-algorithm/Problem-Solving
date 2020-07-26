#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using namespace std;
ll bs(ll a, ll c){
    ll l=a, r=c, ans=-1;
    while(l<=r){
        ll mid=(l+r)/2;
        ll sm = (a+mid)*(mid-a+1)/2;
        if(sm<=c) {ans=max(ans,mid); l=mid+1;}
        else r=mid-1;
    }

    return ans;
}
int main(){
    ios_base::sync_with_stdio(0); cin.tie(0);
    int TC; cin>>TC;
    for(int tc=1;tc<=TC;tc++){
        ll a, b;
        cin>>a>>b;
        int sp=0;
        if(b>a) {swap(a,b); sp++;}
        ll nxt=1;
        ll ans=0;
        while(1){
            if(b>a) {swap(a,b); sp++;}
            if(a==b && sp%2==1){
                swap(a,b); sp++;
            }
            ll nnxt = bs(nxt,a-b);
            if(nnxt==-1);
            else a -= (nxt+nnxt)*(nnxt-nxt+1LL)/2;
            if(b>a) {swap(a,b); sp++;}
            if(a==b && sp%2==1){
                swap(a,b); sp++;
            }
            if(nnxt==-1){
                if(a-nxt>=0){
                    a-=nxt; ans=nxt;
                    nxt++;
                    continue;
                } else break;
            }
            ans=nnxt;
            nxt=nnxt+1;
            if(a-nxt<0) break;
            a-=nxt; ans=nxt; nxt++;
//            printf("n %d %d %d\n",a,b,nxt);
        }
        cout<<"Case #"<<tc<<": ";
        cout<<ans<<' ';
        if(sp%2==1) cout<<b<<' '<<a;
        else cout<<a<<' '<<b;
        cout<<'\n';
    }
}