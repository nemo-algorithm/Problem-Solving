#include <bits/stdc++.h>
using namespace std;
using ll = long long;
int n;
int f(int dir, int a, int b){
    if(dir==1) return b;
    else return a+1-b;
}
int main() {
    int TC; cin>>TC;
    for(int tc=1;tc<=TC;tc++){
        cin>>n;
        vector<int> digit;
        for(int i=0;i<=30;i++){
            if((1<<i)&n) digit.push_back(i);
        }
        cout<<"Case #"<<tc<<':'<<'\n';

        int now, after=0, bef=0, start=1, dir=1;//1이면 오른쪽으로 -1이면 왼쪽으로
        for(int i=0;i<digit.size();i++){
            now=digit[i]+1;
            //전처리
            if(now-bef>=3){
                if(now==3){
                    cout<<"1 1"<<'\n';
                    cout<<"2 1"<<'\n';
                    cout<<"3 1"<<'\n';
                    after+=1;
                    dir=-1;
                    start=4;
                }
                else{
                    for(int j=bef+1;j<=now-3;j++){
                        cout<<j<<' '<<f(dir,j,1)<<'\n';
                    }
                    cout<<now-2<<' '<<f(dir,now-2,2)<<'\n';
                    cout<<now-1<<' '<<f(dir,now-1,3)<<'\n';
                    start=4;
                    after+=now+1-(now-3-bef);
                }
            }
            else if(now-bef==2){
                cout<<now-1<<' '<<f(dir,now-1,1)<<'\n';
                start=2;
            }
            else if(now-bef==1){
                start=1;
            }

            //중간처리
            if(dir==1){
                for(int j=start;j<=now;j++)
                    cout<<now<<' '<<j<<'\n';
                dir=-1;
            }
            else if(dir==-1){
                for(int j=start;j<=now;j++)
                    cout<<now<<' '<<now+1-j<<'\n';
                dir=1;
            }

            bef=now;
        }
        //후처리
        for(int i=1;i<=after;i++){
            cout<<bef+i<<' '<<f(dir,bef+i,1)<<'\n';
        }
    }

}