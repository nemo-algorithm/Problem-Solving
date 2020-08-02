struct PST {
    /*
     구간합에 관한 Persistent Segment Tree이다.
     PST(Q, idx_min, idx_max)로 초기화 한 이후
     이후 아래의 세 함수를 사용할 수 있다.

     void update(ll s, ll d)
     : O(lg n) 인덱스 s의 원소를 d로 업데이트한다

     ll query(int a, int s, ll d)
     : O(lg n) a번째 update까지 진행한 이후, s부터 d까지의 구간합을 반환한다.

     update 2020-07-30 / written by nemo (nemo-algorithm AT korea.ac.kr)
    */
    explicit PST(int Q = 0, ll idx_min = 0, ll idx_max = 1e9) : idx_min(idx_min), idx_max(idx_max) {
        ll n = 1, two_n = 1;
        while (idx_max - idx_min + 1 >= two_n) n++, two_n *= 2;
        root.resize(Q + 1);
        seg.resize(max(1LL, n * Q));
        q = 0, tn = 0;
        seg[0] = {0, 0, 0};
    }
    ll idx_min, idx_max;
    int q, tn;
    struct node {
        int left_node = 0, right_node = 0; ll req = 0;
    };
    vector<int> root;
    vector<node> seg;
    void update(int bef, int a, ll l, ll r, ll s, ll d) {
        if (a == 0) return;
        if (s <= l && r <= s) seg[a].req = d;
        else {
            ll mid = (l + r) / 2;
            if (s <= mid) {
                seg[a].left_node = ++tn; seg[a].right_node = seg[bef].right_node;
                update(seg[bef].left_node, seg[a].left_node, l, mid, s, d);
            } else {
                seg[a].left_node = seg[bef].left_node; seg[a].right_node = ++tn;
                update(seg[bef].right_node, seg[a].right_node, mid + 1, r, s, d);
            }
            seg[a].req = seg[seg[a].left_node].req + seg[seg[a].right_node].req;
        }
    }
    void update(ll s, ll d) {
        root[++q] = ++tn;
        update(root[q - 1], root[q], idx_min, idx_max, s, d);
    }
    ll query(int a, ll l, ll r, ll s, ll d) {
        if (a == 0) return 0;
        if (s <= l && r <= d) return seg[a].req;
        else if (d < l or r < s) return 0;
        else return query(seg[a].left_node, l, (l + r) / 2, s, d) + query(seg[a].right_node, (l + r) / 2 + 1, r, s, d);
    }
    ll query(int a, ll s, ll d) {
        return query(root[a], idx_min, idx_max, s, d);
    }
}pst;