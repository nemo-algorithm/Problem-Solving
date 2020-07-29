//15481 그래프와 MST
#include <bits/stdc++.h>
using namespace std;
using ll = long long;
struct UFT{ //Rank Compression
    explicit UFT(int n=0) : n(n) {
        par.resize(n+1, -1); dep.resize(n+1, 0);
    }
    int n;
    vector<int> par, dep;
    int find(int a){ return par[a]<0?a:find(par[a]); }
    void merge(int a, int b){
        int c=find(a), d=find(b);
        if(c==d) return;
        if(dep[c]<dep[d]) swap(c,d);
        par[c] += par[d]; par[d] = c;
        dep[c] = max(dep[c],dep[d]+1);
    }
    int size(int a) {
        return -par[find(a)];
    }
}uft(0);
struct LCA {
    explicit LCA(const vector<vector<pair<int, ll>>>& G) : G(G) {
            n = G.size();
            if(n > 1) {
                n--;
                tn = (int) log2(n) + 1;
                dep.resize(n + 1, 0);
                vector<vector<pair<int, ll>>>(n + 1, vector<pair<int, ll>>(tn)).swap(par);
                dfs(1, 1);
                make_sparse_table(1);
            }
    }
    int n, tn;
    vector<vector<pair<int, ll>>> G;
    vector<int> dep;
    vector<vector<pair<int, ll>>> par;
    void dfs(int a, int bef) {
        for(pair<int, ll> i: G[a]) {
            int e = i.first; ll cost = i.second;
            if(e == bef) continue;
            par[e][0] = {a, cost}; dep[e] = dep[a] + 1;
            dfs(e, a);
        }
    }
    void make_sparse_table(int root) {
        par[root][0] = {root, 0};
        for(int j=1; j<tn; j++) {
            for(int i=1; i<=n; i++) {
                par[i][j] = {par[par[i][j - 1].first][j - 1].first,
                             max(par[par[i][j-1].first][j-1].second, par[i][j-1].second)};
            }
        }
    }
    pair<int, ll> query(int a, int b) {
        ll ret = 0;
        if(dep[a]<dep[b]) swap(a, b);
        for(int i=tn-1; i>=0; i--)
            if(dep[a] - dep[b] >= (1<<i))
                ret = max(ret, par[a][i].second), a = par[a][i].first;
        if(a == b) return {a, ret};
        for(int i=tn-1; i>=0; i--)
            if(par[a][i].first != par[b][i].first)
                ret = max(ret, max(par[a][i].second, par[b][i].second)),
                a = par[a][i].first, b = par[b][i].first;
        return {par[a][0].first, max(ret, max(par[a][0].second, par[b][0].second))};
    }
}lca(vector<vector<pair<int, ll>>>(0));
struct MST {
    explicit MST(const vector<vector<pair<int, ll>>>& G) : G(G) {
            for(int i=1; i<G.size(); i++) {
                for(pair<int, ll> j: G[i]) {
                    if(i < j.first) {
                        pq.push({i, j.first, j.second});
                    }
                }
            }
            mst = vector<vector<pair<int, ll>>>(G.size());
            uft = UFT(G.size());
            if(!G.empty()) {
                sum = 0;
                kruskal();
                for(tuple<int, int, ll> e: E) {
                    int a=get<0>(e), b=get<1>(e); ll c=get<2>(e);
                    mst[a].push_back({b, c});
                    mst[b].push_back({a, c});
                }
            }
    }
    vector<vector<pair<int, ll>>> G, mst;
    vector<tuple<int, int, ll>> E;
    UFT uft;
    ll sum;
    struct cmp {
        bool operator()(tuple<int, int, ll> a, tuple<int, int, ll> b) {
            return get<2>(a) > get<2>(b);
        }
    };
    priority_queue<tuple<int, int, ll>, vector<tuple<int, int, ll>>, cmp > pq;
    void kruskal() {
        while(!pq.empty()) {
            tuple<int, int, ll> edge = pq.top(); pq.pop();
            if(uft.find(get<0>(edge)) != uft.find(get<1>(edge))) {
                uft.merge(get<0>(edge), get<1>(edge));
                E.push_back(edge);
                sum += get<2>(edge);
            }
        }
    }
}mst(vector<vector<pair<int, ll>>>(0));
int N, M;
vector<vector<pair<int, ll>>> G;
vector<tuple<int, int, ll>> E;
int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    cin>>N>>M; G.resize(N+1);
    for(int i=1; i<=M; i++){
        int a, b; ll c;
        cin>>a>>b>>c;
        G[a].push_back({b, c});
        G[b].push_back({a, c});
        E.emplace_back(a, b, c);
    }
    mst = MST(G);
    lca = LCA(mst.mst);
    for(int i=0; i<M; i++) {
        int isMST=0;
        int a=get<0>(E[i]), b=get<1>(E[i]); ll c=get<2>(E[i]);
        for(pair<int, ll> j: mst.mst[a]) {
            if(j.first == b && j.second == c) isMST = 1;
        }
        if(isMST) cout<<mst.sum<<'\n';
        else cout<<mst.sum + c - lca.query(a, b).second<<'\n';
    }
}