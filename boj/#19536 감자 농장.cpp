//감자 농장
#include<bits/stdc++.h>
using namespace std;
using ll = long long;
struct SEG{
    SEG(int n) : n(n) {
        tn = 1;
        while(tn<n) tn *= 2;
        req.resize(tn * 2);
        for(int i=1; i<2*tn; i++) req[i] = 0;
    }
    int n, tn;
    vector<ll> req;
    void update(int s, ll d){ //s에 d넣기
        int i = tn + s - 1;
        req[i] = d;
        for(i/=2; i>=1; i/=2){
            req[i] = req[i*2] + req[i*2+1];
        }
    }
    ll query(int l, int r){
        ll ret = 0;
        l += tn - 1; r += tn - 1;
        for(;l<r;l/=2, r/=2){
            if(l%2) ret += req[l++];
            if(!(r%2)) ret += req[r--];
        }
        if(l==r) ret += req[l];
        return ret;
    }
    ll kth(ll a){
        ll ret=n,l=1,r=n,mid;
        ll p;
        while(l<=r){
            mid=(l+r)/2;
            p=query(1,mid);
            if(p>=a) ret=min(ret,mid),r=mid-1;
            else l=mid+1;
        }
        return ret;
    }
} seg(0), segl(0), segr(0), seg_rock(0);
int N, Q; ll rl = 0, rr = 0;
string s;
int arr[1<<21], rarr[1<<21];
int kth(int a){
    return lower_bound(arr, arr+N+1, a) - arr;
}
ll rock_kth(int a){
    return lower_bound(rarr, rarr+N+1, a) - rarr;
}

void process1(int ipt){ //ipt가 감자 왼쪽
    ll pl = seg.query(1,ipt), pr = seg.query(ipt, rl);
    ll ldx, rdx;
    ll p = 0, t = 0;
    if(pl < pr) { //pl < pr
        ldx = kth(1); rdx = kth(2 * pl + 1);
        p = 2 * pl + 1;
        t = 2 * (segl.query(ipt, rdx) - segl.query(ldx, ipt));
        t -= ipt;
    }
    else { // pl >= pr
        //우선 pr을 다 먹고, 그만큼 pl도 먹고 원점.
        ldx = kth(pl - pr)+1; rdx = kth(pl + pr);
        p = 2 * pr;
        if(ldx<rdx) t = 2 * (segl.query(ipt, rdx) - segl.query(ldx, ipt));
        //좌측에 pl - pr 만큼의 감자 남음
        //바위에 부딪히기
        t += (pl - pr +1) * 2 * (rl - ipt);
        //좌측 감자 먹기
        p += pl - pr;
        t += 2 * (ipt * (pl - pr) - segl.query(1, kth(pl - pr)));
        t += ipt;
    }
    cout<<p<<' '<<t<<'\n';
}
void process2(int ipt){
    ll ldx = rock_kth(seg_rock.query(1, ipt-1));
    ll rdx = rock_kth(seg_rock.query(1, ipt-1)+1);
    cout<<seg.query(ldx, rdx)<<' '<<-1<<'\n';
}
void process3(int ipt){ //ipt가 바위 오른쪽
    ll pl = seg.query(rr,ipt), pr = seg.query(ipt, N);
    ll ldx, rdx;
    ll p = 0, t = 0;
    if(pl >= pr) {
        ldx = max(rl, (ll)kth(seg.query(1,ipt) - pr)+1);
        rdx = kth(seg.query(1, N));
        p = 2 * pr;
        if(ldx<rdx) t = 2 * (segl.query(ipt, rdx) - segl.query(ldx, ipt));
        t += N + 1 - ipt;
    }
    else { // pl < pr
        //우선 pl을 다 먹고, 그만큼 pr도 먹고 원점.
        ldx = rr+1; rdx = kth(seg.query(1,ipt)+pl);
        p = 2 * pl;
        if(ldx<rdx) t = 2 * (segl.query(ipt, rdx) - segl.query(ldx, ipt));
        //우측에 pr - pl 만큼의 감자 남음
        //바위에 부딪히기
        t += 2 * (pr - pl) * (ipt - rr);
        //우측 감자 먹기
        p += pr - pl;
        t += 2 * ( (-1) * ipt * (pr - pl) + segl.query(rdx + 1, N));
        t += N - ipt + 1;
    }
    cout<<p<<' '<<t<<'\n';
}

int main(){
    ios_base::sync_with_stdio(0); cin.tie(0);
    cin>>N>>Q;
    cin>>s;
    seg = SEG(N+1); segl = SEG(N+1); segr = SEG(N+1); seg_rock = SEG(N+1);
    for(int i=0; i<N; i++) {
        if(s[i] == 'R') {
            if(rl == 0) rl = i + 1;
            rr = i+1;
            seg_rock.update(i+1, 1);
            rarr[i+1] = 1;
        }
        else if(s[i] == 'P') {
            seg.update(i+1, 1);
            segl.update(i+1, i+1);
            segr.update(i+1, N+1-i-1);
            arr[i+1] = 1;
        }
    }
    for(int i=1; i<=N; i++) arr[i] +=arr[i-1], rarr[i]+=rarr[i-1];
    //바위가 없는 경우
    if(rl == 0) {
        for(int i=1; i<=Q; i++) {
            int ipt; cin>>ipt;
            ll pl = seg.query(1,ipt), pr = seg.query(ipt, N);
            ll ldx, rdx;
            ll p = 0, t = 0;
            if(pl >= pr) {
                ldx = kth(pl - pr)+1; rdx = kth(seg.query(1, N));
                p = 2 * pr;
                t = 2 * (segl.query(ipt, rdx) - segl.query(ldx, ipt));
                t += N + 1 - ipt;
            }
            else { //pl < pr
                ldx = kth(1); rdx = kth(2 * pl + 1);
                p = 2 * pl + 1;
                t = 2 * (segl.query(ipt, rdx) - segl.query(ldx, ipt));
                t -= ipt;
            }
            cout<<p<<' '<<t<<'\n';
        }
    } else {
        for(int i=1; i<=Q; i++) {
            int ipt;
            cin>>ipt;
            if(ipt<rl) process1(ipt);
            else if (rl<=ipt && ipt<=rr) process2(ipt);
            else process3(ipt);
        }
    }
}