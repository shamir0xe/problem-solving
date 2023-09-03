#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;
typedef vector<vector<int>> vii;
#define trace(x) cerr << #x << " : " << x << endl
#define _ << " " <<
#define sz(x) ((int)(x).size())
#define X first
#define Y second

#define MAX_N 100005

// generated template for competetive programming
// problem {} ({}/{})
// {}, {}
// author: @shamir0xe
// verdict: [AC/WA/TLE/MLE]

// define variables here
int k;
vector<int> fac;
string s;
const int mod = 1000 * 1000 * 1000 + 7;

vector<int> range(int n) {
    vector<int> indices(n);
    for (int i = 0; i < n; ++i)
        indices[i] = i;
    return indices;
}

int mul(int a, int b) { return int((1LL * a * b) % mod); }

int fast_pow(int a, int b) {
    int res = 1;
    while (b) {
        if (b & 1) {
            res = mul(res, a);
        }
        b >>= 1;
        a = mul(a, a);
    }
    return res;
}

int choose(int n, int k) {
    return mul(fac[n], fast_pow(mul(fac[n - k], fac[k]), mod - 2));
}

class Solution {
  public:
    int countKSubsequencesWithMaxBeauty(string s, int k) {
        int nums[33];
        fill(nums, nums + 33, 0);
        int n = sz(s);
        for (auto i: range(n)) {
            nums[s[i] - 'a'] += 1;
        }
        vi candidates;
        for (auto i: range(33)) {
            if (nums[i] != 0) {
                // trace(char('a' + i) _ nums[i]);
                candidates.push_back(nums[i]);
            }
        }
        sort(candidates.begin(), candidates.end());
        reverse(candidates.begin(), candidates.end());
        if (sz(candidates) < k) {
            return 0;
        }
        int index = k - 1;
        if (sz(candidates) > k) {
            if (candidates[k - 1] == candidates[k]) {
                while (index >= 0 &&
                       candidates[index] == candidates[index + 1]) {
                    index -= 1;
                }
            }
        }
        trace(sz(candidates) _ index);

        int t = 0;
        for (int i = index + 1;
             i < sz(candidates) && candidates[i] == candidates[index + 1];
             ++i) {
            t++;
        }
        trace(t);
        fac = vi(n + 1);
        fac[1] = 1;
        fac[0] = 1;
        for (int i = 2; i <= n; ++i) {
            fac[i] = mul(fac[i - 1], i);
        }
        int ans = 1;
        for (int i = 0; i <= index; ++i) {
            ans = mul(ans, candidates[i]);
        }
        if (t > 0 and index + 1 < k) {
            // trace(k - index + 1);
            ans = mul(ans, choose(t, k - index - 1));
            for (auto i: range(k - index - 1))
                ans = mul(ans, candidates[index + 1]);
        }
        return ans;
    }
};

void read_input() {
    cin >> k >> s;
    // trace(hs[0] _ hs[1] _ sz(edges));
}

auto solve() {
    // main logic comes here
    Solution solution = Solution();
    int ans = solution.countKSubsequencesWithMaxBeauty(s, k);
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
