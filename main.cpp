#include <bits/stdc++.h>

using namespace std;

long long roundUp(long long n)
{
    long long p = 1;
    while(p < n)
        p *= 2;
    return p;
}

long long lowestBit(long long a)
{
    long long i = 0;
    while(a != 0)
    {
        if(a % 2 == 1)
            return pow(2, i);
        a /= 2;
        i++;
    }
    return 0;
}

struct fenwick
{
    fenwick(long long n):
        data(roundUp(n) + 1) {}

    void add(long long k, long long x = 1)
    {
        while (k < data.size())
        {
            data[k] += x;
            k += lowestBit(k);
        }
    }

    long long query(long long k)
    {
        long long result = 0;
        if (!k)
            return 0;
        while (k > 0)
        {
            result += data[k];
            k -= lowestBit(k);
        }
        return result;
    }
    vector<long long> data;
};

int main()
{
    ifstream fin("input.txt");
    ofstream fout("output.txt");

    long long n;
    fin >> n;

    fenwick numbers(n);
    fenwick inversions(n);
    long long megainversions = 0;

    for (long long i = 0; i < n; i++)
    {
        long long num;
        fin >> num;
        numbers.add(num);
        inversions.add(num, numbers.query(n) - numbers.query(num));
        megainversions += inversions.query(n) - inversions.query(num);
    }
    fout << megainversions << endl;
    return 0;
}
