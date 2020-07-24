struct SCC {
    /*
     tarjan 알고리즘을 이용해 SCC를 계산한다.
     그래프의 정점은 1부터 시작하도록 넣어주어야 한다.
     SCC(G)를 통해 O(N)에 초기화하면
     그래프의 SCC를 구해 Scc에 저장하고 0부터 넘버링한다.
     이후 아래의 세 함수를 사용 가능하다.

     int get_scc_size()
     : O(1) scc의 개수를 반환한다.

     int get_scc_num(int a)
     : O(1) a가 속한 SCC의 번호를 반환한다.

     int is_same_scc(int a, int b)
     : 같은 SCC이면 1, 아니면 0을 반환한다.

     update 2020-07-24 / written by nemo (nemo-algorithm AT korea.ac.kr)
    */
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