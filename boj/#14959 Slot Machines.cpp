//Slot Machines
#include <bits/stdc++.h>
using namespace std;
using ll = long long;
int n, p = 0, ans;
int arr[1<<20], ak, ap, f[1<<20];
int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    cin>>n; ans = n; ak = n - 1; ap = 1;
    for(int i=n; i>=1; i--) cin>>arr[i];
    for(int i=2; i<=n; i++){
        while(arr[i] != arr[p+1] && p!=0) p = f[p];
        if(arr[i]==arr[p+1]) p++;
        f[i] = p;
        if(ans > (n - f[i])){
            ans = n - f[i];
            ak = n - i;
            ap = i - f[i];
        }
    }
    cout<<ak<<' '<<ap;
}