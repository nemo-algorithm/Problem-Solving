//ㄷㄷㄷㅈ
#include<bits/stdc++.h>
using namespace std;
using ll = long long;
int N;
vector<int> G[1<<19];
struct st { ll one, two; }arr[1<<19];
ll du = 0, jang = 0;
void dfs(int a, int bef){
    jang += G[a].size() * (G[a].size() - 1) * (G[a].size() - 2) / 6;
    for(int i:G[a]) {
        if(i == bef) continue;
        dfs(i, a);
        arr[a].one += 1;
        arr[a].two += arr[i].one;
        du += arr[i].two;
        du -= arr[i].one;
    }
    du += arr[a].one * arr[a].two;
};
int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    cin>>N;
    for(int i=1; i<N; i++) {
        int a, b; cin>>a>>b;
        G[a].push_back(b);
        G[b].push_back(a);
    }
    dfs(1, 1);
    if(du == 3 * jang) cout<<"DUDUDUNGA";
    if(du > 3 * jang) cout<<"D";
    if(du < 3 * jang) cout<<"G";
}