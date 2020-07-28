struct MST {
    /*
     kruskal 알고리즘을 이용해 Minimum Spanning Tree를 구한다.
     MST(G)를 통해 O(n)에 초기화하며
     이후 아래의 두 변수에 다음과 같은 값이 담긴다.

     vector<tuple<int, int, ll>> E
     : 최소 스패닝 트리
       첫 번째 인자와 두 번째 인자는 간선의 양 끝 정점을
       세 번째 인자는 간선의 가중치를 의미한다.
     vector<vector<pair<int, ll>>> mst
     : 최소 스패닝 트리
        최소 스패닝 트리를 인접리스트를 이용한
        그래프 표현 방식으로 나타낸 것이다.
     ll sum
     : 최소 스패닝 트리를 구성하는 간선의 합

     update 2020-07-28 / written by nemo (nemo-algorithm AT korea.ac.kr)
    */
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