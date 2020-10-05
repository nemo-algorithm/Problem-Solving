struct ConvexHullTrick{
    /*
     Convex Hull Trick을 위해 직선을 관리하는 자료구조이다.
     최솟값을 구하는 자료구조이며, 최댓값을 구하고자 하는 경우
     push에 -a와 -b를 대입하고, f의 return에 - 을 붙이면 된다.
     init()을 이용해 초기화한다.

     void push(ll a, ll b)
     : 기울기가 a이며 y 절편이 b인 직선을 삽입한다.
       반드시 삽입하는 직선의 기울기는 강단조감소해야한다.

     int f(ll x)
     : x를 대입했을 때, y의 최솟값을 반환한다.

     update 2020-10-06 / written by nemo (nemo-algorithm AT korea.ac.kr)
    */
    struct line {
        ll a, b;
        ll f(ll x) const { return a * x + b; }
    };
    vector<line> lines;
    void init() {
        vector<line>().swap(lines);
    }
    double_t intersect (line a, line b) const {
        return (double_t) (b.b - a.b) / (a.a - b.a);
    }
    void push(ll a, ll b) {
        line now = {a, b};
        for(int i = lines.size() - 1; i > 0; i--) {
            if(intersect(lines[i], now) < intersect(lines[i], lines[i-1])) lines.pop_back();
            else break;
        }
        lines.push_back(now);
    }
    ll f(ll x) {
        int l = 0, r = lines.size() - 1;
        while(l < r) {
            int mid = (l + r) / 2;
            if(x < intersect(lines[mid], lines[mid+1])) r = mid;
            else l = mid + 1;
        }
        return lines[l].f(x);
    }
} CHT;