struct SEG{
    /*
     Bottom-Up 방식의 Range Sum Segment Tree이다.
     SEG(n)를 통해 O(n lg n)에 초기화하며
     아래의 두 함수를 사용 가능하다.

     void update(int s, int d)
     : O(lg n) 인덱스 s의 값을 d로 갱신한다.

     int query(int l, int r)
     : O(lg n) l부터 r까지 구간합을 반환한다.

     int lower_bound(int a)
     : O(lg n) a의 lower_bound에 대응하는 인덱스를 반환한다.
       (0, 1)의 값만 주어디는 SegTree에서는 k번째 원소의 인덱스를 반환한다.

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
    int lower_bound(ll a){
        int ret=n,l=1,r=n,mid;
        ll p;
        while(l<=r){
            mid=(l+r)/2;
            p=query(1,1,mid);
            if(p>=a) ret=min(ret,mid),r=mid-1;
            else l=mid+1;
        }
        return ret;
    }
} seg(0);