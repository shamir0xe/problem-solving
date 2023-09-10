#include <bits/stdc++.h>
#include <iterator>
using namespace std;

/**
 * generated template for competetive programming
 * problem D (4/4)
 * leetcode, weekly-contest-362
 * author: @shamir0xe
 * verdict: [AC/WA/TLE/MLE]
 **/

typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;
typedef vector<long long> vl;
typedef vector<vector<int>> vvi;
typedef vector<vector<ll>> vvl;
#define trace(x) cout << #x << " : " << x << endl
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
string s, t;
ll k;
int mod = 1000 * 1000 * 1000 + 7;

// define functions here
inline int mul(int a, int b) { return (1LL * a * b) % mod; }
inline int add(int a, int b) { return (1LL * a + b + mod) % mod; }

class Matrix {
  public:
    int n, m;
    vvi values;
    Matrix(int n, int m) : n(n), m(m) { this->values = vvi(n, vi(m, 0)); }
    vi &operator[](int idx) { return values[idx]; }
    const vi &operator[](int idx) const { return values[idx]; }
    Matrix operator*(const Matrix &b) const {
        assert(m == b.n);
        Matrix res(n, b.m);
        for (int i: range(n)) {
            for (int j: range(b.m)) {
                res[i][j] = 0;
                for (int k: range(m)) {
                    res[i][j] = add(res[i][j], mul(values[i][k], b[k][j]));
                }
            }
        }
        return res;
    }
    Matrix operator^(ll b) const {
        assert(m == n);
        Matrix res(n, n), cur(n, n);
        for (int i: range(n)) {
            for (int j: range(n)) {
                cur[i][j] = values[i][j];
            }
            res[i][i] = 1;
        }
        while (b) {
            if (b & 1)
                res = res * cur;
            cur = cur * cur;
            b >>= 1;
        }
        return res;
    }
};

ostream &operator<<(ostream &os, Matrix const &matrix) {
    int n = matrix.n;
    int m = matrix.m;
    for (int i: range(n)) {
        for (int j: range(m)) {
            os << matrix.values[i][j] << ' ';
        }
        os << endl;
    }
    return os;
}

int fast_pow(int a, ll b) {
    int ans = 1;
    int cur = a;
    while (b) {
        if (b & 1)
            ans = mul(ans, cur);
        cur = mul(cur, cur);
        b >>= 1;
    }
    return ans;
}

class Solution {
  public:
    int numberOfWays(string s, string t, long long k) {
        int hash = 0;
        int base = 61;
        int n = sz(s);
        int dest_hash = 0;
        for (int i: range(n)) {
            hash = mul(hash, base);
            hash = add(hash, s[i] - 'a');

            dest_hash = mul(dest_hash, base);
            dest_hash = add(dest_hash, t[i] - 'a');
        }
        int alter_hash = hash;
        int divide2 = fast_pow(base, mod - 2);
        int power2 = fast_pow(base, n - 1);
        int cnt = 0;
        trace(hash);
        for (int i: range(1, n)) {
            int num = s[n - i] - 'a';
            alter_hash = add(alter_hash, -num);
            alter_hash = mul(alter_hash, divide2);
            alter_hash = add(alter_hash, mul(num, power2));
            if (alter_hash == dest_hash) {
                cnt++;
            }
        }
        Matrix T(2, 2), A(1, 2);
        A[0][1] = 1;
        T[0] = {0, 1};
        T[1] = {n - 1, n - 2};
        Matrix B = A * (T ^ (k - 1));
        trace(T);
        trace((T ^ (k - 1)));
        trace(A);
        trace(B);
        int a = B[0][0];
        int b = B[0][1];
        trace(a _ b _ cnt);
        int ans = mul(b, cnt);
        if (hash == dest_hash)
            ans = add(ans, a);
        return ans;
    }
};

int read_input() {
    cin >> s >> t >> k;
    return 0;
}

auto solve() {
    /**
     * main logic goes here
     **/
    Solution solution = Solution();
    auto ans = solution.numberOfWays(s, t, k);
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
