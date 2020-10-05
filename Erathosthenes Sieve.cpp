#include <iostream>
#include <memory.h>

using namespace std;

int isPrime[1000001];
int masks[33]; // keeping accesses to 32 bit positions

void generatePrimes();

pair<int, int> findIndex(int n);

int main()
{
	generatePrimes();
	int a = 1;
	while (a)
	{
		cin >> a;
		cout << isPrime[a] << endl;
	}
	return 0;
}

void generatePrimes()
{
	memset(isPrime, 0, 100000);
	int prod = 1;
	masks[0] = 1;
	for (int i = 1; i <= 31; ++i)
	{
		prod *= 2;
		masks[i] = prod;
	}

	pair<int, int> index, index2;

	for (long long i = 2; i <= 30000; ++i)
	{
		index = findIndex(i);
		if (!(isPrime[index.first] & masks[index.second]))
		{
			//cout << i << endl;
			for (long long j = i * i; j <= 3000000; j += i)
			{
				index2 = findIndex(j);
				isPrime[index2.first] |= masks[index2.second];
			}
		}
	}
}

pair<int, int> findIndex(int n)
{
	pair<int, int> ind;
	ind.first = n / 32;
	ind.second = n % 32;
	return ind;
}