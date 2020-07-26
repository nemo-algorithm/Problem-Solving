//이제 다시 시작이다.
#include <bits/stdc++.h>
#define INF 1e9
using namespace std;
using ll = long long;
ll sx,sy,ex,ey;
int Q;
using ll=long long;
ll arr[1<<22];
ll arr1[1<<22];
ll arr2[1<<22];
ll seg[1<<22],seg1[1<<22],seg2[1<<22]; int tn=1;

ll opt, x0, x1, x2;
int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    while(tn<400004) tn*=2;
    cin>>sx>>sy>>ex>>ey;
    cin>>Q;
    ll m = min(ex-sx, ey-sy), M = max(ex-sx, ey-sy);
    while(Q--){
        int a; ll b, c, v;
        cin>>a;
        if(a==1) {
            cin>>b>>c;

            for(int j=(b+c-ex-ey);j<tn;j+=(j&-j))
                seg[j]+=1LL,
                seg1[j]+=(b+c-ex-ey),
                seg2[j]+=(b+c-ex-ey)*(b+c-ex-ey);
        } else {
            cin>>v;
            opt = 0;
            x0 = x1 = x2 = 0;
            for(int j=v;j>=1;j-=(j&-j)) x0+=seg[j], x1+=seg1[j], x2+=seg2[j];
            for(int j=v-m-1;j>=1;j-=(j&-j)) x0-=seg[j], x1-=seg1[j], x2-=seg2[j];

            opt += v * v * x0 - (ll) 2 * v * x1 + x2;

            x0 = x1 = x2 = 0;
            for(int j=v-m-1;j>=1;j-=(j&-j)) x0+=seg[j], x1+=seg1[j], x2+=seg2[j];
            for(int j=v-M-1;j>=1;j-=(j&-j)) x0-=seg[j], x1-=seg1[j], x2-=seg2[j];
            opt += -(ll) m * m * x0 + (ll) 2 * v * m * x0 - (ll) 2 * m * x1;

            x0 = x1 = x2 = 0;
            for(int j=v-M-1;j>=1;j-=(j&-j)) x0+=seg[j], x1+=seg1[j], x2+=seg2[j];
            for(int j=v-M-m-1;j>=1;j-=(j&-j)) x0-=seg[j], x1-=seg1[j], x2-=seg2[j];

            opt += -(ll) m * m * x0 + (ll) 2 * v * m * x0 - (ll) 2 * m * x1 + (ll) 2 * v * x1 - (ll) v * v * x0 -
                   x2 - M * M * x0 + (ll) 2 * v * M * x0 - (ll) 2 * M * x1;

            x0 = 0;
            for(int j=v-M-m-1;j>=1;j-=(j&-j)) x0+=seg[j];
            for(int j=0;j>=1;j-=(j&-j)) x0-=seg[j];
            opt += M * m * x0 * (ll) 2;

            cout<<opt<<' '<<'\n';
        }
    }
}