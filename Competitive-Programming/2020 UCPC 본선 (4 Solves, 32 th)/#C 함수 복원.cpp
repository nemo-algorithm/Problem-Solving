#include<bits/stdc++.h>
using namespace std;
using ll = long long;
struct SCC {
    SCC(vector<vector<int>> G) : G(G) {
        N = G.size() - 1;
        g2s.resize(N+1);
        discover.resize(N+1);
        low.resize(N+1);
        vst.resize(N+1);
        vector<vector<int>>().swap(Scc);
        if(G.size() != 0) tarjan();
    }
    int N;
    vector<vector<int>> G, Scc;
    vector<int> g2s, discover, low, vst;
    int di;
    stack<int> s;
    int dfs(int a) {
        vst[a] = 1; s.push(a);
        discover[a] = low[a] = ++di;
        for(int i : G[a]){
            if(discover[i] == 0) low[a] = min(low[a], dfs(i));
            else if(vst[i] == 1) low[a] = min(low[a], discover[i]);
        }
        if(low[a] == discover[a]) {
            Scc.push_back(vector<int>(0));
            int scc_num = Scc.size() - 1;
            while(!s.empty()){
                int p = s.top(); s.pop(); vst[p] = 0;
                g2s[p] = scc_num; Scc[scc_num].push_back(p);
                if(a == p) break;
            }
        }
        return low[a];
    }
    void tarjan() {
        di = 0;
        for(int i=1; i<=N; i++) if(discover[i] == 0) dfs(i);
    }
    int get_scc_size(){ return Scc.size(); }
    int get_scc_num(int a){ return g2s[a]; }
    int is_same_scc(int a, int b){ return g2s[a] == g2s[b]? 1: 0;}
} scc(vector<vector<int> >(0));
int n;
int arr[501][501];
ll fac[501];
vector<vector<int>> G;
int main(){
    ios_base::sync_with_stdio(0); cin.tie(0);
    cin>>n; G.resize(n+1);
    int tr = 1; ll cnt = 1, mod = 1e9 + 7;
    fac[0] = fac[1] = 1;
    for(int i=2; i<=500; i++) {
        fac[i] = fac[i-1] * i;
        fac[i] %= mod;
    }
    for(int i=1; i<=n; i++) {
        for(int j=1; j<=n; j++) {
            cin>>arr[i][j];
            if(i == j) continue;
            if(arr[i][j] == 1) G[i].push_back(j);
        }
    }
    scc = SCC(G);
    for(int i=0; i<scc.Scc.size(); i++) {
        cnt *= fac[scc.Scc[i].size() - 1];
        cnt %= mod;
    }
    //scc에서 scc로 가는 정점은 없는가
    for(int i=0; i<scc.Scc.size(); i++) {
        if(scc.Scc[i].size() == 1) {
            int now = scc.Scc[i][0], scn = -1;
            for(int j: G[now]) scn = max(scn, scc.g2s[j]);
            if(scn == -1) continue;
            cnt *= scc.Scc[scn].size();
            cnt %= mod;
        }
    }
    if(tr == 1) cout<<cnt;
}