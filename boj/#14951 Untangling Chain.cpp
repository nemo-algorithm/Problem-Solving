//Untangling Chain
#include <bits/stdc++.h>
using namespace std;
using ll = long long;
int n, dir[10001], karo = 0, sero = 0, bef = -1, now = 0;
int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    cin>>n;
    for(int i=1; i<=n; i++) { cin>>dir[i]; cin>>dir[i]; }
    for(int i=0; i<n; i++) {
        if(bef == dir[i]){
            if(now == 0){
                cout<<++karo;
                now = 1;
            } else{
                cout<<++sero;
                now = 0;
            }
        }
        else {
            cout<<1;
            if(now == 0) {
                ++karo;
                now = 1;
            }
            else {
                ++sero;
                now = 0;
            }
        }
        cout<<' ';
        bef = dir[i];
    }
}