#include<cstdio>
#include<climits>
#include<cmath>
#include<cstdlib>
#include<cstring>
#include<cassert>
#include<vector>
#include<iostream>
#include<fstream>
#include<sstream>
#include<queue>
#include<stack>
#include<set>
#include<map>
#include<unordered_map>
#include<unordered_set>
#include<deque>
#include<list>
#include<string>
#include<bitset>
#include<algorithm>
#include<functional>
#include<numeric>
#include<random>

using namespace std;

#define LIMIT 10000000000000000
#define MOD 1000000007
#define PI 3.14159265359
#define SIZE 1000

typedef long long ll;
typedef unsigned long long ull;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
typedef long double ld;

typedef struct {
	long double x, y;
}Point;

typedef struct {
	Point center;
	long double radius;
}Circle;

long double dist(Point& a, Point& b) {
	return sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
}

Point findCenter(Point& a, Point& b) {
	return { (a.x + b.x) / 2.0, (a.y + b.y) / 2.0 };
}
Point findCenter(Point& a, Point& b, Point& c) {
	long double ab = dist(a, b), bc = dist(b, c), ca = dist(c, a);

	if (ab * ab > bc * bc + ca * ca) {
		return findCenter(a, b);
	}
	else if (bc * bc > ca * ca + ab * ab) {
		return findCenter(b, c);
	}
	else if (ca * ca > ab * ab + bc * bc) {
		return findCenter(c, a);
	}

	long double ax = a.x - c.x;
	long double ay = a.y - c.y;
	long double bx = b.x - c.x;
	long double by = b.y - c.y;

	long double asq = ax * ax + ay * ay;
	long double bsq = bx * bx + by * by;
	long double ccw = ax * by - ay * bx;

	return { c.x + (by * asq - ay * bsq) / (2.0 * ccw), c.y - (bx * asq - ax * bsq) / (2.0 * ccw) };
}

Circle findCircleWithTwoPoint(vector<Point>& points, Point& p1, int idx1, Point& p2, int idx2) {
	Point temp = findCenter(p2, p1);
	Circle now = { temp, dist(temp, p1) };

	for (int i = 0; i < idx2; i++) {
		if (dist(points[i], now.center) > now.radius) {
			temp = findCenter(p1, p2, points[i]);
			now = { temp, dist(temp, points[i]) };
		}
	}
	return now;
}

Circle findCircleWithPoint(vector<Point>& points, Point& p1, int idx) {
	Point temp = findCenter(points[0], p1);
	Circle now = { temp, dist(temp, p1) };

	for (int i = 1; i < idx; i++) {
		if (dist(points[i], now.center) > now.radius) {
			now = findCircleWithTwoPoint(points, p1, idx, points[i], i);
		}
	}
	return now;
}

Circle findCircle(vector<Point>& points) {
	if (points.size() == 1) {
		return { points[0], 0 };
	}

	Point temp = findCenter(points[0], points[1]);
	Circle now = { temp, dist(temp, points[0]) };

	for (int i = 2; i < points.size(); i++) {
		if (dist(points[i], now.center) > now.radius) {
			now = findCircleWithPoint(points, points[i], i);
		}
	}
	return now;
}

int n;
vector<Point>points;

int main(void)
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	cin >> n;

	while (n--) {
		double a, b;
		cin >> a >> b;
		points.push_back({ a, b });
	}

	random_device rd;
	mt19937 gen(rd());
	shuffle(points.begin(), points.end(), gen);

	Circle ans = findCircle(points);
	cout << fixed;
	cout.precision(10);
	cout << ans.center.x << " " << ans.center.y << " " << ans.radius;
}
