//격자 0 만들기
#include<bits/stdc++.h>
#define INF 1e9
#define MAXV 2700
using namespace std;
using ll = long long;
struct edge{int to, cap, rev;};
vector<edge> G[MAXV];
int darr[MAXV], iter[MAXV];
void add_edge(int from, int to, int cap){
    G[from].push_back({to,cap,G[to].size()});
    G[to].push_back({from,0,G[from].size()-1});
}
void BFS(int a){
    queue<int> q;
    q.push(a); darr[a]=0;
    while(!q.empty()){
        a=q.front(); q.pop();
        for(edge e:G[a]){
            if(e.cap>0&&darr[e.to]<0){
                darr[e.to]=darr[a]+1;
                q.push(e.to);
            }
        }
    }
}
int DFS(int s, int d, int f){
    if(s==d) return f;
    for(int&i=iter[s];i<G[s].size();i++){
        edge&e=G[s][i];
        if(e.cap>0&&darr[e.to]>darr[s]){
            int flow=DFS(e.to,d,min(f,e.cap));
            if(flow>0){
                e.cap-=flow;
                G[e.to][e.rev].cap+=flow;
                return flow;
            }
        }
    }
    return 0;
}
int dinic(int s, int d){
    int ret=0;
    while(1){
        memset(darr,-1,sizeof(darr));
        BFS(s);
        if(darr[d]<0) return ret;
        memset(iter,0,sizeof(iter));
        int f;
        while(f=DFS(s,d,INF)) ret+=f;
    }
}
int T, n, m, arr[52][52], mx[4] = {0,1,0,-1}, my[4] = {-1,0,1,0};
int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    cin>>T;
    while(T--){
        cin>>n>>m;
        memset(arr, -1, sizeof(arr));
        int sum = 0;
        for(int i=1; i<=n; i++)
            for(int j=1; j<=m; j++) {
                cin >> arr[i][j];
                sum += arr[i][j];
            }
        vector<edge> cl(0);
        for(int i=0; i<=2505; i++) G[i] = cl;
        //0 source, 1 sink, 1 + 50 * (i - 1) + j
        for(int i=1; i<=n; i++){
            for(int j=1; j<=m; j++){
                if(arr[i][j]<0 || (i+j)%2) continue;
                int idx1 = 1 + 50 * (i - 1) + j;
                add_edge(0, idx1, arr[i][j]);
                for(int k=0; k<4; k++) {
                    int ii = i + mx[k], jj = j +my[k];
                    if(arr[ii][jj]<0) continue;
                    int idx2 = 1 + 50 * (ii - 1) + jj;
                    add_edge(idx1, idx2, INF);
                }
            }
        }
        for(int i=1; i<=n; i++)
            for(int j=1; j<=m; j++){
                int idx = 1 + 50 * (i - 1) + j;
                if((i+j)%2 == 1)
                    add_edge(idx, 1, arr[i][j]);
            }
        int ans = dinic(0,1);
        cout<<ans + (sum - ans * 2)<<'\n';
    }
}