/**
 * Author: Icelast
 * Description: Check bipartite online
 */

int ans; // number of bipartite component
struct DSU{
    vector<pair<int&, int>> his; // cool history style from jiangly

    int n;
    vector<int> pa, sz, g, bip;
    //g[] is parity of distance to parent in DSU
    //bip[] is bipartite or not
    DSU(int n_) : n(n_){
        pa.resize(n+1, -1);
        sz.resize(n+1, 1);
        bip.resize(n+1, 1);
        g.resize(n+1, 0);
    }

    pair<int, int> find(int x){
        if(pa[x] == -1){
            return {x, 0};
        }
        auto it = find(pa[x]);
        int p = it.first, w = it.second;
        return {p, w ^ g[x]};
    }

    void set(int &a, int b){
        his.emplace_back(a, a);
        a = b;
    }

    void merge(int a, int b){
        auto fa = find(a);
        int u = fa.first, xa = fa.second;
        auto fb = find(b);
        int v = fb.first, xb = fb.second;
        int w = xa ^ xb ^ 1;
        if(u == v){
            if(bip[u] && w){
                set(bip[u], 0);
                ans--;
            }
            return;
        }
        if(sz[u] < sz[v]){
            swap(u, v);
        }
        ans -= bip[u];
        ans -= bip[v];
        set(bip[u], bip[u] && bip[v]);
        set(sz[u], sz[u] + sz[v]);
        set(pa[v], u);
        set(g[v], w);
        ans += bip[u];
    }

    int timeStamp(){
        return his.size();
    }

    void rollback(int t){
        while((int)his.size() > t){
            auto it = his.back();
            int& x = it.first;
            int y = it.second;
            x = y;
            his.pop_back();
        }
    }
};
// use those snippets

const int N = ?; //plane of time size
    vector<vector<array<int, 2>>> edges(4 << __lg(N));
    auto add = [&](int x, int y, array<int, 2> e) -> void{
        auto add = [&](auto self, int p, int l, int r, int x, int y, array<int, 2> e) -> void{
            if(l >= y || r <= x){
                return;
            }
            if(l >= x && r <= y){
                edges[p].push_back(e);
                return;
            }
            int m = (l + r) / 2;
            self(self, 2 * p, l, m, x, y, e);
            self(self, 2 * p + 1, m, r, x, y, e);
        };
        add(add, 1, 1, N+1, x, y, e);
    };

DSU dsu(?); // number of vertices in graph
    
    auto dfs = [&](auto dfs, int p, int l, int r) -> void{ 
        int t = dsu.timeStamp();
        int ores = ans; //rollback the global bipartite component cnt
        for(auto it : edges[p]){
            dsu.merge(it[0], it[1]);
        }
        if(r - l == 1){    //customize depend on problem
            if(k[l] % 3 != 2){
                res[l] = k[l] % 3;
            }else{
                res[l] = (n - ans) % 2 ? 2 : 1;
            }
        }else{
            int m = (l + r) / 2;
            dfs(dfs, 2 * p, l, m);
            dfs(dfs, 2 * p + 1, m, r);
        }
        ans = ores;
        dsu.rollback(t);
    };