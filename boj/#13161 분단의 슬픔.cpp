//분단의 슬픔
#include<bits/stdc++.h>
#define INF 1e9
#define MAXV 705
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
int n, ipt;
int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    cin>>n;
    //0 source, 1 sink, 1 + i people
    for(int i=1; i<=n; i++){
        cin>>ipt;
        if(ipt == 1) add_edge(0, 1+i, INF);
        if(ipt == 2) add_edge(1+i, 1, INF);
    }
    for(int i=1; i<=n; i++){
        for(int j=1; j<=n; j++){
            cin>>ipt;
            if(i != j) add_edge(1+i, 1+j, ipt);
        }
    }
    cout<<dinic(0, 1)<<'\n';
    for(int i=1; i<=n; i++) if(darr[i+1]>=0) cout<<i<<' '; cout<<'\n';
    for(int i=1; i<=n; i++) if(darr[i+1]<0) cout<<i<<' '; cout<<'\n';
}