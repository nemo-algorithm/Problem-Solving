//k번째 수
#include <bits/stdc++.h>
using namespace std;
using ll = long long;
struct PST {
    explicit PST(int Q = 0, ll idx_min = 0, ll idx_max = 1e9) : idx_min(idx_min), idx_max(idx_max) {
        ll n = 1, two_n = 1;
        while (idx_max - idx_min + 1 >= two_n) n++, two_n *= 2;
        root.resize(Q + 1);
        seg.resize(max(1LL, n * Q));
        q = 0, tn = Q;
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
    void update(ll i, ll s, ll d) {
        root[i] = i;
        update(i - 1, i, idx_min, idx_max, s, d);
    }
    ll query(int a, ll l, ll r, ll s, ll d) {
        if (a == 0) return 0;
        if (s <= l && r <= d) return seg[a].req;
        else if (d < l or r < s) return 0;
        else return query(seg[a].left_node, l, (l + r) / 2, s, d) + query(seg[a].right_node, (l + r) / 2 + 1, r, s, d);
    }
    ll query(int a, int s, int d) {
        return query(root[a], idx_min, idx_max, s, d);
    }
    int kth(int a, int b, ll l, ll r, int k) {
        if(l == r) return l;
        int val = seg[seg[b].left_node].req - seg[seg[a].left_node].req;
        if(val >= k) return kth(seg[a].left_node, seg[b].left_node, l, (l + r) / 2, k);
        else return kth(seg[a].right_node, seg[b].right_node, (l + r) / 2 + 1, r, k - val);
    }
    int kth(int a, int b, int k) {
        return kth(a-1, b, idx_min, idx_max, k);
    }
} pst;
int n, m;
struct st{ int val, idx, ord = 0; } arr[1<<17];
ll o2v[1<<17];

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    cin>>n>>m;
    for(int i=1; i<=n; i++) cin>>arr[i].val, arr[i].idx = i;
    sort(arr+1, arr+n+1, [&](st a, st b){
        return a.val < b.val;
    });
    for(int i=1; i<=n; i++) arr[i].ord = i, o2v[i] = arr[i].val;
    sort(arr+1, arr+n+1, [&](st a, st b){
        return a.idx < b.idx;
    });
    pst = PST(n, 1, n);
    for(int i=1; i<=n; i++) {
        pst.update(i, arr[i].ord, 1);
    }
    for(int i=1; i<=m; i++) {
        int a, b, k; cin>>a>>b>>k;
        cout<<o2v[pst.kth(a, b, k)]<<'\n';
    }
}