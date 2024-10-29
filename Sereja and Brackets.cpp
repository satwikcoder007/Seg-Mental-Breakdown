#include <bits/stdc++.h>
using namespace std;

using ll = long long;
const ll mod = 1e9;

class segTree {
public:
    string s;
    int n;
    vector<array<int, 3>> seg;

    segTree(int n, string s) : n(n), s(s) {
        seg.resize(4 * n, {-1, -1, -1});
    }

    void createTree(int l, int h, int ind) {
        if (l == h) {
            if (s[l] == '(') seg[ind] = {0, 1, 0};
            else seg[ind] = {0, 0, 1};
            return;
        }
        int m = (l + h) / 2;
        createTree(l, m, 2 * ind + 1);
        createTree(m + 1, h, 2 * ind + 2);
        int b = seg[2 * ind + 1][0] + seg[2 * ind + 2][0];
        int newb = min(seg[2 * ind + 1][1], seg[2 * ind + 2][2]);
        b += newb;
        int ob = seg[2 * ind + 1][1] + seg[2 * ind + 2][1] - newb;
        int cb = seg[2 * ind + 1][2] + seg[2 * ind + 2][2] - newb;
        seg[ind] = {b, ob, cb};
    }

    array<int, 3> queryProcessing(int l, int h, int L, int H, int ind) {
        if (l > H || h < L) {
            return {0, 0, 0};
        }
        if (L <= l && h <= H) {
            return seg[ind];
        }
        int m = (l + h) / 2;
        array<int, 3> lef = queryProcessing(l, m, L, H, 2 * ind + 1);
        array<int, 3> rig = queryProcessing(m + 1, h, L, H, 2 * ind + 2);
        array<int, 3> v = {0, 0, 0};
        v[0] = lef[0] + rig[0];
        int newb = min(lef[1], rig[2]);
        v[0] += newb;
        v[1] = lef[1] + rig[1] - newb;
        v[2] = lef[2] + rig[2] - newb;
        return v;
    }
};

void solve() {
    int m;
    string s;
    vector<pair<int, int>> queries;

    cin >> s;
    cin >> m;
    for (int i = 0; i < m; i++) {
        int l, r;
        cin >> l >> r;
        queries.push_back({l - 1, r - 1});
    }

    int n = s.size();
    segTree s1(n, s);

    s1.createTree(0, n - 1, 0);
    for (const auto& it : queries) {
        int x = s1.queryProcessing(0, n - 1, it.first, it.second, 0)[0];
        cout << x * 2 << endl;
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    solve();
}
