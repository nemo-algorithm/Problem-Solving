struct LCA {
    /*
     G는 1부터 넘버링한 트리이며
     간선의 첫 번째 인자는 도착지, 두번째 인자는 가중치를 의미한다.

     LCA(G)를 통해 O(n lg n)에 초기화하며
     이후 아래의 함수를 사용 가능하다.

     pair<int, ll> query(int a, int b)
     : O(lg n) {LCA, a부터 b까지의 거리}를 반환한다.

     make_sparse_table에서 parent를 업데이트하는 부분과
     query에서 ret를 갱신하는 부분을 수정하면
     a부터 b까지 경로에 존재하는 간선의 최댓값 / 최솟값 쿼리 등도 처리 가능하다.

     update 2020-07-28 / written by nemo (nemo-algorithm AT korea.ac.kr)
    */
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
    pair<int, ll> query(int a, int b) {
        ll ret = 0;
        if(dep[a]<dep[b]) swap(a, b);
        for(int i=tn-1; i>=0; i--)
            if(dep[a] - dep[b] >= (1<<i))
                ret += par[a][i].second, a = par[a][i].first;
        if(a == b) return {a, ret};
        for(int i=tn-1; i>=0; i--)
            if(par[a][i].first != par[b][i].first)
                ret += par[a][i].second + par[b][i].second,
                a = par[a][i].first, b = par[b][i].first;
        return {par[a][0].first, ret + par[a][0].second + par[b][0].second};
    }
} lca(vector<vector<pair<int, ll>>>(0));