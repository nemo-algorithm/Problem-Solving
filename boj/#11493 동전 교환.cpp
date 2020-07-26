//동전 교환
#include<bits/stdc++.h>
#define MAXV 1200
#define INF 1e9
#define fi first
#define se second
using namespace std;
typedef pair<int, int> pii;
using ll = long long;
struct edge{ int to, cap, cost, rev; };
vector<edge> G[MAXV];
int dis[MAXV], vst[MAXV];
pii par[MAXV];
queue<int> q;
void add_edge(int from, int to, int cap, int cost){
    G[from].push_back({to,cap,cost,(int)G[to].size()});
    G[to].push_back({from,0,-cost,(int)G[from].size()-1});
}
bool SPFA(int s,int e){
    for(int i=0;i<MAXV;i++) vst[i]=0, dis[i]=1e9;
    dis[s]=0; q.push(s); vst[s]=1;
    while(!q.empty()){
        s=q.front(); q.pop(); vst[s]=0;
        for(edge e:G[s]){
            if(e.cap>0 && dis[e.to]>dis[s]+e.cost){
                dis[e.to]=dis[s]+e.cost;
                par[e.to]={s,G[e.to][e.rev].rev};
                if(vst[e.to]==0){
                    q.push(e.to);
                    vst[e.to]=1;
                }
            }
        }
    }
    return dis[e]!=INF;
}
pii MCMF(int s, int d){
    int flow=0, cost=0;
    while(SPFA(s,d)){
        int f=INF, c=0;
        for(int i=d;i!=s;i=par[i].fi){
            edge&e=G[par[i].fi][par[i].se];
            f=min(f,e.cap);
            c+=e.cost;
        }
        flow+=f; cost+=(f*c);
        for(int i=d;i!=s;i=par[i].fi){
            edge&e=G[par[i].fi][par[i].se];
            e.cap-=f;
            G[e.to][e.rev].cap+=f;
        }
    }
    return {flow,cost};
}
int dist[501][501];
int n, m, from[501], to[501];
int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    int T;
    cin>>T;
    while(T--) {
        cin>>n>>m;
        for(int i=1; i<=n; i++) for(int j=1; j<=n; j++) dist[i][j] = INF;
        for(int i=1; i<=n; i++) {
            dist[i][i] = 0;
        }
        for(int i=1; i<=m; i++){
            int a, b;
            cin>>a>>b;
            dist[a][b] = dist[b][a] = min(dist[a][b], 1);
        }
        for(int k=1; k<=n; k++)
            for(int i=1; i<=n; i++)
                for(int j=1; j<=n; j++)
                    if(i!=j)
                        dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
        for(int i=1; i<=n; i++) cin>>to[i];
        for(int i=1; i<=n; i++) cin>>from[i];
        vector<edge> cl(0);
        for(int i=0; i<=1001; i++) G[i] = cl;
        // 0 source, 1 sink, 1 + i from, 1 + n + i to
        for(int i=1; i<=n; i++) { //from
            if(to[i] == 1) add_edge(1 + n + i, 1, 1, 0);
            if(from[i] == 0) continue;
            add_edge(0, 1 + i, 1, 0);
            for(int j=1; j<=n; j++){ //to
                if(to[j] == 0) continue;
                add_edge(1 + i, 1 + n + j, 1, dist[i][j]);
            }
        }
        pii ans = MCMF(0,1);
        cout<<ans.se<<'\n';
    }
}