//Leftmost Segment
#include<bits/stdc++.h>
#define INF 1e9
using ll = long long;
using namespace std;
struct CHT{//끝이 증가하는 CHT
    struct line{
        double a,b; double f(double x){ return a*x+b; }
        int idx;
    };
    deque<line> dq;
    double inter(line a, line b){ return 1.00*(b.b-a.b)/(a.a-b.a); }
    void push(double a,double b,int idx){
        line now;
        now.a=a; now.b=b; now.idx=idx;
        for(int i=dq.size()-1;i>0;i--)
            if(inter(now,dq[i])-0.00000001<inter(dq[i],dq[i-1]))
                dq.pop_back();
            else break;

        dq.push_back(now);
    }
    int find(double k){//점 k에 해당되는 직선의 인덱스
        int l=0,r=dq.size()-1;
        while(l<r){
            int mid=(l+r)>>1;
            if(k+0.00000001<inter(dq[mid],dq[mid+1])) r=mid;
            else l=mid+1; }
        return dq[r].idx;
    }
}cht;
struct Line{
    double a, b; int idx;
    bool operator<(const Line l)const{
        if(a-0.00000001<l.a && a+0.00000001>l.a){
            return b<l.b;
        }
        return a<l.a;
    }
};
vector<Line> line;
int main(){
    ios_base::sync_with_stdio(0); cin.tie(0);
    double h,H;
    cin>>H>>h; double d=H-h;
    int n; double x,X;
    cin>>n;
    for(int i=1;i<=n;i++){
        cin>>X>>x;
        Line imsi; imsi.a=(-X+x)/d; imsi.b=-x; imsi.idx=i;
        line.push_back(imsi);
    }
    sort(line.begin(),line.end());
    for(int i=0;i<line.size();i++){
        if(i!=line.size()-1){
            if(line[i].a-0.00000001<line[i+1].a && line[i].a+0.00000001>line[i+1].a){
                continue;
            }
            cht.push(line[i].a,line[i].b,line[i].idx);
        }
        else cht.push(line[i].a,line[i].b,line[i].idx);
    }

    int q;
    cin>>q;
    while(q--){
        double ipt;
        cin>>ipt;
        cout<<cht.find(ipt-h)<<'\n';
    }
}