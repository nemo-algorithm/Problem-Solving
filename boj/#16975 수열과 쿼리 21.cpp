//수열과 쿼리 21
#include <bits/stdc++.h>
using namespace std;
using ll = long long;
struct LAZYSEG{
    int n, tn; ll tree[1<<18], lazy[1<<18];
    void init(int n){
        (*this).n = n;
        tn=1; while(tn<n) tn*=2;
        for(int i=1;i<2*tn;i++) tree[i]=lazy[i]=0;
    }
    void propagate(int a, int s, int d){
        tree[a]+=((ll)d-(ll)s+1LL)*lazy[a];
        if(s!=d) lazy[2*a]+=lazy[a], lazy[2*a+1]+=lazy[a];
        lazy[a]=0;
    }
    void update(int a, int l, int r, int s, int d, ll x){
        propagate(a,s,d);
        if(d<l||r<s) return;
        else if(l<=s && d<=r){
            lazy[a]+=x;
            propagate(a,s,d);
        }
        else{
            update(2*a,l,r,s,(s+d)/2,x); update(2*a+1,l,r,(s+d)/2+1,d,x);
            tree[a]=tree[2*a]+tree[2*a+1];
        }
    }
    void update(int l, int r, ll x){
        update(1,l,r,1,n,x);
    }
    ll query(int a, int l, int r, int s, int d){
        propagate(a,s,d);
        if(d<l||r<s) return 0;
        else if(l<=s && d<=r) return tree[a];
        else return query(2*a,l,r,s,(s+d)/2)+query(2*a+1,l,r,(s+d)/2+1,d);
    }
    ll query(int l, int r){
        return query(1,l,r,1,n);
    }
}ls;
int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    int n; cin>>n; ls.init(n);
    for(int i=1;i<=n;i++) {int x; cin>>x; ls.update(i,i,x);}
    int m; cin>>m;
    for(int i=1;i<=m;i++) {
        int a,b,c,d;
        cin>>a;
        if(a==1){
            cin>>b>>c>>d;
            ls.update(b,c,d);
        } else {
            cin>>b;
            cout<<ls.query(b,b)<<'\n';
        }
    }
}