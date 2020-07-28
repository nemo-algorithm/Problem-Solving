struct UFT{ //Rank Compression
    /*
     Rank Compression을 통해 집합을 합치는 Union Find Tree이다.
     n을 통해 O(n)에 초기화하며
     아래의 세 함수를 사용 가능하다.

     int find(int a)
     : O(lg n) a가 속한 집합의 루트를 반환한다.

     void merge(int a, int b)
     : O(n lg n) a가 속한 집합과 b가 속한 집합을 합친다.

     int size(int a)
     : O(1) a가 속한 집합의 크기를 반환한다.

     update 2020-07-28 / written by nemo (nemo-algorithm AT korea.ac.kr)
    */
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