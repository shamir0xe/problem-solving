#include <bits/stdc++.h>
using namespace std;

/**
 * generated template for competetive programming
 * problem C (3/4)
 * leetcode, Weekly-Contest-361
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
#define X first
#define Y second

vi range(int n) {
    if (n <= 0)
        return vi();
    vi indices(n);
    for (int i = 0; i < n; ++i)
        indices[i] = i;
    return indices;
}

// define variables here
#define MAX_N 100005 // 10^5 + 5
int n, k, modulo;
vi c;
vi nums;

// define functions here

class Solution {
  public:
    string assert_string(string s) { return "entered " + s; }
    long long countInterestingSubarrays(vector<int> &nums, int modulo, int k) {
        // trace(modolu _ k);
        int n = sz(nums);
        c.resize(n + 1, 0);
        vi tt;
        tt.push_back(0);
        for (auto t: nums) {
            tt.push_back(t);
        }
        map<int, int> total;
        total[0] = 1;
        ll ans = 0;
        for (int i = 1; i < sz(tt); ++i) {
            c[i] = c[i - 1] + (tt[i] % modulo == k ? 1 : 0);
            int le = (c[i] - k + modulo) % modulo;
            // trace(i _ c[i] _ le);
            if (total.find(le) != total.end()) {
                // trace(total[le]);
                ans += total[le];
            }
            int temp = c[i] % modulo;
            if (total.find(temp) != total.end())
                total[temp] += 1;
            else
                total[temp] = 1;
        }

        return ans;
    }
};

void read_input() {
    cin >> n >> modulo >> k;
    for (auto i: range(n)) {
        int temp;
        cin >> temp;
        nums.push_back(temp);
    }
}

auto solve() {
    /**
     * main logic goes here
     **/
    Solution solution = Solution();
    auto ans = solution.countInterestingSubarrays(nums, modulo, k);
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
