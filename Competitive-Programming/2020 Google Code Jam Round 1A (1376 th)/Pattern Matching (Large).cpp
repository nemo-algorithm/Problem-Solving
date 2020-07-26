#include <bits/stdc++.h>
using namespace std;
using ll = long long;
int n;
int f(int dir, int a, int b){
    if(dir==1) return b;
    else return a+1-b;
}
char mfx[10002]; int ms=-1;
//가장 긴 prefix와 가장 긴 suffix를 찾고 둘이 일치하는 지 확인.이 아니고 둘을 걍 붙이면 됨.
int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    int TC; cin>>TC;
    for(int tc=1;tc<=TC;tc++){
        int tr=1;
        cin>>n;
        char pfx[102]; int ps=-1;
        char sfx[102]; int ss=-1;
        ms=-1;
        for(int cntipt=0;cntipt<n;cntipt++){
            string ipt;
            cin>>ipt; int ilen=ipt.length();
            int ff=-1,fs=-2;
            for(int i=0;i<ilen;i++){
                if(ipt[i]=='*'){
                    ff=i;
                    break;
                }
                if(i<=ps){
                    if(ipt[i]!=pfx[i]){
                        tr=0;
                        break;
                    }
                }
                else pfx[++ps]=ipt[i];
            }
            for(int i=ilen-1;i>=0;i--){
                if(ipt[i]=='*'){
                    fs=i;
                    break;
                }
                if((ilen-i-1)<=ss){
                    if(ipt[i]!=sfx[ilen-i-1]){
                        tr=0;
                        break;
                    }
                }
                else sfx[++ss]=ipt[i];
            }
            if(ff<fs){
                for(int i=ff+1;i<fs;i++){
                    if(ipt[i]!='*')
                        mfx[++ms]=ipt[i];
                }
            }
        }
        cout<<"Case #"<<tc<<':'<<' ';
        if(tr==0){
            cout<<"*";
        }
        else{
            for(int i=0;i<=ps;i++) cout<<pfx[i];
            for(int i=0;i<=ms;i++) cout<<mfx[i];
            for(int i=ss;i>=0;i--) cout<<sfx[i];
        }
        cout<<'\n';
    }
}