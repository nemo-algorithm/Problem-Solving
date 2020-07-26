//Vacation Plans
#include <bits/stdc++.h>
#define INF  1e18
using namespace std;
using ll = long long;
int p, n[4], m[4], des[4]; ll hotel[4][51];
struct edge{ int to; ll cost; };
vector<edge> G[4][51];

ll bef[4][51], now[4][51], ans=INF;

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    cin>>p;
    for(int i=1; i<=3; i++) {
        if(i <= p){
            cin>>n[i]>>m[i];
            for(int j=1; j<=n[i]; j++){ cin>>hotel[i][j]; G[i][j].push_back({j, hotel[i][j]}); }
            for(int j=1; j<=m[i]; j++){
                int a, b; ll c; cin>>a>>b>>c; G[i][a].push_back({b,c});
            }
            cin>>des[i];
        }
        else { n[i] = 1, m[i] = 0, hotel[i][1] = 0, G[i][1].push_back({1,0}); des[i] = 1; }
    }
    for(int i=1; i<=3; i++) for(int j=1; j<=50; j++) bef[i][j] = now[i][j] = INF;

    bef[1][1] = bef[2][1] = bef[3][1] = 0;
    int Day = n[1]*n[2]*n[3];
    for(int day = 0; day<Day; day++){
        for(int i=1; i<=3; i++){
            for(int j=1; j<=n[i]; j++){
                for(int k=0; k<G[i][j].size(); k++){
                    int nxt = G[i][j][k].to; ll cost = G[i][j][k].cost;
                    now[i][nxt] = min(now[i][nxt], bef[i][j] + cost);
                }
            }
        }
        ans = min(ans, now[1][des[1]] + now[2][des[2]] + now[3][des[3]]);
        for(int i=1; i<=3; i++) for(int j=1; j<=50; j++) bef[i][j] = now[i][j], now[i][j] = INF;    }
    cout<<ans;
}