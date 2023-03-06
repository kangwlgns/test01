#include <iostream>
#include <vector>

using namespace std;
using ll = long long;

class Line {
public:
    ll m, b;
    long double s;

    Line() {m = 0; b = 0; s = 0;}

    Line(ll m, ll b) {
        this->m = m;
        this->b = b;
        s = 0;
    }
};

int N;
ll A[100000], B[100000];
ll dist[100000];
Line lines[100000];

long double getCross(Line l1, Line l2) {
    ll m1 = l1.m, b1 = l1.b, m2 = l2.m, b2 = l2.b;
    return ((long double) b2 - b1) / (m1 - m2);
}

int lowerbound(int left, int right, ll key) {
    int ans = right - 1;

    while (left <= right) {
        int mid = (left + right) / 2;
        double s = lines[mid].s;

        if (key >= s) {
            ans = mid;
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }

    return ans;
}

void CHT() {
    int size = 0;
    dist[0] = 0;

    for (int i = 1; i < N; i++) {
        Line cur(B[i - 1], dist[i - 1]);

        while (size > 0) {
            Line pre = lines[size - 1];
            cur.s = getCross(cur, pre);

            if (cur.s > pre.s) break;
            --size;
        }

        lines[size++] = cur;

        ll x = A[i];
        int idx = lowerbound(0, size - 1, x);

        dist[i] = lines[idx].m * x + lines[idx].b;
    }
}

int main(void) {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    cin >> N;
    for (int i = 0; i < N; i++) {
        int n; cin >> n;
        A[i] = n;
    }
    
    for (int i = 0; i < N; i++) {
        int n; cin >> n;
        B[i] = n;
    }

    CHT();

    cout << dist[N - 1];

    return 0;
}