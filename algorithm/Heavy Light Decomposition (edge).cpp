struct HLD{ //edge
    /*
     edge 기준으로 HLD query를 수행한다.
     트리의 정점은 1부터 시작하도록 넣어주어야 하며, pair<int, int> 형식을 통해 간선 가중치 정보를 포함해야 한다.
     Segment Tree 구조체와 함께 선언되어야 하며
     HLD(G)를 통해 O(n)에 초기화하면
     이후 아래의 두 함수를 사용 가능하다.

     void update(int a, int s, int d)
     : O(lg n) 정점 a와 정점 s을 있는 간선의 가중치 정보를 d로 갱신한다.

     int query(int a, int s)
     : O(lg n) a부터 s까지 경로에 있는 간선을 보며 query를 수행한다.

     본 구현은 백준 온라인 저지의 #13510 트리와 쿼리 1을 해결하기 위한 간선 HLD이다.

     HLD 특성상, 구현을 수정할 일이 많은데
     수행하고자 하는 연산에 해당되는 세그먼트 트리 부분,
     어떤 세그트리(Sum/Max/Min etc)를 쓰느냐에 따라
     update 연산과 query - ret 과 관련된 부분을 수정하면 된다.

     update 2020-07-24 / written by nemo (nemo-algorithm AT korea.ac.kr)
    */

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
    void update(int a, int s, int d){ //a에서 s로 가는 간선의 가중치를 d로 바꾼다.
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
