#include <bits/stdc++.h>
#include <iostream>
using namespace std;

int main() {

    int m;
    cin >> m;
    vector<int> bits(31, 0);
    while (m--) {
        int t, v;
        cin >> t >> v;
        // vector<int> v1;
        if (t == 1) {
            bits[v]++;
        } else {
            int sum = v;
            for (int i = 29; i >= 0; i--) {
                int count = 0;
                while (count < bits[i] && ((1 << i) <= sum)) {
                    count++;
                    sum -= (1 << i);
                }
            }

            if (sum == 0) {
                cout << "YES" << endl;
            } else {
                cout << "NO" << endl;
            }
        }
    }
    return 0;
}
