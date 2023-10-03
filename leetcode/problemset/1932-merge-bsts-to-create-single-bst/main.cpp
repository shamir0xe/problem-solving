#include <bits/stdc++.h>
using namespace std;

/**
 * generated template for competetive programming
 * problem 1932-merge-bsts-to-create-single-bst (1/1)
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

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right)
        : val(x), left(left), right(right) {}
};

// define variables here
#define MAX_N 1000000
int n;
vector<TreeNode *> _trees;
vector<TreeNode *> trees;
TreeNode all_nodes[MAX_N];
int node_index = 0;

// define functions here
TreeNode *build_bst() {
    map<int, TreeNode *> mp, roots;
    for (TreeNode *tree: _trees) {
        // trace(tree->val);
        roots[tree->val] = tree;
        if (tree->left != nullptr) {
            mp[tree->left->val] = tree;
        }
        if (tree->right != nullptr) {
            mp[tree->right->val] = tree;
        }
    }
    bool bl = true;
    while (bl) {
        bl = false;
        // trace(sz(roots));
        if (sz(roots) == 1)
            break;
        int cnt = 0;
        for (auto &[value, root]: roots) {
            cnt++;
            if (cnt >= 3) {
                bl = false;
                break;
            }
            if (mp.find(value) == mp.end())
                continue;
            TreeNode *node = mp[value];
            // trace(root->val _ node->val);
            if (node->val > root->val) {
                node->left = root;
            } else {
                node->right = root;
            }
            mp.erase(value);
            roots.erase(value);
            bl = true;
            break;
        }
    }
    if (sz(roots) != 1)
        return nullptr;
    return roots.begin()->second;
}

int check_bst(TreeNode *root, int mini = -1e7, int maxi = 1e7) {
    if (root == nullptr)
        return 0;
    // trace(root->val);
    if (root->val >= maxi || root->val <= mini) {
        // trace(mini _ maxi);
        return -1;
    }
    int le = check_bst(root->left, mini, root->val);
    int ri = check_bst(root->right, root->val, maxi);
    if (le == -1 || ri == -1)
        return -1;
    return le + ri + 1;
}

TreeNode *make_node() { return &all_nodes[node_index++]; }

/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left),
 * right(right) {}
 * };
 */
class Solution {
  public:
    TreeNode *canMerge(vector<TreeNode *> &trees) {
        _trees = trees;
        TreeNode *root = build_bst();
        // trace("before check");
        set<int> total;
        for (auto &node: trees) {
            total.insert(node->val);
            if (node->left)
                total.insert(node->left->val);
            if (node->right)
                total.insert(node->right->val);
        }
        int bl = check_bst(root);
        // trace(bl);
        if (bl == sz(total))
            return root;
        else
            return nullptr;
    }
};

int read_input() {
    cin >> n;
    // trace("before inputi");
    trees.clear();
    for (int i: range(n)) {
        int t;
        cin >> t;
        vi arr;
        for (int j: range(t)) {
            int temp;
            cin >> temp;
            arr.push_back(temp);
        }
        // trace(arr);
        TreeNode *node = make_node();
        node->val = arr[0];
        for (int j: range(1, sz(arr))) {
            TreeNode *alter_node = make_node();
            alter_node->val = arr[j];
            if (alter_node->val > node->val)
                node->right = alter_node;
            else
                node->left = alter_node;
        }
        trees.push_back(node);
    }
    // trace("after input");
    return 0;
}

auto solve() {
    /**
     * main logic goes here
     **/
    Solution solution = Solution();
    auto ans = solution.canMerge(trees);
    return ans;
}

int second_main() {
    read_input();
    auto ans = solve();
    cout << (ans != nullptr ? ans->val : -1) << endl;
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
