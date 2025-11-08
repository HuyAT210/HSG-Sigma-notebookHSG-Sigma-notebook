/**
 * Author: Pannda
 * Description: Weighted DSU, using heuristic approach
 * Time: O(nlogn)
 * Status: Tested
 */

const int inf = 1.1e9;
struct weightedDSU {

    vector<int> p, pr, wg;

    weightedDSU(int n) : p(n), pr(n), wg(n, inf) {
        for (int i = 0; i < n; i++) p[i] = pr[i] = i;
        mt19937 mt((size_t)make_unique<char>().get());
        shuffle(begin(pr), end(pr), mt);
    }

    int &par(int v) {
        if (p[v] == v) return p[v];
        while (wg[p[v]] <= wg[v]) p[v] = p[p[v]];
        return p[v];
    }
    int find(int v, int w = inf - 1) {
        while (wg[v] <= w) v = par(v);
        return v;
    }
    bool same(int u, int v){
        return find(u) == find(v);
    }
    void add_edge(int u, int v, int w) {
        while (u != v) {
            u = find(u, w), v = find(v, w);
            if (pr[u] < pr[v]) swap(u, v);
            swap(par(v), u), swap(wg[v], w);
        }
    }
    void delete_edge(int v) { par(v) = v, wg[v] = inf; }

    int max_edge(int u, int v) { //THIS RETURNS THE VERTEX
        if (find(u) != find(v)) return -1;
        for (;; u = par(u)) {
            if (wg[u] > wg[v]) swap(u, v);
            if (par(u) == v) return u;
        }
    }
    int max_w(int u, int v) { //THIS RETURNS THE WEIGHT
        return wg[max_edge(u, v)];
    }
    void merge(int u, int v, int w) { //main function to use
        if (u == v) return;
        int id = max_edge(u, v);
        if (id == -1) {
            add_edge(u, v, w);
        } else if (wg[id] > w) {
            delete_edge(id), add_edge(u, v, w);
        }
    }
};