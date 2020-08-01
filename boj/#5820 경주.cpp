#include <bits/stdc++.h>
using namespace std;
using ll = long long;
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
        for(pair<int, ll> i:G[a]) {
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
                             par[par[i][j-1].first][j-1].second + par[i][j-1].second};
            }
        }
    }
    pair<ll, int> query(int a, int b) {
        ll ret = 0, ret2 = 0;
        if(dep[a]<dep[b]) swap(a, b);
        for(int i=tn-1; i>=0; i--)
            if(dep[a] - dep[b] >= (1<<i))
                ret += par[a][i].second, a = par[a][i].first, ret2 += (1<<i);
        if(a == b) return {ret, ret2 + 1};
        for(int i=tn-1; i>=0; i--)
            if(par[a][i].first != par[b][i].first)
                ret += par[a][i].second + par[b][i].second, ret2 += (1<<(i+1)),
                a = par[a][i].first, b = par[b][i].first;
        return {ret + par[a][0].second + par[b][0].second, ret2 + 3};
    }
} lca(vector<vector<pair<int, ll>>>(0));
struct CENTROID {
    explicit CENTROID(vector<vector<int>> G) : G(G) {
        n = G.size() - 1; if(n < 1) return;
        centree.resize(n + 1, vector<int>(0));
        cen_par.resize(n + 1);
        cen_dep.resize(n + 1);
        sz.resize(n + 1);
        make_centree(1, 1);
    }
    int n, root;
    vector<vector<int>> G, centree;
    vector<int> cen_par, cen_dep, sz;
    int dfs(int a, int bef) {
        sz[a] = 1;
        for(int i: G[a]) {
            if(i == bef || cen_par[i]) continue;
            sz[a] += dfs(i, a);
        }
        return sz[a];
    }
    int centroid(int a, int bef, int s) { //a를 루트로 하는 트리의 센트로이드 반환
        for(int i: G[a]) {
            if(i == bef || cen_par[i]) continue;
            if(sz[i] > s) return centroid(i, a, s);
        }
        return a;
    }
    void make_centree(int a, int bef) { //a의 서브트리에 대한 센트로이드 트리 구축
        int cen = centroid(a, a, dfs(a, a) / 2);
        if(a == bef) {
            root = cen;
            cen_par[cen] = cen;
        }
        else {
            centree[cen].push_back(bef); centree[bef].push_back(cen);
            cen_dep[cen] = cen_dep[bef] + 1, cen_par[cen] = bef;
        }
        for(int i: G[cen]){
            if(i == cen_par[cen] || cen_par[i]) continue;
            make_centree(i, cen);
        }
    }
} centroid(vector<vector<int>>(0));
int N, K;
int dis[18][1<<20];
vector<vector<int>> G;
vector<vector<pair<int, ll>>> pG;
vector<pair<int, ll>> v[1<<18]; // a까지 정점 개수랑 거리
int dfs(int a, int bef, int k) {
    int ret = 1e9, j = 0, dep = centroid.cen_dep[a];
    for(int i: centroid.centree[a]) {
        if(centroid.cen_dep[i] <= centroid.cen_dep[a]) continue;
        ret = min(ret, dfs(i, a, k));
        queue<pair<int, ll>> q;
        for(; j<v[a].size(); j++) {
            pair<int, ll> now = v[a][j];
            if(now.second > k);
            else if(now.second == k) ret = min(ret, now.first);
            else {
                if(dis[dep][k - now.second] != 0) ret = min(ret, now.first + dis[dep][k - now.second]);
                q.push(now);
            }
        }
        while(!q.empty()) {
            pair<int, ll> now = q.front(); q.pop();
            if(dis[dep][now.second] == 0) dis[dep][now.second] = now.first;
            else dis[dep][now.second] = min(dis[dep][now.second], now.first);
        }
    }
    for(j=0; j<v[a].size(); j++) if(v[a][j].second <= k) dis[dep][v[a][j].second] = 0;
    for(j=a; j!=centroid.cen_par[j]; j=centroid.cen_par[j]) {
        int par = centroid.cen_par[j];
        pair<ll, int> p = lca.query(a, par); // 거리, 개수
        if(p.first > k);
        else v[par].emplace_back(p.second-1, p.first); // 개수, 거리
    }
    //vector<pair<int, ll>>().swap(v[a]);
    return ret;
}
int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    cin>>N>>K; G.resize(N+1); pG.resize(N+1);
    for(int i=1; i<N; i++) {
        int a, b; ll c; cin>>a>>b>>c; a++; b++;
        G[a].push_back(b); G[b].push_back(a);
        pG[a].push_back({b, c}); pG[b].push_back({a, c});
    }
    lca = LCA(pG);
    centroid = CENTROID(G);
    int ans = dfs(centroid.root, centroid.root, K);
    if(ans == 1e9) cout<<-1;
    else cout<<ans;
}