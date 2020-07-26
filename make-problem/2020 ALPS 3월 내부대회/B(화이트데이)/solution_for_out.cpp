#include<bits/stdc++.h>
using namespace std;
int n, ipt[5001], arr[5001], ans;
int main(){
	int TC=50;
	for(int t=3;t<=50;t++){
//		ifstream fin(to_string(t)+".in");
		istream&in=cin;
//		ofstream of(to_string(t)+".out");
		ostream& out=cout;
		
		in>>n; ans=0;
		for(int i=1;i<=n;i++){
			in>>ipt[i];
			arr[i]=0;
		}
		for(int i=n;i>=1;i--){
			int cnt=0;
			for(int j=i;j<=n;j+=i){
				if(arr[j]) cnt++;
			}
			if(cnt==ipt[i]-1){
				arr[i]=1; ans++;
			}
		}
		out<<ans<<'\n';
		for(int i=1;i<=n;i++) if(arr[i]) out<<i<<' ';
	}
}
