//Awkward Group
#include <bits/stdc++.h>
using namespace std;
using ll = long long;
int T, n;
struct edge{ int from, to, cost; };
struct cmp{
    bool operator()(edge a, edge b){
        return a.cost>b.cost;
    }
};
struct UFT{
    int par[1001], ecnt[1001];
    void init(int n){ for(int i=1;i<=n;i++) par[i] = -1, ecnt[i]=0; }
    int find(int a){ return par[a]<0?a:(par[a]=find(par[a])); }
    void merge(int a, int b) {
        int c=find(a), d=find(b);
        if(c!=d) par[c] += par[d], par[d] = c, ecnt[c]+=ecnt[d];
        ecnt[c]++;
    }
    int sz(int a){ a=find(a); return -par[a]; }
    int e(int a){ a=find(a); return ecnt[a]; }
}uft;
int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    cin>>T;
    while(T--){
        cin>>n;
        int ans=0;
        uft.init(n);
        priority_queue<edge, vector<edge>, cmp> pq;
        for(int i=1;i<n;i++){
            for(int j=i+1;j<=n;j++){
                int cost;
                cin>>cost;
                pq.push({i,j,cost});
            }
        }
        queue<int> q;
        set<int> s;
        while(!pq.empty()){
            edge e = pq.top(); pq.pop();
            uft.merge(e.from, e.to);
            q.push(e.from);
            if(!pq.empty()&&e.cost == pq.top().cost) continue;
            while(!q.empty()){
                int a = q.front(); q.pop(); a=uft.find(a);
                s.insert(a);
            }
            for (set<int>::iterator iter = s.begin(); iter != s.end(); ++iter){
                int a = *iter;
                int sz = uft.sz(a);
                if(sz*(sz-1)/2 == uft.e(a)) ans++;
            }
            s.clear();
        }
        cout<<ans-1<<'\n';
    }
}