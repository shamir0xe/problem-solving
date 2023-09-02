#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;
typedef vector<vector<int> > vii;
#define trace(x) cerr << #x << " : " << x << endl
#define _ << " " << 
#define sz(x) ((int) (x).size())
#define X first
#define Y second

#define MAX_N 100005

// generated template for competetive programming
// problem {} ({}/{})
// {}, {}
// author: @shamir0xe
// verdict: [AC/WA/TLE/MLE]

// define variables here
int n, m, k;
vi nums;

vector <int> range(int n) {
	vector <int> indices(n);
	for (int i = 0; i < n; ++i) indices[i] = i;
	return indices;
}

class Solution {
public:
    long long maxSum(vector<int>& nums, int m, int k) {
    	ll sum = 0;
    	int n = sz(nums);
    	map <int, int> table;
    	ll ans = 0;
    	for (auto i: range(n)) {
    		sum += nums[i];
    		if (table.find(nums[i]) != table.end()) {
    			table[nums[i]] += 1;
    		} else {
    			table[nums[i]] = 1;
    		}
    		if (i >= k) {
    			sum -= nums[i - k];
    			table[nums[i - k]] -= 1;
    			if (table[nums[i - k]] == 0) {
    				table.erase(nums[i - k]);
    			}
    		}
    		if (sz(table) >= m) {
    			ans = max(ans, sum);
    		}
    	}
    	return ans;
    }
};


void read_input() {
	cin >> n >> m >> k;
	for (auto i: range(n)) {
		int temp; cin >> temp;
		nums.push_back(temp);
	}
	// trace(hs[0] _ hs[1] _ sz(edges));
}

auto solve() {
	// main logic comes here
	Solution solution = Solution();
	ll ans = solution.maxSum(nums, m, k);
	return ans;
}




int second_main() {
	read_input();
	auto ans = solve();
	cout << ans << endl;
	return 0;
}

int main() {
	ios_base::sync_with_stdio(false); cin.tie(0);
	bool test_case = false;
	if (test_case) {
		int t; cin >> t;
		while (t--) {
			second_main();
		}
	} else {
		second_main();
	}
	return 0;
}

