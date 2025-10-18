/**
 * Author: Ann
 * Description: line add min get, returns INF if no line added
*/
struct Line{
    ll a = 0, b = INF;
};
struct Lichao {
    vector<Line> L;
    vector<ll> x;
    int N, m;
    Lichao(vector<ll> dom){
        N = 1;
        x = dom;
        sort(x.begin(), x.end());
        x.resize(unique(x.begin(), x.end()) - x.begin());
        N = x.size();
        L.resize(N*4+1, Line());
    };
    bool better(Line a, Line b, ll x){
        return a.a*x + a.b < b.a*x + b.b;
    }
    void addline(int node, int low, int high, Line e){
        int mid = (low+high)/2;
        bool doml = better(e, L[node], x[low]);
        bool domm = better(e, L[node], x[mid]);
        if(domm) swap(e, L[node]);
        if(low+1 == high) return;
        if(doml != domm){
            addline(node*2, low, mid, e);
        }else{
            addline(node*2+1, mid, high, e);
        }
    }
    void add(Line e){
        addline(1, 0, N, e);
    }
    void add(int l, int r, Line e){
        auto decompose = [&](auto self, int node, int low, int high, int l, int r, Line e) -> void{
            if(low >= r || l >= high) return;
            if(low >= l && r >= high){
                addline(node, low, high, e);
                return;
            }
            int mid = (low+high)/2;
            self(self, node*2, low, mid, l, r, e);
            self(self, node*2+1, mid, high, l, r, e);
        };
        decompose(decompose, 1, 0, N, l, r, e);
    }
    ll query(ll v){
        auto query = [&](auto self, int node, int low, int high, int i) -> ll{
            ll res = L[node].a*x[i] + L[node].b;
            if(low+1 == high) return res;
            int mid = (low+high)/2;
            if(i < mid){
                return min(res, self(self, node*2, low, mid, i));
            }else{
                return min(res, self(self, node*2+1, mid, high, i));
            }
        };
        int k = lower_bound(x.begin(), x.end(), v) - x.begin();
        return query(query, 1, 0, N, k);
    }
};