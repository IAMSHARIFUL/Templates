#include<bits/stdc++.h>
#include<math.h>
using namespace std;
#define MAX 100000
int prime[MAX+1],Phi[MAX+1];
void sieve()
{
    int i,j;
    for(i=2; i*i<=MAX; i++)
    {
        if(prime[i]) continue;
        for(j=i; j*i<=MAX; j++)
        {
            if(prime[i*j]==0) prime[i*j]=i;
        }
    }
}
void PhiWithSieve()
{
    int i;
    for(i=2; i<=MAX; i++)
    {
        if(prime[i]==0)
        {
            Phi[i]=i-1;
        }
        else if((i/prime[i])%prime[i]==0)
        {
            Phi[i]=Phi[i/prime[i]]*prime[i];
        }
        else
        {
            Phi[i]=Phi[i/prime[i]]*(prime[i]-1);
        }
    }
}
int gcd(int a,int b)
{
    if(b==0) return a;
    else return gcd(b,a%b);
}
int powmod (int a, int b, int p) {
    int res = 1;
    while (b)
        if (b & 1)
            res = int (res * 1ll * a % p),  --b;
        else
            a = int (a * 1ll * a % p),  b >>= 1;
    return res;
}
int PrimitiveRoot(int p)
{
    vector<int>fact;
    int phi=Phi[p];
    int n=phi;
    while(n>1)
    {
        if(prime[n]==0)
        {
            fact.push_back(n);
            n=1;
        }
        else
        {
            int f=prime[n];
            while(n%f==0)
            {
                n=n/f;
            }
            fact.push_back(f);
        }
    }
    int res;
    for(res=p-1; res>1; --res)
    {
        for(n=0; n<fact.size(); n++)
        {
            if(powmod(res,phi/fact[n],p)==1)
            {
                break;
            }
        }
        if(n>=fact.size()) return res;
    }
    return -1;
}
int DiscreteLog(int a, int b, int m) {
    a %= m, b %= m;
    int n = sqrt(m) + 1;
    map<int, int> vals;
    for (int p = 1; p <= n; ++p)
        vals[powmod(a,(int) (1ll* p * n) %m , m)] = p;
    for (int q = 0; q <= n; ++q) {
        int cur = (powmod(a, q, m) * 1ll * b) % m;
        if (vals.count(cur)) {
            int ans = vals[cur] * n - q;
            return ans;
        }
    }
    return -1;
}
vector<int> DiscreteRoot(int n,int a,int k)
{
    int g = PrimitiveRoot(n);
    vector<int> ans;
    int any_ans = DiscreteLog(powmod(g,k,n),a,n);
    if (any_ans == -1)
    {
        return ans;
    }
    int delta = (n-1) / gcd(k, n-1);
    for (int cur = any_ans % delta; cur < n-1; cur += delta)
        ans.push_back(powmod(g, cur, n));
    sort(ans.begin(), ans.end());
    return ans;
}
