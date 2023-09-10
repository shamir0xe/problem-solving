#include <bits/stdc++.h>
using namespace std;

/**
 * generated template for competetive programming
 * problem D (4/6)
 * codeforces, codeforces-round-896-div2
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
vi arr;
set<ll> pow2s;

// define functions here

int read_input() {
    cin >> n;
    arr.resize(n);
    for (int i: range(n)) {
        cin >> arr[i];
    }
    return 0;
}

pii find_pair(ll delta) {
    int rev = 0;
    if (delta < 0) {
        rev = 1;
        delta = -delta;
    }
    int j = 0;
    while ((1LL << j) <= delta) {
        ll t = delta + (1LL << j);
        if (pow2s.find(t) != pow2s.end()) {
            t = round(log(t) / log(2));
            if (rev) return {t, j};
            return {j, t};
        }
        j++;
    }
    return {-1, -1};
}

auto solve() {
    /**
     * main logic goes here
     **/
    pow2s.clear();
    for (int i: range(64)) {
        pow2s.insert(1LL << i);
    }
    ll sum = 0;
    for (int i: range(n)) {
        sum += arr[i];
    }
    if (sum % n != 0)
        return false;
    ll dest = sum / n;
    map<ll, int> total;
    vector <pii> storage; 
    for (int i: range(n)) {
        if (arr[i] != dest) {
            auto [j, k] = find_pair(arr[i] - dest);
            if (j == -1) {
                return false;
            }
            if (abs(k - j) == 1) {
                int t = min(k, j);
                storage.push_back({t, arr[i] - dest < 0 ? -1 : +1});
                continue;
            }
            if (total.find(-j) != total.end()) {
                total[-j] -= 1;
                if (total[-j] == 0)
                    total.erase(-j);
            } else {
                total[j] += 1;
            }
            if (total.find(k) != total.end()) {
                total[k] -= 1;
                if (total[k] == 0)
                    total.erase(k);
            } else {
                total[-k] += 1;
            }
        }
    }
    sort(all(storage));
    reverse(all(storage));
    for (auto [t, signed_t]: storage) {
        if (signed_t < 0) {
            // sink
            if (total.find(-t - 1) != total.end()) {
                total[-t-1] --;
                if (total[-t-1] == 0) total.erase(-t-1);
                if (total.find(t) != total.end()) {
                    total[t] --;
                    if (total[t] == 0) total.erase(t);
                } else {
                    total[-t] ++;
                }
            } else {
                if (total.find(-t) != total.end()) {
                    total[-t] --;
                    if (total[-t] == 0) total.erase(-t);
                } else {
                    total[t] ++;
                }
            }
        } else {
            // source
            if (total.find(t + 1) != total.end()) {
                total[t + 1] --;
                if (total[t + 1] == 0) total.erase(t + 1);
                if (total.find(-t) != total.end()) {
                    total[-t]--;
                    if (total[-t] == 0) total.erase(-t);
                } else {
                    total[t] ++;
                }
            } else {
                if (total.find(t) != total.end()) {
                    total[t]--;
                    if (total[t] == 0) total.erase(t);
                } else {
                    total[-t]++;
                }
            }
        }
    }
    // trace(sz(total));
    // for (auto key: total) {
    //     trace(key);
    // }
    return sz(total) == 0;
}

int second_main() {
    read_input();
    auto ans = solve();
    cout << (ans ? "YES" : "NO") << endl;
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
