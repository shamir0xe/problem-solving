#include <bits/stdc++.h>
#include <cmath>
using namespace std;

/**
 * generated template for competetive programming
 * problem 1453-maximum-number-of-darts-inside-of-a-circular-dartboard (1/1)
 * leetcode, problemset
 * author: @shamir0xe
 * verdict: [AC]
 **/

typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;
typedef vector<long long> vl;
typedef vector<vector<int>> vvi;
typedef vector<vector<ll>> vvl;
#define trace(x) cerr << #x << " : " << x << endl
#define _ << " " <<
#define sz(x) ((int)(x).size())
#define all(x) (x).begin(), (x).end()
#define X first
#define Y second

/**
 * printing tuples
 **/
template <size_t n, typename... T>
typename enable_if<(n >= sizeof...(T))>::type
__tuple_printer(ostream &os, const tuple<T...> &tup){};

template <size_t n, typename... T>
typename enable_if<(n < sizeof...(T))>::type
__tuple_printer(ostream &os, const tuple<T...> &tup) {
    if (n != 0)
        os << " ";
    os << get<n>(tup);
    __tuple_printer<n + 1>(os, tup);
};

template <typename... T>
std::ostream &operator<<(std::ostream &os, const std::tuple<T...> &tup) {
    os << "(";
    __tuple_printer<0>(os, tup);
    os << ")";
    return os;
}

/**
 * printing pairs
 **/
template <typename T, typename K>
ostream &operator<<(std::ostream &os, const std::pair<T, K> &p) {
    os << "(" << p.first << " " << p.second << ")";
    return os;
}

/**
 * printing vectors
 **/
template <class T>
std::ostream &operator<<(std::ostream &os, const std::vector<T> &v) {
    os << "[";
    bool first = true;
    for (auto ii = v.begin(); ii != v.end(); ++ii) {
        if (first)
            first = false;
        else
            os << " ";
        os << (*ii);
    }
    os << "]";
    return os;
}

/**
 * range functions
 **/
inline vi range(int idx, int n) {
    if (n <= idx)
        return vi();
    vi indices(n - idx);
    for (int i = idx; i < n; ++i)
        indices[i - idx] = i;
    return indices;
}

inline vi range(int n) { return range(0, n); }

// define variables here
#define MAX_M 15
#define EPS 1e-9
int r;
vvi darts;

// define functions here
typedef complex<double> point;
#define x real()
#define y imag()

void smax(int &a, const int b) {
    if (a < b)
        a = b;
}

int get_center(const point &A, const point &B, double r, point &res) {
    point ab = B - A;
    point ba(ab.y, -ab.x);
    point unit = ba * (1. / abs(ba));
    // trace(unit);
    // trace(r * r);
    // trace(norm(ab * 0.5));
    if (r * r + EPS < norm(ab * 0.5)) {
        return -1;
    }
    point temp = unit * sqrt(r * r - norm(ab * 0.5));
    // trace(temp);
    res = (A + B) * 0.5 + temp;
    // trace(A _ B);
    // trace(res);
    return 0;
}

bool is_inside(const point &O, double r, const point &C) {
    return abs(O - C) < r + EPS;
}

class Solution {
  public:
    int numPoints(vector<vector<int>> &darts, int r) {
        int ans = 1;
        int n = sz(darts);
        for (int i: range(n)) {
            point A(darts[i][0], darts[i][1]);
            for (int j: range(n)) {
                if (i == j) continue;
                point B(darts[j][0], darts[j][1]);
                point O;
                if (get_center(A, B, r, O) != 0) continue;
                int cnt = 0;
                for (int k: range(n)) {
                    point C(darts[k][0], darts[k][1]);
                    cnt += is_inside(O, r, C) ? 1 : 0;
                }
                smax(ans, cnt);
            }
        }
        return ans;
    }
};

int read_input() {
    int n;
    cin >> n >> r;
    darts.clear();
    for (int i: range(n)) {
        int xx, yy;
        cin >> xx >> yy;
        darts.push_back(vi{xx, yy});
    }
    return 0;
}

auto solve() {
    /**
     * main logic goes here
     **/
    Solution solution = Solution();
    auto ans = solution.numPoints(darts, r);
    return ans;
}

int second_main() {
    read_input();
    auto ans = solve();
    cout << ans << endl;
    return 0;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    bool test_case = false;
    if (test_case) {
        int t;
        cin >> t;
        while (t--) {
            second_main();
        }
    } else {
        second_main();
    }
    return 0;
}
