#include <bits/stdc++.h>
using namespace std;

#ifdef LOCAL
#include <algo/debug.h>
#endif

bool cmp(const vector<int>& a, const vector<int>& b) {
	return a[2] < b[2];
}

struct DSU {
	vector<int> parent;
	vector<int> size;

	DSU(int range) {
		parent.resize(range);
		size.resize(range);
		for (int i = 0; i < range; i++) {
			parent[i] = i;
			size[i] = 1;
		}
	}
	int find(int node) {
		if (parent[node] == node) return node;
		return parent[node] = find(parent[node]);
	}
	bool join(int a, int b) {
		a = find(a);
		b = find(b);
		if (a == b) return false;
		if (size[a] < size[b]) {
			int temp = a;
			a = b;
			b = temp;
		}
		parent[b] = a;
		size[a] += size[b];
		size[b] = size[a];
		return true;
	}
};

int main() {
	freopen("moocast.in", "r", stdin);
	freopen("moocast.out", "w", stdout);

	ios::sync_with_stdio(false);
	cin.tie(NULL);

	int n;
	cin >> n;
	DSU dsu(n);
	vector<vector<int>> edge(0, vector<int>(3));
	vector<pair<int, int>> coord(n);
	for (int i = 0; i < n; i++) cin >> coord[i].first >> coord[i].second;
	for (int i = 0; i < n; i++) {
		for (int j = i + 1; j < n; j++) {
			edge.push_back({i, j, (int)(pow(coord[i].first - coord[j].first, 2) + pow(coord[i].second - coord[j].second, 2))});
		}
	}
	sort(edge.begin(), edge.end(), cmp);
	// highest weight edge on minimum spanning tree
	int maxWeight = 0;
	for (int i = 0; i < (int)edge.size(); i++) {
		if (dsu.join(edge[i][0], edge[i][1])) {
			maxWeight = edge[i][2];
		}
	}

	cout << maxWeight;
	return 0;
}
