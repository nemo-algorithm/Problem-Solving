#include<bits/stdc++.h>
using namespace std;
using ll = long long;

struct ConvexHullTrick{
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

int T;
int n;
ll x[1<<17], h[1<<17], sz;
ll dp[1<<17];
string point[] = {"00", "25", "50", "75"};

int main () {
    ios_base::sync_with_stdio(0); cin.tie(0);

    cin>>T;
    while(T--) {
        cin>>n;
        CHT.init();
        sz = 1;

        for(int i=1; i<=n; i++) {
            ll x_now, h_now; cin >> x_now >> h_now;
            if(sz > 1) {
                if(h_now + x_now - x[sz - 1] <= h[sz - 1]) continue;
                while(sz > 1 && h[sz - 1] + x_now - x[sz - 1] <= h_now) sz--;
                x[sz] = x_now, h[sz] = h_now, sz++;
            }
            else x[sz] = x_now, h[sz] = h_now, sz++;
        }

        dp[0] = 0;
        CHT.push(2 * (h[1] - x[1]), dp[0] + (h[1] - x[1]) * (h[1] - x[1]));
        for(int i = 1; i < sz; i++) {
            dp[i] = CHT.f(x[i] + h[i]) + (h[i] + x[i]) * (h[i] + x[i]);
            CHT.push(2 * (h[i + 1] - x[i + 1]), dp[i] + (h[i + 1] - x[i + 1]) * (h[i + 1] - x[i + 1]));
        }
        cout << dp[sz - 1] / 4<<'.'<<point[dp[sz - 1] % 4]<<'\n';
    }
}