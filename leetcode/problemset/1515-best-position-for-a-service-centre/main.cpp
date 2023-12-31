#include <bits/stdc++.h>
using namespace std;

/**
 * problem 1515-best-position-for-a-service-centre (1/1)
 * leetcode, problemset
 * author: @shamir0xe
 * generated by contest-builder
 * https://github.com/shamir0xe/contest-builder
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
int n;
typedef complex<double> point;

// define functions here

class Solution {
  public:
    double getMinDistSum(vector<vector<int>> &positions) {
        point fermat(0, 0);
        vector <point> points;
        int n = sz(positions);
        if (n == 1) return 0;
        for (vi &p: positions) {
            point cur(p[0], p[1]);
            fermat += cur;
            points.push_back(cur);
        }
        fermat *= 1. / n;
        trace(fermat);
        point fermat_prim(random() * 100, random() * 100);
        while (fabs(norm(fermat - fermat_prim)) > EPS) {
            fermat_prim = fermat;
            point cur(0, 0);
            double nom[2], denom;
            nom[0] = nom[1] = denom = 0;
            for (point &p: points) {
                double ai = abs(p - fermat);
                nom[0] += p.real() * 1/ai;
                nom[1] += p.imag() * 1/ai;
                denom += 1./ai;
            }
            fermat = point(nom[0] * 1. / denom, nom[1] * 1. / denom);
        }
        double ans = 0;
        for (point &p: points) {
            ans += abs(fermat - p);
        }
        return ans;
    }
};

int read_input() {
    cin >> n;
    return 0;
}

auto solve() {
    /**
     * main logic goes here
     **/
    Solution solution = Solution();
    auto ans = solution.assert_yellow("Hello");
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
