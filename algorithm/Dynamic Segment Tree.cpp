struct DYNAMICSEG {
    /*
     Dynamic Segment Tree이다.
     DYNAMICSEG(Q, idx_min, idx_max)를 통해 O(n lg n)에 초기화하며
     공간복잡도는 Q lg(idx_max - idx_min)이다.
     아래의 두 함수를 사용 가능하다.

     void update(int s, int d)
     : O(lg n) 인덱스 s의 값을 d로 갱신한다.

     int query(int l, int r)
     : O(lg n) l부터 r까지 구간합을 반환한다.

     update 2020-07-24 / written by nemo (nemo-algorithm AT korea.ac.kr)
    */

    DYNAMICSEG(int Q, ll idx_min, ll idx_max) : idx_min(idx_min), idx_max(idx_max) {
        ll n = 0, two_n = 1;
        while(idx_max - idx_min + 1 > two_n) {
            n++; two_n *= 2;
        }
        seg.resize(n*Q);
        tn = 0;
        seg[0] = {0, 0, 0};
        seg[++tn] = {0, 0, 0};
    }
    ll idx_min, idx_max;
    int tn;
    struct node{
        int left_node, right_node; ll req;
    };
    vector<node> seg;
    void update(int a, ll l, ll r, ll s, ll d) {
        if(l == r) {
            seg[a].req = d;
        } else {
            ll mid = (l + r) / 2;
            if(s <= mid){
                if(seg[a].left_node == 0) seg[a].left_node = ++tn;
                update(seg[a].left_node, l, mid, s, d);
            } else {
                if(seg[a].right_node == 0) seg[a].right_node = ++tn;
                update(seg[a].right_node, mid+1, r, s, d);
            }
            seg[a].req = seg[seg[a].left_node].req + seg[seg[a].right_node].req;
        }
    }
    void update(ll s, ll d) {
        return update(1, idx_min, idx_max, s, d);
    }
    ll query(int a, ll l, ll r, ll s, ll d) {
        if(d<l || r<s || a == 0) return 0;
        else if(s <= l && r <= d) return seg[a].req;
        else return query(seg[a].left_node, l, (l + r) / 2, s, d) + query(seg[a].right_node, (l + r) / 2 + 1, r, s, d);
    }
    ll query(ll s, ll d){
        return query(1, idx_min, idx_max, s, d);
    }
};