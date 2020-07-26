//사과나무
#include<bits/stdc++.h>
using namespace std;
using ll = long long;
int N, arr[1<<17], sum = 0, cnt = 0;
int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    cin>>N;
    for(int i=1; i<=N; i++) {
        cin>>arr[i];
        sum += arr[i];
        cnt += arr[i]/2;
    }
    if(sum % 3 == 0 && (sum / 3) <= cnt) {
        cout<<"YES";
    }
    else cout<<"NO";
}