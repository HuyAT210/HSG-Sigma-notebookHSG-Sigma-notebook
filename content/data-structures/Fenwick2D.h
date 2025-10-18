/**
 * Author: Icelast
 * Description: 2D RMQ on Fenwick
*/

struct Fenwick2D {
    int n, m;
    vector<vector<int>> bit;
    vector<vector<int>> f;

    Fenwick2D(int n, int m) : n(n), m(m), bit(n + 1), f(n + 1) {}

    void fakeAdd(int i0, int j0) {
        for (int i = i0; i <= n; i += i & -i) {
            for (int j = j0; j <= m; j += j & -j) {
                f[i].push_back(j);
            }
        }
    }

    void work() {
        for (int i = 1; i <= n; i++) {
            f[i].push_back(0);
            sort(f[i].begin(), f[i].end());
            f[i].resize(unique(f[i].begin(), f[i].end()) - f[i].begin());
            bit[i].resize(f[i].size(), 0);
        }
    }

    void add(int i0, int j0, int x) {
        for (int i = i0; i <= n; i += i & -i) {
            for (int j = lower_bound(f[i].begin(), f[i].end(), j0) - f[i].begin(); j < (int)f[i].size(); j += j & -j) {
                bit[i][j] += x;
            }
        }
    }

    int sum(int i0, int j0) {
        int res = 0;
        for (int i = i0; i > 0; i -= i & -i) {
            for (int j = upper_bound(f[i].begin(), f[i].end(), j0) - f[i].begin() - 1; j > 0; j -= j & -j) {
                res += bit[i][j];
            }
        }
        return res;
    }
};