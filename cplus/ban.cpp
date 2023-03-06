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
    return ((double) b2 - b1) / (m1 - m2);
}

void CHT() {
    dist[0] = 0;
    int top = 0; // stacksize
    int j = 0;

    for (int i = 1; i < N; i++) {
        Line cur(B[i - 1], dist[i - 1]);

        while (top > 0) {
            long double preP = lines[top - 1].s, curP = getCross(lines[top - 1], cur);
            if (curP <= preP) {
                if (--top == j) --j;
            } else {
                cur.s = curP;
                break;
            }
        }

        lines[top++] = cur;

        while (1) {
            if (j == (top - 1) || A[i] < lines[j + 1].s) {
                dist[i] = lines[j].m * A[i] + lines[j].b;
                break;
            } else {
                ++j;
            }
        }
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