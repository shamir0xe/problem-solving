#include <bits/stdc++.h>
using namespace std;

/**
 * generated template for competetive programming
 * problem 1361-validate-binary-tree-nodes (1/1)
 * leetcode, problemset
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
vi colors;
vi lefts, rights;

// define functions here
bool dfs(int u) {
    if (u == -1)
        return true;
    colors[u] = 1;
    int le = lefts[u];
    int ri = rights[u];
    bool res = true;
    if (le != -1 && colors[le] != 0)
        return false;
    res &= dfs(le);
    if (ri != -1 && colors[ri] != 0)
        return false;
    res &= dfs(ri);
    return res;
}

class Solution {
  public:
    bool validateBinaryTreeNodes(int n, vector<int> &leftChild,
                                 vector<int> &rightChild) {
        set<int> roots;
        trace("hallop");
        // roots.insert(all(range(n)));
        for (int i: range(n)) {
            roots.insert(i);
        }
        trace("yolo");
        for (int t: leftChild)
            if (roots.find(t) != roots.end())
                roots.erase(t);
        for (int t: rightChild)
            if (roots.find(t) != roots.end())
                roots.erase(t);
        if (sz(roots) != 1)
            return false;
        int root = *roots.begin();
        lefts = leftChild;
        rights = rightChild;
        colors.assign(n, 0);
        if (!dfs(root))
            return false;
        for (int t: colors) {
            if (t == 0)
                return false;
        }
        return true;
    }
};

int read_input() {
    cin >> n;
    lefts.resize(n);
    rights.resize(n);
    for (int i: range(n)) {
        cin >> lefts[i];
    }
    for (int i: range(n)) {
        cin >> rights[i];
    }
    return 0;
}

auto solve() {
    /**
     * main logic goes here
     **/
    Solution solution = Solution();
    auto ans = solution.validateBinaryTreeNodes(n, lefts, rights);
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
