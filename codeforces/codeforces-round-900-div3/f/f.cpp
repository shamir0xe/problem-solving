#include <bits/stdc++.h>
using namespace std;

/**
 * generated template for competetive programming
 * problem F (6/7)
 * codeforces, codeforces-round-900-div3
 * author: @shamir0xe
 * verdict: [AC/WA/TLE/MLE]
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
int n;
vector<pii> queries;
vi primes;

// define functions here

int read_input() {
    int q;
    cin >> n >> q;
    queries.clear();
    for (int i: range(q)) {
        int t;
        int x = 0;
        cin >> t;
        if (t == 1)
            cin >> x;
        queries.push_back({t, x});
    }
    return 0;
}

map<int, int> decompose(int num) {
    map<int, int> res;
    for (int &prime: primes) {
        if (1LL * prime * prime > num)
            break;
        while (num % prime == 0) {
            res[prime]++;
            num /= prime;
        }
    }
    if (num != 1)
        res[num]++;
    // for (auto [k, v]: res) {
    //     trace(k _ v);
    // }
    return res;
}

void sieve() {
    primes = vi{2};
    const int maxn = 2 * 1000 * 1000;
    vi bl(maxn, 1);
    for (int i = 3; i < maxn; ++i) {
        if (bl[i]) {
            primes.push_back(i);
            for (int j = i + i; j < maxn; j += i) {
                bl[j] = 0;
            }
        }
    }
}

auto solve() {
    /**
     * main logic goes here
     **/
    map<int, int> factors = decompose(n);
    for (auto &[t, x]: queries) {
        if (t == 2) {
            factors = decompose(n);
            continue;
        }
        map<int, int> xf = decompose(x);
        map<int, int> divisors;
        // trace(x);
        for (auto &[key, value]: xf) {
            factors[key] += value;
        }
        for (auto &[key, value]: factors) {
            for (auto &[kk, vv]: decompose(value + 1)) {
                divisors[kk] += vv;
            }
        }
        // for (auto [k, v]: factors) {
        //     trace("fac[n]" _ k _ v);
        // }
        // trace("div");
        bool bl = true;
        for (auto &[key, value]: divisors) {
            // trace(key _ value);
            if (factors.find(key) == factors.end() || value > factors[key]) {
                bl = false;
                break;
            }
        }
        if (bl)
            cout << "YES" << endl;
        else
            cout << "NO" << endl;
    }
    cout << endl;
    return 0;
}

int second_main() {
    read_input();
    auto ans = solve();
    // cout << ans << endl;
    return 0;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    sieve();
    bool test_case = true;
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
