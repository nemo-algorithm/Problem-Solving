#include<bits/stdc++.h>
#define INF 1e9
#define MAXV 305
using namespace std;
using ll = long long;
struct edge{int to, cap, rev, origin;};
//파라메트릭할 때 재활용 해야하므로, origin을 만들어 cap을 복구해준다!
vector<edge> G[MAXV];
int darr[MAXV], iter[MAXV];
void add_edge(int from, int to, int cap){
    G[from].push_back({to,cap,G[to].size(),cap});
    G[to].push_back({from,0,G[from].size()-1,0});
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
int V,E,P;
int cnt_people=0;
int main(){
    ios_base::sync_with_stdio(0); cin.tie(0);
//	ifstream fin("1.in");
	istream&in=cin;
//	ofstream of("1.out");
	ostream&out=cout;
	in>>V>>E>>P;
	// 0 source 1 sink
	// 1+i input 101+i output
	for(int i=1;i<=P;i++){ //공항
		int a; in>>a;
		add_edge(101+a,1,100000);
	}
	for(int i=1;i<=E;i++){
		int a, b; in>>a>>b;
		add_edge(101+a,1+b,100000);
		add_edge(101+b,1+a,100000);
	}
	for(int i=1;i<=V;i++){ //사람수
		int a; in>>a; cnt_people+=a;
		add_edge(0,1+i,a);
	}
	for(int i=1;i<=V;i++){ //식량
		int b; in>>b;
		add_edge(1+i,101+i,b);
	}
	for(int k=0;k<=100000;k++){
		for(int i=0;i<MAXV;i++) for(edge&e:G[i]){
			e.cap=e.origin;
			if(2<=i&&i<102&&e.to==101+i-1) e.cap+=k;
		}
		if(dinic(0,1)==cnt_people){
			out<<k; return 0;
		}
	}
}
