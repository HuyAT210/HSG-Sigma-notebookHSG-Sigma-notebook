/**
 * Author: Ann
 * Description: RMQ with large ranges
*/

template <class Info, class Tag>
struct ImplicitLazySegmentTree {
    struct Node {
        Info info = Info();
        Tag tag = Tag();
        int ln = 0, rn = 0;
    };

    int n;
    vector<Node> nodes;

    ImplicitLazySegmentTree(int n) : n(n), nodes(2) {
        nodes[1].info.makeDefault(0, n);
    }

    void apply(int p, const Tag &t) {
        nodes[p].info.apply(t);
        nodes[p].tag.apply(t);
    }
    void pull(int p) {
        nodes[p].info = nodes[nodes[p].ln].info + nodes[nodes[p].rn].info;
    }
    void push(int p) {
        apply(nodes[p].ln, nodes[p].tag);
        apply(nodes[p].rn, nodes[p].tag);
        nodes[p].tag = Tag();
    }
    void newNode(int &aug, int l, int r)  {
        aug = nodes.size();
        nodes.push_back(nodes[0]);
        nodes.back().info.makeDefault(l, r);
    }

    template <class T>
    void modify(int i, const T &val) {
        auto dfs = [&](auto self, int p, int l, int r) -> void {
            if (l + 1 == r) {
                nodes[p].info = val;
                return;
            }
            int m = (l + r) >> 1;
            if (nodes[p].ln == 0) newNode(nodes[p].ln, l, m);
            if (nodes[p].rn == 0) newNode(nodes[p].rn, m, r);
            push(p);
            if (i < m) self(self, nodes[p].ln, l, m);
            else self(self, nodes[p].rn, m, r);
            pull(p);
        };
        dfs(dfs, 1, 0, n);
    }

    void rangeApply(int ql, int qr, const Tag &t) {
        auto dfs = [&](auto self, int p, int l, int r) -> void {
            if (r <= ql || qr <= l) return;
            if (ql <= l && r <= qr) return apply(p, t);
            int m = (l + r) >> 1;
            if (nodes[p].ln == 0) newNode(nodes[p].ln, l, m);
            if (nodes[p].rn == 0) newNode(nodes[p].rn, m, r);
            push(p);
            self(self, nodes[p].ln, l, m);
            self(self, nodes[p].rn, m, r);
            pull(p);
        };
        dfs(dfs, 1, 0, n);
    }

    Info rangeQuery(int ql, int qr) {
        Info res = Info();
        auto dfs = [&](auto self, int p, int l, int r, Tag t) -> void {
            if (r <= ql || qr <= l) return;
            if (ql <= l && r <= qr) {
                Info info = nodes[p].info;
                if (p == 0) info.makeDefault(l, r);
                info.apply(t);
                res = res + info;
                return;
            }
            int m = (l + r) >> 1;
            t.apply(nodes[p].tag);
            self(self, nodes[p].ln, l, m, t);
            self(self, nodes[p].rn, m, r, t);
        };
        dfs(dfs, 1, 0, n, Tag());
        return res;
    }

    template <class F>
    int findFirst(int ql, int qr, F &&pred) {
        Info res = Info();
        auto dfs = [&](auto self, int p, int l, int r, Tag t) -> int {
            if (r <= ql || qr <= l) return -1;
            Info info = nodes[p].info;
            if (p == 0) info.makeDefault(l, r);
            info.apply(t);
            if (ql <= l && r <= qr && !pred(info)) return -1;
            if (l + 1 == r) return l;
            int m = (l + r) >> 1;
            t.apply(nodes[p].tag);
            int get = self(self, nodes[p].ln, l, m, t);
            if (get == -1) get = self(self, nodes[p].rn, m, r, t);
            return get;
        };
        return dfs(dfs, 1, 0, n, Tag());
    }
};

struct Tag {
    void apply(const Tag &t) {
    }
};

struct Info {
    void makeDefault(int l, int r) {}
    void apply(const Tag &t) {
    }
    Info operator+(const Info &b) const {
        return {};
    }
};