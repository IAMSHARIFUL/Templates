#include<bits/stdc++.h>
using namespace std;
#define MAX 100000
#define MOD 1000000007
long long int fact[MAX+1],fact_inv[MAX+1];
long long int gcd(long long int a,long long int b)
{
    if(b==0) return a;
    else return gcd(b,a%b);
}
long long int egcd(long long int a, long long int b, long long int & x, long long int & y) {
    if (a == 0) {
        x = 0;
        y = 1;
        return b;
    }
    long long int x1, y1;
    long long int d = egcd(b % a, a, x1, y1);
    x = y1 - (b / a) * x1;
    y = x1;
    return d;
}
long long int ModuloInverse(long long int a,long long int n)
{
    long long int x,y;
    x=gcd(a,n);
    a=a/x;
    n=n/x;
    long long int res = egcd(a,n,x,y);
    x=(x%n+n)%n;
    return x;
}
void precal()
{
    int i;
    fact[0]=fact_inv[0]=1;
    for(i=1;i<=MAX;i++)
    {
        fact[i]=(fact[i-1]*i)%MOD;

    }
    i=MAX;
    fact_inv[i]=ModuloInverse(fact[i],MOD);
    for(i=MAX-1;i>0;i--)
    {
        fact_inv[i]=(fact_inv[i+1]*(i+1))%MOD;
    }
}
long long int C(int n,int r)
{
    long long int res=fact[n];
    res=(res*fact_inv[n-r])%MOD;
    res=(res*fact_inv[r])%MOD;
    return res;
}
int main()
{
    precal();
    while(true)
    {
        int n,r;
        scanf("%d %d",&n,&r);
        long long int res=C(n,r);
        long long int mod_inv=ModuloInverse(n,MOD);
        printf("%lld %lld\n",res,mod_inv);
    }
    return 0;
}
