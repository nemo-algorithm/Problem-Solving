//루머
#include<bits/stdc++.h>
using namespace std;
using ll = long long;
int N, M, ipt;
int cnt[1<<18], ans[1<<18];
vector<int> G[1<<18];
queue<int> q;
int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    cin>>N;
    memset(ans, -1, sizeof(ans));
    for(int i=1; i<=N; i++){
        while(1){
            cin>>ipt;
            if(ipt == 0) break;
            G[i].push_back(ipt);
        }
    }
    cin>>M;
    for(int i=1; i<=M; i++) {
        cin>>ipt; q.push(ipt); ans[ipt] = 0;
    }
    while(!q.empty()){
        int now = q.front(); q.pop();
        for(int i : G[now]) {
            if(ans[i]<0) {
                cnt[i] ++;
                if(cnt[i] * 2 >= G[i].size()) {
                    q.push(i);
                    ans[i] = ans[now] + 1;
                }
            }
        }
    }
    for(int i=1; i<=N; i++) cout<<ans[i]<<' ';
}