#include <iostream>
#include <algorithm>
#include <vector>
#define f first
#define s second

using namespace std;

vector<pair<int, pair<int, int>>> E, MST;
//vector<vector<pair<int, int>>> G(100000);
int* comp, *num, *par;

void connect(int a, int b);
int parent(int, int* par);

int main()
{
	int vert, edges;
	cin >> vert >> edges;
	par = new int[vert];
	comp = new int[vert];
	num = new int[vert];
	for (int i = 0; i <= vert; i++)	par[i] = i, comp[i] = i, num[i] = 1;
	for (int i = 0; i < edges; i++)
	{
		int a, b, dist;
		cin >> dist >> a >> b;
		E.push_back(make_pair(dist, make_pair(a,b)));
		//G[a].push_back(make_pair(dist, b));
		//G[b].push_back(make_pair(dist, a));
	}
	sort(E.begin(), E.end());

	for (int i = 0; i < edges; i++)
	{
		int a, b, dist;
		dist = E[i].first;
		a = E[i].second.first;
		b = E[i].second.second;
		int pa, pb;
		pa = parent(a, par);
		pb = parent(b, par);
		if (comp[pa] != comp[pb]) {
			connect(pa, pb);
			MST.push_back(E[i]);
		}
	}
	for (int i = 0; i < MST.size(); i++)
	{
		cout << MST[i].s.f << " " << MST[i].s.s << " " << MST[i].f << endl;
	}
	return 0;
}



int parent(int v, int* par)
{
	if (v == par[v]) return v;
	int ret = parent(par[v], par);
	par[v] = ret;
	return par[v];
}

void connect(int a, int b)
{
	if (num[a] < num[b]) swap(a, b);
	int pa, pb;
	pa = parent(a, par);
	pb = parent(b, par);
	comp[pb] = comp[pa];
	par[pb] = pa;
	num[pa] += num[pb];
	num[pb] = num[pa];
}