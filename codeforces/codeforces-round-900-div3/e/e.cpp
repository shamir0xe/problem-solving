#include <bits/stdc++.h>
#include <cassert>
#include <functional>
using namespace std;

/**
 * generated template for competetive programming
 * problem E (5/7)
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

namespace atcoder {

namespace internal {

#if __cplusplus >= 202002L

using std::bit_ceil;

#else

// @return same with std::bit::bit_ceil
unsigned int bit_ceil(unsigned int n) {
    unsigned int x = 1;
    while (x < (unsigned int)(n))
        x *= 2;
    return x;
}

#endif

// @param n `1 <= n`
// @return same with std::bit::countr_zero
int countr_zero(unsigned int n) {
#ifdef _MSC_VER
    unsigned long index;
    _BitScanForward(&index, n);
    return index;
#else
    return __builtin_ctz(n);
#endif
}

// @param n `1 <= n`
// @return same with std::bit::countr_zero
constexpr int countr_zero_constexpr(unsigned int n) {
    int x = 0;
    while (!(n & (1 << x)))
        x++;
    return x;
}

} // namespace internal

#if __cplusplus >= 201703L

template <class S, auto op, auto e> struct segtree {
    static_assert(std::is_convertible_v<decltype(op), std::function<S(S, S)>>,
                  "op must work as S(S, S)");
    static_assert(std::is_convertible_v<decltype(e), std::function<S()>>,
                  "e must work as S()");

#else

template <class S, S (*op)(S, S), S (*e)()> struct segtree {

#endif

  public:
    segtree() : segtree(0) {}
    explicit segtree(int n) : segtree(std::vector<S>(n, e())) {}
    explicit segtree(const std::vector<S> &v) : _n(int(v.size())) {
        size = (int)internal::bit_ceil((unsigned int)(_n));
        log = internal::countr_zero((unsigned int)size);
        d = std::vector<S>(2 * size, e());
        for (int i = 0; i < _n; i++)
            d[size + i] = v[i];
        for (int i = size - 1; i >= 1; i--) {
            update(i);
        }
    }

    void set(int p, S x) {
        assert(0 <= p && p < _n);
        p += size;
        d[p] = x;
        for (int i = 1; i <= log; i++)
            update(p >> i);
    }

    S get(int p) const {
        assert(0 <= p && p < _n);
        return d[p + size];
    }

    S prod(int l, int r) const {
        assert(0 <= l && l <= r && r <= _n);
        S sml = e(), smr = e();
        l += size;
        r += size;

        while (l < r) {
            if (l & 1)
                sml = op(sml, d[l++]);
            if (r & 1)
                smr = op(d[--r], smr);
            l >>= 1;
            r >>= 1;
        }
        return op(sml, smr);
    }

    S all_prod() const { return d[1]; }

    template <bool (*f)(S)> int max_right(int l) const {
        return max_right(l, [](S x) { return f(x); });
    }
    template <class F> int max_right(int l, F f) const {
        assert(0 <= l && l <= _n);
        assert(f(e()));
        if (l == _n)
            return _n;
        l += size;
        S sm = e();
        do {
            while (l % 2 == 0)
                l >>= 1;
            if (!f(op(sm, d[l]))) {
                while (l < size) {
                    l = (2 * l);
                    if (f(op(sm, d[l]))) {
                        sm = op(sm, d[l]);
                        l++;
                    }
                }
                return l - size;
            }
            sm = op(sm, d[l]);
            l++;
        } while ((l & -l) != l);
        return _n;
    }

    template <bool (*f)(S)> int min_left(int r) const {
        return min_left(r, [](S x) { return f(x); });
    }
    template <class F> int min_left(int r, F f) const {
        assert(0 <= r && r <= _n);
        assert(f(e()));
        if (r == 0)
            return 0;
        r += size;
        S sm = e();
        do {
            r--;
            while (r > 1 && (r % 2))
                r >>= 1;
            if (!f(op(d[r], sm))) {
                while (r < size) {
                    r = (2 * r + 1);
                    if (f(op(d[r], sm))) {
                        sm = op(d[r], sm);
                        r--;
                    }
                }
                return r + 1 - size;
            }
            sm = op(d[r], sm);
        } while ((r & -r) != r);
        return 0;
    }

  private:
    int _n, size, log;
    std::vector<S> d;

    void update(int k) { d[k] = op(d[2 * k], d[2 * k + 1]); }
};

} // namespace atcoder

// define variables here
#define MAX_M 15
int n;
vi arr;
int q;
vector<pii> queries;

// define functions here

int read_input() {
    cin >> n;
    arr.resize(n);
    for (int i: range(n))
        cin >> arr[i];
    cin >> q;
    queries.clear();
    for (int i: range(q)) {
        int l, k;
        cin >> l >> k;
        l--;
        queries.push_back({l, k});
    }
    return 0;
}

int bitwise_and(int a, int b) { return a & b; }
int e() { return (1 << 30) - 1; }
auto solve() {
    /**
     * main logic goes here
     **/
    atcoder::segtree < int, bitwise_and, e> seg(arr);
    vi ans;
    for (auto [l, k]: queries) {
        if (seg.get(l) < k) {
            ans.push_back(-1);
            continue;
        }
        int le = l;
        int r = n;
        while (r - le > 1) {
            int mid = (le + r) >> 1;
            int temp = seg.prod(l, mid + 1);
            // trace(r _ le _ mid _ temp);
            if (temp >= k) {
                le = mid;
            } else {
                r = mid;
            }
        }
        ans.push_back(le + 1);
    }
    return ans;
}

int second_main() {
    read_input();
    auto ans = solve();
    for (int t: ans) cout << t << ' ';
    cout << endl;
    return 0;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
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
