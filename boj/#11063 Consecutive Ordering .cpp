// Consecutive Ordering
#include <bits/stdc++.h>
#define INF 1e9
using namespace std;
using ll = long long;
int n,len;
struct st { int idx, l; } arr[1<<17];
struct SEGMAX{
    int n, tn;
    struct node{
        int l,r; ll req;
    }tree[1<<19];
    void make(int a){
        if(a>=tn) return;
        make(2*a); make(2*a+1);
        tree[a].l=tree[2*a].l; tree[a].r=tree[2*a+1].r;
        tree[a].req=max(tree[2*a].req, tree[2*a+1].req);
    }
    void init(int n){
        (*this).n=n; tn=1;
        while(tn<n) tn*=2;
        for(int i=tn;i<2*tn;i++) tree[i].l=tree[i].r=i-tn+1, tree[i].req=0;
        make(1);
    }
    void update(int a, int s, ll d){
        if(s<tree[a].l || tree[a].r<s);
        else if(s<=tree[a].l && tree[a].r<=s) tree[a].req=d;
        else{
            update(2*a,s,d); update(2*a+1,s,d);
            tree[a].req=max(tree[2*a].req, tree[2*a+1].req);
        }
    }
    ll query(int a, int s, int d){
        if(d<tree[a].l || tree[a].r<s) return 0;
        else if(s<=tree[a].l && tree[a].r<=d) return tree[a].req;
        else return max(query(2*a,s,d), query(2*a+1,s,d));
    }
}segM;
struct SEGMIN{
    int n, tn;
    struct node{
        int l,r; ll req;
    }tree[1<<19];
    void make(int a){
        if(a>=tn) return;
        make(2*a); make(2*a+1);
        tree[a].l=tree[2*a].l; tree[a].r=tree[2*a+1].r;
        tree[a].req=min(tree[2*a].req, tree[2*a+1].req);
    }
    void init(int n){
        (*this).n=n; tn=1;
        while(tn<n) tn*=2;
        for(int i=tn;i<2*tn;i++) tree[i].l=tree[i].r=i-tn+1, tree[i].req=INF;
        make(1);
    }
    void update(int a, int s, ll d){
        if(s<tree[a].l || tree[a].r<s);
        else if(s<=tree[a].l && tree[a].r<=s) tree[a].req=d;
        else{
            update(2*a,s,d); update(2*a+1,s,d);
            tree[a].req=min(tree[2*a].req, tree[2*a+1].req);
        }
    }
    ll query(int a, int s, int d){
        if(d<tree[a].l || tree[a].r<s) return INF;
        else if(s<=tree[a].l && tree[a].r<=d) return tree[a].req;
        else return min(query(2*a,s,d), query(2*a+1,s,d));
    }
}segm;
int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    int T;
    cin>>T;
    while(T--) {
        cin>>n>>len;
        for(int i=1; i<=n; i++) cin>>arr[i].l;
        for(int i=1; i<=n; i++) {int a; cin>>a; arr[a].idx=i;}
        int l = 1, r = 0;
        segm.init(n); segM.init(n);
        int tr = 1;
        for(int i=1; i<=n; i++) {
            while(arr[l].l+len < arr[i].l && l<n){
                segm.update(1, arr[l].idx, INF);
                segM.update(1, arr[l].idx, 0);
                l++;
            }
            while(arr[r+1].l <= arr[i].l + len && r+1<=n){
                r++;
                segm.update(1, arr[r].idx, arr[r].idx);
                segM.update(1, arr[r].idx, arr[r].idx);
            }
            int m = segm.query(1,1,n), M = segM.query(1,1,n);
            if(M-m+1 != (r-l+1)) tr=0;
        }
        if(tr) cout<<1<<'\n';
        else cout<<-1<<'\n';
    }
}