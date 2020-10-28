#include <iostream>
#include <math.h>
#include <memory.h>
#include <algorithm>

using namespace std;

void Propagate(int ST[], int lazy[], int v, int L, int R);
void Build(int ST[], int v, int L, int R, int numbers[]);
int Sum(int ST[], int lazy[], int v, int L, int R, int left, int right);
void Add(int ST[], int lazy[], int v, int L, int R, int left, int right, int add);
void Display(int ST[], int lazy[], int v, int L, int R);

int main()
{
	int a[10000], ST[100000], lazy[100000];
	memset(lazy, 0, 100000);
	memset(ST, 0, 100000);
	int n;
	cin >> n;
	for (int i = 0; i < n; i++) cin >> a[i];
	Build(ST, 1, 0, n - 1, a);
	int option = 1, l, r;
	while (option)
	{
		cin >> option;
		if (option == 1)
		{
			cin >> l >> r;
			cout << Sum(ST, lazy, 1, 0, n - 1, l, r) << endl;
		}
		else if (option == 2)
		{
			int add;
			cin >> l >> r >> add;
			Add(ST, lazy, 1, 0, n - 1, l, r, add);
		}
		else
			Display(ST, lazy, 1, 0, n - 1);
	}
	return 0;
}

void Build(int ST[], int v, int L, int R, int numbers[])
{
	if (L == R) { ST[v] = numbers[L]; return; }
	int mid = (L + R) / 2;
	Build(ST, v * 2, L, mid, numbers);
	Build(ST, v * 2 + 1, mid + 1, R, numbers);
	ST[v] = ST[v * 2] + ST[v * 2 + 1];
}
int Sum(int ST[], int lazy[], int v, int L, int R, int left, int right)
{
	int mid = (L + R) / 2;
	if (left > R || right < L) return 0;
	Propagate(ST, lazy, v, L, R);
	if (L == left && R == right) return ST[v];
	int lSum, rSum;
	lSum = Sum(ST, lazy, v * 2, L, mid, left, min(mid, right));
	rSum = Sum(ST, lazy, v * 2 + 1, mid + 1, R, max(mid + 1, left), right);
	ST[v] = lSum + rSum;
	return lSum + rSum;
}

void Propagate(int ST[], int lazy[], int v, int L, int R)
{
	ST[v] += (R-L+1) * lazy[v];
	lazy[v * 2] += lazy[v];
	lazy[v * 2 + 1] += lazy[v];
	lazy[v] = 0;
}

void Add(int ST[], int lazy[], int v, int L, int R, int left, int right, int add)
{
	int mid = (L + R) / 2;
	if (left > R || right < L) return;
	Propagate(ST, lazy, v, L, R);
	if (left == L && right == R) { 
		ST[v] += (R - L + 1) * add; lazy[v * 2] += add; lazy[v * 2 + 1] += add; return; 
}
	Add(ST, lazy, v * 2, L, mid, left, min(mid, right), add);
	Add(ST, lazy, v * 2 +1, mid+1, R, max(mid+1, left), right, add);
	ST[v] = ST[v * 2] + ST[v * 2 + 1];
}

void Display(int ST[], int lazy[], int v, int L, int R)
{
	int mid = (L + R) / 2;
	Propagate(ST, lazy, v, L, R);
	if (L == R) { cout << ST[v] << " "; return; }
	Display(ST, lazy, v * 2, L, mid);
	Display(ST, lazy, v * 2+1, mid+1, R);
	if (v == 1) cout << endl;
}
