//Grasshopper Route
#include<bits/stdc++.h>
#define INF 1e9
using ll = long long;
using namespace std;
int n, s, t;
int vst[1<<17];
vector<int> G[1<<17];
vector<int> ans;
void route(int a){
    if(vst[a]==1) return;
    vst[a]=1; ans.push_back(a);
    for(int i=0;i<G[a].size();i++){
        int nhop = G[a][i];
        if(vst[nhop]) continue;
        vst[nhop]=1;
        for(int j=0;j<G[nhop].size();j++){
            int nxt = G[nhop][j];
            if(vst[nxt]) continue;
            route(nxt);
        }
        ans.push_back(nhop);
    }
}
vector<int> path;
int pvst[1<<17];
int path_find(int s, int e){
    if(pvst[s]) return 0;
    pvst[s] = 1;
    if(s==e) return 1;
    for(int i=0;i<G[s].size();i++){
        int nxt = G[s][i];
        if(pvst[nxt]) continue;
        if(path_find(nxt,e)){
            path.push_back(nxt);
            return 1;
        }
    }
    return 0;
}
int ps=0;
int main(){
    ios_base::sync_with_stdio(0); cin.tie(0);
    cin>>n;
    for(int i=1;i<n;i++){ int a, b; cin>>a>>b; G[a].push_back(b); G[b].push_back(a); }
    cin>>s>>t;
    path_find(s,t); reverse(path.begin(),path.end());
    int nxt = 0;
    while(s!=t){
        vst[path[nxt]]=1;

        if(path[nxt]==t){
            vst[s]=0;
            ps=s;
            route(s);
            break;
        }

        vst[s] = 1; ans.push_back(s);
        for(int i=0;i<G[s].size();i++){
            int rt = G[s][i];
            if(vst[rt]) continue;
            route(rt);
        }
        vst[path[nxt]]=0;
        s=path[nxt]; nxt++;
    }
    vst[t]=1;
    for(int i=0;i<G[t].size();i++){
        int rt = G[t][i];
        if(vst[rt]) continue;
        route(rt);
    }
    route(t);
    for(int i=0;i<ans.size();i++)
        if(ans[i]!=t)
            cout<<ans[i]<<'\n';

    cout<<t<<'\n';
}