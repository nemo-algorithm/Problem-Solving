//트리와 쿼리 1
#include <bits/stdc++.h>
#define INF 1e9
using namespace std;
using ll = int;
struct SEG{
    SEG(int n) : n(n) {
        tn = 1;
        while(tn<n) tn *= 2;
        req.resize(tn * 2);
        for(int i=1; i<2*tn; i++) req[i] = 0;
    }
    int n, tn;
    vector<int> req;
    void update(int s, ll d){ //s에 d넣기
        int i = tn + s - 1;
        req[i] = d;
        for(i/=2; i>=1; i/=2){
            req[i] = max(req[i*2], req[i*2+1]);
        }
    }
    ll query(int l, int r){
        int ret = 0;
        l += tn - 1; r += tn - 1;
        for(;l<r;l/=2, r/=2){
            if(l%2) ret = max(ret, req[l++]);
            if(!(r%2)) ret = max(ret, req[r--]);
        }
        if(l==r) ret = max(ret, req[l]);
        return ret;
    }
} seg(0);
struct HLD{ //vertex
    HLD(vector<vector<pair<int, int>>> G) : G(G), seg(SEG(G.size()-1)){
        n = G.size() - 1;
        if(n > 0) {
            parent.resize(n + 1);
            for (int i = 1; i <= n; i++) parent[i] = i;
            sz.resize(n + 1, 0);
            dep.resize(n + 1, 0);
            i2d.resize(n + 1, -1);
            d2i.resize(n + 1, -1);
            tail.resize(n + 1, 0);
            chain.resize(n + 1, 0);
            dfs(1, 1);
            di = 0;
            hld(1, 1, 1);
        }
    }
    int n, di;
    SEG seg;
    vector<vector<pair<int, int>>> G;
    vector<int> dep, parent, sz, i2d, d2i, tail, chain;
    int dfs(int a, int bef) {
        sz[a] = 1;
        for(pair<int, int> e: G[a]) {
            int i = e.first;
            if(i == bef) continue;
            dep[i] = dep[a] + 1;
            parent[i] = a;
            sz[a] += dfs(i, a);
        }
        return sz[a];
    }
    void hld(int a, int bef, int cn){
        i2d[a] = tail[cn] = ++di; d2i[di] = a;
        chain[di] = cn;
        int idx = 0, val;
        for(pair<int, int> e: G[a]) {
            int i = e.first;
            if(i == bef) continue;
            if(sz[idx]<=sz[i]){
                idx = i; val = e.second;
            }
        }
        if(idx == 0) return;
        seg.update(di+1, val);
        hld(idx, a, cn);
        for(pair<int, int> e: G[a]) {
            int i = e.first;
            if(i != bef && i != idx) {
                seg.update(di+1, e.second);
                hld(i, a, di+1);
            }
        }
    }
    void update(int a, int s, int d){ //a에서 s로 가는 간선을 d로 바꾼다.
        if(dep[a] < dep[s]) swap(a, s);
        seg.update(i2d[a], d);
    }
    int query(int a, int s) {
        int ret = -1, da = i2d[a], ds = i2d[s];
        while(chain[da] != chain[ds]) {
            int ca = chain[da], cs = chain[ds];
            if(dep[d2i[ca]] > dep[d2i[cs]] ) ret = max(ret, seg.query(ca, da)), da = i2d[parent[d2i[ca]]];
            else ret = max(ret, seg.query(cs, ds)), ds = i2d[parent[d2i[cs]]];
        }
        //같은 체인일 경우
        if(dep[d2i[da]] > dep[d2i[ds]]) swap(da, ds);
        ret = max(ret, seg.query(da + 1, ds));
        return ret;
    }
} hld(vector<vector<pair<int, int>>>(0));

int N, M;
vector<vector<pair<int, int>>> G;
vector<pair<int, int>> ipt;
int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    cin>>N;
    G = vector<vector<pair<int, int>>>(N+1);
    ipt.push_back({0,0});
    for(int i=1; i<N; i++) {
        int a, b, c; cin>>a>>b>>c;
        G[a].push_back({b, c}); G[b].push_back({a, c});
        ipt.push_back({a, b});
    }
    hld = HLD(G);
    cin>>M;
    for(int i=1; i<=M; i++) {
        int a, b, c;
        cin>>a>>b>>c;
        if(a == 1) hld.update(ipt[b].first, ipt[b].second, c);
        else cout<<hld.query(b, c)<<'\n';
    }
}