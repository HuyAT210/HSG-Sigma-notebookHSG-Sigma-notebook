#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for (int i = a; i < int(b); ++i)
#define trav(a, v) for (auto &a : v)
#define all(x) x.begin(), x.end()
#define sz(x) (int)(x).size()

typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;

#include "../../content/geometry/PolygonArea.h"
typedef Point<double> P;

#include "../../content/geometry/HalfPlane.h"

namespace sjtu {
typedef double T;
const T sEPS = 1e-8;
inline int sign(T a) { return a < -sEPS ? -1 : a > sEPS; }
struct Point {
    T x, y;
    Point() {}
    Point(T _x, T _y) : x(_x), y(_y) {}
    Point operator+(const Point &p) const { return Point(x + p.x, y + p.y); }
    Point operator-(const Point &p) const { return Point(x - p.x, y - p.y); }
    Point operator*(T d) const { return Point(x * d, y * d); }
    Point operator/(T d) const { return Point(x / d, y / d); }
    bool operator<(const Point &p) const {
        int c = sign(x - p.x);
        if (c)
            return c == -1;
        return sign(y - p.y) == -1;
    }
    T dot(const Point &p) const { return x * p.x + y * p.y; }
    T det(const Point &p) const { return x * p.y - y * p.x; }
    T alpha() const { return atan2(y, x); }
    T distTo(const Point &p) const {
        T dx = x - p.x, dy = y - p.y;
        return hypot(dx, dy);
    }
    T alphaTo(const Point &p) const {
        T dx = x - p.x, dy = y - p.y;
        return atan2(dy, dx);
    }
    // clockwise
    Point rotAlpha(const T &alpha, const Point &o = Point(0, 0)) const {
        T nx = cos(alpha) * (x - o.x) + sin(alpha) * (y - o.y);
        T ny = -sin(alpha) * (x - o.x) + cos(alpha) * (y - o.y);
        return Point(nx, ny) + o;
    }
    Point rot90() const { return Point(-y, x); }
    Point unit() { return *this / abs(); }
    void read() { scanf("%lf%lf", &x, &y); }
    T abs() { return hypot(x, y); }
    T abs2() { return x * x + y * y; }
    void write() { cout << "(" << x << "," << y << ")" << endl; }
};
#define cross(p1, p2, p3) ((p2.x - p1.x) * (p3.y - p1.y) - (p3.x - p1.x) * (p2.y - p1.y))
#define crossOp(p1, p2, p3) sign(cross(p1, p2, p3))

Point isSS(Point p1, Point p2, Point q1, Point q2) {
    T a1 = cross(q1, q2, p1), a2 = -cross(q1, q2, p2);
    return (p1 * a2 + p2 * a1) / (a1 + a2);
}
struct Border {
    Point p1, p2;
    T alpha;
    void setAlpha() { alpha = atan2(p2.y - p1.y, p2.x - p1.x); }
    void read() {
        p1.read();
        p2.read();
        setAlpha();
    }
};

int n;
const int MAX_N_BORDER = 20000 + 10;
Border border[MAX_N_BORDER];

bool operator<(const Border &a, const Border &b) {
    int c = sign(a.alpha - b.alpha);
    if (c != 0)
        return c == 1;
    return crossOp(b.p1, b.p2, a.p1) >= 0;
}

bool operator==(const Border &a, const Border &b) { return sign(a.alpha - b.alpha) == 0; }

void add(T x, T y, T nx, T ny) {
    border[n].p1 = Point(x, y);
    border[n].p2 = Point(nx, ny);
    border[n].setAlpha();
    n++;
}

Point isBorder(const Border &a, const Border &b) { return isSS(a.p1, a.p2, b.p1, b.p2); }

Border que[MAX_N_BORDER];
int qh, qt;

bool check(const Border &a, const Border &b, const Border &me) {
    Point is = isBorder(a, b);
    return crossOp(me.p1, me.p2, is) > 0;
}

void convexIntersection() {
    qh = qt = 0;
    sort(border, border + n);
    n = (int)(unique(border, border + n) - border);
    for (int i = 0; i < n; ++i) {
        Border cur = border[i];
        while (qh + 1 < qt && !check(que[qt - 2], que[qt - 1], cur))
            --qt;
        while (qh + 1 < qt && !check(que[qh], que[qh + 1], cur))
            ++qh;
        que[qt++] = cur;
    }
    while (qh + 1 < qt && !check(que[qt - 2], que[qt - 1], que[qh]))
        --qt;
    while (qh + 1 < qt && !check(que[qh], que[qh + 1], que[qt - 1]))
        ++qh;
}

T calcArea() {
    static Point ps[MAX_N_BORDER];
    int cnt = 0;

    if (qt - qh <= 2) {
        return 0;
    }

    for (int i = qh; i < qt; ++i) {
        int next = i + 1 == qt ? qh : i + 1;
        ps[cnt++] = isBorder(que[i], que[next]);
    }

    T area = 0;
    for (int i = 0; i < cnt; ++i) {
        area += ps[i].det(ps[(i + 1) % cnt]);
    }
    area /= 2;
    area = (T) fabsl(area);
    return area;
}

T halfPlaneIntersection(vector<Line> cur) {
    n = 0;
    for (auto i : cur)
        add(i[0].x, i[0].y, i[1].x, i[1].y);
    convexIntersection();
    return calcArea();
}
#undef cross
} // namespace sjtu
namespace mit {
#define eps 1e-8
typedef Point<double> P;

template <class P> pair<int, P> lineIntersection(P s1, P e1, P s2, P e2) {
    auto d = (e1 - s1).cross(e2 - s2);
    if (d == 0) // if parallel
        return {-((e1 - s1).cross(s2 - s1) == 0 || s2 == e2), P(0, 0)};
    else
        return {1, s2 - (e2 - s2) * (e1 - s1).cross(s2 - s1) / d};
}

struct Line {
    P P1, P2;
    // Right hand side of the ray P1 -> P2
    explicit Line(P a = P(), P b = P()) : P1(a), P2(b){};
    P intpo(Line y) {
        auto res = lineIntersection(P1, P2, y.P1, y.P2);
        assert(res.first == 1);
        return res.second;
    }
    P dir() { return P2 - P1; }
    bool contains(P x) { return (P2 - P1).cross(x - P1) < eps; }
    bool out(P x) { return !contains(x); }
};

template <class T> bool mycmp(Point<T> a, Point<T> b) {
    // return atan2(a.y, a.x) < atan2(b.y, b.x);
    if (a.x * b.x < 0)
        return a.x < 0;
    if (abs(a.x) < eps) {
        if (abs(b.x) < eps)
            return a.y > 0 && b.y < 0;
        if (b.x < 0)
            return a.y > 0;
        if (b.x > 0)
            return true;
    }
    if (abs(b.x) < eps) {
        if (a.x < 0)
            return b.y < 0;
        if (a.x > 0)
            return false;
    }
    return a.cross(b) > 0;
}

bool cmp(Line a, Line b) { return mycmp(a.dir(), b.dir()); }

double Intersection_Area(vector<Line> b) {
    sort(b.begin(), b.end(), cmp);
    int n = (int) b.size();
    int q = 1, h = 0, i;
    vector<Line> ca(b.size() + 10);
    for (i = 0; i < n; i++) {
        while (q < h && b[i].out(ca[h].intpo(ca[h - 1])))
            h--;
        while (q < h && b[i].out(ca[q].intpo(ca[q + 1])))
            q++;
        ca[++h] = b[i];
        if (q < h && abs(ca[h].dir().cross(ca[h - 1].dir())) < eps) {
            if (ca[h].dir().dot(ca[h - 1].dir()) > 0) {
                h--;
                if (b[i].out(ca[h].P1))
                    ca[h] = b[i];
            } else {
                // The area is either 0 or infinite.
                // If you have a bounding box, then the area is definitely 0.
                return 0;
            }
        }
    }
    while (q < h - 1 && ca[q].out(ca[h].intpo(ca[h - 1])))
        h--;
    while (q < h - 1 && ca[h].out(ca[q].intpo(ca[q + 1])))
        q++;
    // Intersection is empty. This is sometimes different from the case when
    // the intersection area is 0.
    if (h - q <= 1)
        return 0;
    ca[h + 1] = ca[q];
    vector<P> s;
    for (i = q; i <= h; i++)
        s.push_back(ca[i].intpo(ca[i + 1]));
    s.push_back(s[0]);
    // for (auto i: s) cout<<i<<' ';
    // cout<<endl;
    double ans = 0;
    for (i = 0; i < (int)s.size() - 1; i++)
        ans += s[i].cross(s[i + 1]);
    return ans / 2;
}
} // namespace mit
vector<mit::Line> convert(vector<Line> x) {
    vector<mit::Line> res;
    for (auto i : x)
        res.push_back(mit::Line(i[1], i[0]));
    return res;
}

const double INF = 100;
void addInf(vector<Line> &res, double INF = INF) {
    vector<P> infPts({P(INF, INF), P(-INF, INF), P(-INF, -INF), P(INF, -INF)});
    for (int i = 0; i < 4; i++)
        res.push_back({infPts[i], infPts[(i + 1) % 4]});
}
P randPt(int lim = INF) { return P(rand() % lim, rand() % lim); }
void test1() {
    vector<Line> t({{P(0, 0), P(5, 0)}, {P(5, -2), P(5, 2)}, {P(5, 2), P(2, 2)}, {P(0, 3), P(0, -3)}});
    auto res = halfPlaneIntersection(t);
    assert(polygonArea2(res) == 20);
    addInf(t);
    res = halfPlaneIntersection(t);
    assert(polygonArea2(res) == 20);
}
void testInf() {
    vector<Line> t({{P(0, 0), P(5, 0)}});
    addInf(t);
    auto res = halfPlaneIntersection(t);
    assert(polygonArea2(res) / (4 * INF * INF) == 1);
    t = vector<Line>({{P(0, 0), P(5, 0)}, {P(0, 0), P(0, 5)}});
    addInf(t);
    res = halfPlaneIntersection(t);
    assert(polygonArea2(res) / (2 * INF * INF) == 1);
}
void testLine() {
    vector<Line> t({{P(0, 0), P(5, 0)}, {P(5, 0), P(0, 0)}});
    addInf(t);
    auto res = halfPlaneIntersection(t);
    assert(sz(res) >= 2);
    assert(polygonArea2(res) == 0);
}
void testPoint() {
    vector<Line> t({{P(0, 0), P(5, 0)}, {P(5, 0), P(0, 0)}, {P(0, 0), P(0, 5)}, {P(0, 5), P(0, 0)}});
    addInf(t);
    auto res = halfPlaneIntersection(t);
    assert(sz(res) >= 1);
    assert(polygonArea2(res) == 0);
}
void testEmpty() {
    vector<Line> t(
        {{P(0, 0), P(5, 0)}, {P(5, 0), P(0, 0)}, {P(0, 0), P(0, 5)}, {P(0, 5), P(0, 0)}, {P(0, 2), P(5, 2)}});
    addInf(t);
    auto res = halfPlaneIntersection(t);
    assert(sz(res) == 0);
}
void testRandom() {
    auto toIntPoint = [&](P p) -> Point<int> {
        return Point<int>((int)p.x, (int)p.y);
    };
    int lim = 3;
    double mxDiff = 0;
    for (int i = 0; i < 10000000; i++) {
        vector<Line> t;
        for (int i = 0; i < 4; i++) {
            Line cand{P(0, 0), P(0, 0)};
            while (cand[0] == cand[1])
                cand = {randPt(lim), randPt(lim)};
            Point<int> s1 = toIntPoint(cand[0]);
            Point<int> e1 = toIntPoint(cand[1]);
            bool fail = false;
            for (auto j: t) {
                Point<int> s2 = toIntPoint(j[0]);
                Point<int> e2 = toIntPoint(j[1]);
                if (lineInter(s1, e1, s2, e2).first == -1) {
                    fail = false;
                    break;
                }
            }
            if (fail) {
                i--;
                continue;
            }
            t.push_back(cand);
        }
        addInf(t, lim);
        auto res = halfPlaneIntersection(t);
        double area = sjtu::halfPlaneIntersection(t);
        double resArea = abs(polygonArea2(res) / 2);
        // double resArea = mit::Intersection_Area(convert(t));
        double diff = abs(area - resArea);
        mxDiff = max(diff, mxDiff);
        if (diff > .1 || isnan(diff)) {
            cout << diff << ' ' << area << ' ' << resArea << endl;
            for (auto i : t)
                cout << i[0] << "->" << i[1] << ' ';
            cout << endl;
            for (auto i : t)
                cout << "{P" << i[0] << ","
                     << "P" << i[1] << "},";
            cout << endl;
            for (auto i : res)
                cout << i << ',';
            cout << endl;
            assert(false);
        }
    }
}
vector<P> convexHull(vector<P> pts) {
	if (sz(pts) <= 1) return pts;
	sort(all(pts));
	vector<P> h(sz(pts)+1);
	int s = 0, t = 0;
	for (int it = 2; it--; s = --t, reverse(all(pts)))
		trav(p, pts) {
			while (t >= s + 2 && h[t-2].cross(h[t-1], p) <= 0) t--;
			h[t++] = p;
		}
	return {h.begin(), h.begin() + t - (t == 2 && h[0] == h[1])};
}


int main() {
    test1();
    testInf();
    testLine();
    testPoint();
    testRandom();

    cout << "Tests passed!" << endl;
}
