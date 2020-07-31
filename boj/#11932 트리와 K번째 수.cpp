//트리와 K번째 수
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

struct PST {
    explicit PST(int Q = 0, ll idx_min = -2147483648, ll idx_max = 2147483647) : idx_min(idx_min), idx_max(idx_max) {
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
    vector <node> seg;
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
    void update(ll bef, ll a, ll s, ll d){
        root[a] = a;
        update(bef, a, idx_min, idx_max, s, d);
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
    int f(int ax, int ay, int alca, int aplca, ll l, ll r, int k) {
        if(l == r) return l;
        ll val = seg[seg[ax].left_node].req + seg[seg[ay].left_node].req - seg[seg[alca].left_node].req - seg[seg[aplca].left_node].req;
        if(val >= k) return f(seg[ax].left_node, seg[ay].left_node, seg[alca].left_node, seg[aplca].left_node, l, (l + r) / 2, k);
        else return f(seg[ax].right_node, seg[ay].right_node, seg[alca].right_node, seg[aplca].right_node, (l + r) / 2 + 1, r, k - val);
    }
} pst;
pair<int, int> vertex[1<<17];
struct LCA {
    explicit LCA(const vector<vector<int>>& G) : G(G) {
        n = G.size();
        if(n > 1) {
            n--;
            tn = (int) log2(n) + 1;
            dep.resize(n + 1, 0);
            vector<vector<int>>(n + 1, vector<int>(tn)).swap(par);
            pst.update(0, 1, vertex[1].second, 1);
            dfs(1, 1);
            make_sparse_table(1);
        }
    }
    int n, tn;
    vector<vector<int>> G;
    vector<int> dep;
    vector<vector<int>> par;
    void dfs(int a, int bef) {
        for(int i: G[a]) {
            if(i == bef) continue;
            pst.update(a, i, vertex[i].second, 1);
            par[i][0] = a; dep[i] = dep[a] + 1;
            dfs(i, a);
        }
    }
    void make_sparse_table(int root) {
        par[root][0] = root;
        for(int j=1; j<tn; j++) {
            for(int i=1; i<=n; i++) {
                par[i][j] = par[par[i][j - 1]][j - 1];
            }
        }
    }
    int query(int a, int b) {
        if(dep[a]<dep[b]) swap(a, b);
        for(int i=tn-1; i>=0; i--)
            if(dep[a] - dep[b] >= (1<<i))
                a = par[a][i];
        if(a == b) return a;
        for(int i=tn-1; i>=0; i--)
            if(par[a][i] != par[b][i])
                a = par[a][i], b = par[b][i];
        return par[a][0];
    }
} lca(vector<vector<int>>(0));
int n, m;
vector<vector<int>> G;
int o2v[1<<17];
int query(int x, int y, int k) {
    int l = lca.query(x, y); int pl = lca.par[l][0];
    if(l==1 && pl == 1) pl = 0;
    return o2v[pst.f(x, y, l, pl, 1LL, n, k)];
}
int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    cin>>n>>m; G.resize(n+1);
    for(int i=1; i<=n; i++) { vertex[i].first = i; cin>>vertex[i].second; }
    sort(vertex+1, vertex+n+1, [&](pair<int, int> a, pair<int, int> b){
        return a.second < b.second;
    });
    for(int i=1; i<=n; i++) {
        o2v[i] = vertex[i].second; vertex[i].second = i;
    }
    sort(vertex+1, vertex+n+1);
    for(int i=1; i<n; i++) {
        int a, b; cin>>a>>b;
        G[a].push_back(b); G[b].push_back(a);
    }
    pst = PST(n, 1, n);
    lca = LCA(G);
    for(int i=1; i<=m; i++) {
        int x, y, k; cin>>x>>y>>k;
        cout<<query(x, y, k)<<'\n';
    }
}