struct CENTROID {
    /*
     트리 G에 대한 센트로이드 트리를 구축한다.
     CENTROID(G)를 통해 O(n lg n)에 초기화하며
     이후 아래의 변수에 다음과 같은 값이 담긴다.

     vector<vector<int>> centree
     : 센트로이드 트리

     vector<int> cen_par, cen_dep
     각 정점의 센트로이드 트리에서의 부모와 깊이

     update 2020-08-01 / written by nemo (nemo-algorithm AT korea.ac.kr)
    */
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