#include<bits/stdc++.h>
using namespace std;
using ll = long long;
int n, s, d;
int dep[1<<17], longest[1<<17];
vector<int> G[1<<17];
int dfs(int a, int bef){
    int ret = 0;
    for(int i:G[a]) {
        if(i != bef) {
            ret = max(ret, dfs(i, a));
        }
    }
    longest[a] = ret + 1;//자기 포함 자기에서 제일 먼거
    return ret + 1;
}
int dfs2(int a, int bef) {
    int ret = 1;
    for(int i: G[a]) {
        if(i != bef) {
            if(longest[i] <= d) continue;
            ret += dfs2(i, a);
        }
    }
    return ret;
}
int main(){
    ios_base::sync_with_stdio(0); cin.tie(0);
    cin>>n>>s>>d;
    for(int i=1; i<n; i++) {
        int a, b; cin>>a>>b;
        G[a].push_back(b); G[b].push_back(a);
    }
    dfs(s, s);
    cout<<2*(dfs2(s, s) - 1);
}