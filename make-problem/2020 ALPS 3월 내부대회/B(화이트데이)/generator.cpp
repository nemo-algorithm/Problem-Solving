#include<random>
#include<chrono>
#include<bits/stdc++.h>
using namespace std;
int n, ipt[5001], arr[5001], ans;
struct st{
	int a, b;
	bool operator<(const st&x)const{
		return a<x.a;
	}
};
int main(){
	auto curTime = chrono::system_clock::now();
	auto duration = curTime.time_since_epoch();
	auto millis = chrono::duration_cast<chrono::milliseconds>(duration).count();
	mt19937 rnd(millis);
	uniform_int_distribution<int> rndm(1,300000);
	int TC=50;
	for(int t=50;t<=50;t++){
		ofstream of(to_string(t)+".in");
		ostream&out=of;

		n=rndm(rnd)%5000+1;
		out<<n<<'\n';
		ans=rndm(rnd)%n+1;
		for(int i=1;i<=n;i++) ipt[i]=arr[i]=0;
		vector<st> horangi;
		for(int j=1;j<=n;j++){
			horangi.push_back({rndm(rnd),j});
		}
		sort(horangi.begin(),horangi.end());
		for(int i=0;i<ans;i++) ipt[horangi[i].b]=1;
		for(int i=1;i<=n;i++){
			for(int j=i;j<=n;j+=i)
				if(ipt[j])
					arr[i]++;
		}
		for(int i=1;i<=n;i++) out<<arr[i]<<' ';
	}
}
