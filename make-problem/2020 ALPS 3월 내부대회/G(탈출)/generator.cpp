#include "testlib.h"

#include <iostream>
#include <sstream>
#include <fstream>
#include <iomanip>
#include <string>
//#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <ctime>
#include <climits>
#include <cassert>
#include <vector>
#include <queue>
#include <stack>
#include <deque>
#include <set>
#include <map>
#include <bitset>
#include <utility>
#include <algorithm>
#include<random>
#include<chrono>

#define forn(i, n) for (int i = 0; i < int(n); i++)

using namespace std;

//int rndm(){
//	random_device rd;
//	mt19937 rnd(rd());
//	uniform_int_distribution<int> range(0,300000);
//    return range(rnd);
//}
char filename[100];
int use1D[10001],use2D[10001][10001];
struct st{
	int rd, a, b;
	bool operator<(const st&x)const{
		return rd<x.rd;
	}
};
vector<st> makeP, vec, makeE;
int main(int argc, char* argv[]){
//	ifstream fin("2.in");
//	istream&in=fin;
	ofstream of("57.in");
	ostream&out=of;
	int V=100;
	int E=99; //V-1<E
	int P=1;
	int costMAX=1000;

	//주워온 코드 for random 
	auto current = std::chrono::system_clock::now();
	auto duration = current.time_since_epoch();
	auto millis = std::chrono::duration_cast<std::chrono::milliseconds>(duration).count();

	std::mt19937_64 genMT(millis);
	std::uniform_int_distribution<__int64> rndm(0, 30000000);
	out<<V<<' '<<E<<' '<<P<<'\n';
	out<<1<<'\n';
/*
	//줍줍 코드 for tree
	registerGen(argc, argv, 1);
	
    //make P
	for(int i=1;i<=V;i++){
		makeP.push_back({rndm(genMT),i,0});
	}
	sort(makeP.begin(),makeP.end());
	for(int i=0;i<P;i++){
		out<<makeP[i].a<<' ';
	}
	out<<'\n';
	//랜덤간선 만들기
	memset(use2D,0,sizeof(use2D));
	for(int i=1;i<=V;i++){
		for(int j=i+1;j<=V;j++){
			if(i!=j){
				int a,b,c;
				a=rndm(genMT);
				b=i; c=j;
				if(rndm(genMT)>rndm(genMT)) swap(b,c);
				vec.push_back({a,b,c}); 
			}
		}
	}
	sort(vec.begin(),vec.end());
	// 줍줍 코드 시작 
	    int n = V; //opt<int>(1);
	    int t = 1; //opt<int>(2);
		
	    vector<int> p(n);
	    forn(i, n)
	        if (i > 0)
	            p[i] = rnd.wnext(i, t);
	 
	    vector<int> perm(n);
	    forn(i, n)
	        perm[i] = i;
	    shuffle(perm.begin() + 1, perm.end());
	    vector<pair<int,int> > edges;
	
	    for (int i = 1; i < n; i++)
	        if (rnd.next(2))
	            edges.push_back(make_pair(perm[i], perm[p[i]]));
	        else
	            edges.push_back(make_pair(perm[p[i]], perm[i]));
	
	    shuffle(edges.begin(), edges.end());
	
	    for (int i = 0; i + 1 < n; i++){ 
	    	use2D[edges[i].first+1][edges[i].second+1]=1;
	    	use2D[edges[i].second+1][edges[i].first+1]=1;
	    	makeE.push_back({rndm(genMT), edges[i].first+1 ,edges[i].second+1});
		}
	//줍줍코드 끝
	for(int i=V, j=-1;i<=E;i++){
		while(1){
			j++;
			if(use2D[vec[j].a][vec[j].b]==0&&use2D[vec[j].b][vec[j].a]==0){
				use2D[vec[j].a][vec[j].b]=use2D[vec[j].b][vec[j].a]=1;
				makeE.push_back({rndm(genMT),vec[j].a,vec[j].b});
				break;
			}
		}
	}
	sort(makeE.begin(), makeE.end());
	for(int i=0;i<makeE.size();i++){
		out<<makeE[i].a<<' '<<makeE[i].b<<'\n';
	}
	//정점별 사람수 
*/
	for(int i=1;i<=E;i++) out<<i<<' '<<i+1<<'\n';
	for(int i=0;i<V;i++) out<<rndm(genMT)%(costMAX+1)<<' ';
	out<<'\n';
	
	for(int i=0;i<V;i++) out<<rndm(genMT)%(costMAX+1)<<' ';
	out<<'\n';
    
	return 0;
}
