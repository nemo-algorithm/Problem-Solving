struct SEG{
    /*
     Bottom-Up 방식의 Range Sum Segment Tree이다.
     SEG(n)를 통해 O(n lg n)에 초기화하며
     아래의 두 함수를 사용 가능하다.

     void update(int s, int d)
     : O(lg n) 인덱스 s의 값을 d로 갱신한다.

     int query(int l, int r)
     : O(lg n) l부터 r까지 구간합을 반환한다.

     int closest_min(int a)
     : O(lg n) 인덱스의 존재유무를 관리하는 seg에서만 사용 가능하며,
       a보다 작거나 같은 인덱스의 존재 유무를 반환한다. (미검증)

     update 2020-07-24 / written by nemo (nemo-algorithm AT korea.ac.kr)
    */
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
            req[i] = req[i*2] + req[i*2+1];
        }
    }
    ll query(int l, int r){
        int ret = 0;
        l += tn - 1; r += tn - 1;
        for(;l<r;l/=2, r/=2){
            if(l%2) ret += req[l++];
            if(!(r%2)) ret += req[r--];
        }
        if(l==r) ret += req[l];
        return ret;
    }
    int closest_min(int a, int s){ //s보다 작은 것 중 가장 큰 거
        if(tree[a].l == tree[a].r) {
            if(tree[a].l>s) return -1;
            return tree[a].l;
        }
        if(tree[2*a+1].req>0) {
            int ret = closest_min(2*a+1, s);
            if(ret>=0) return ret;
        }
        if(tree[2*a].l<=s && tree[2*a].req>0) return closest_min(2*a, s);
        return -1;
    }
} seg(0);