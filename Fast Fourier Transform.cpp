#include <bits/stdc++.h>
using namespace std;

#define MOD 1000000007
#define MAX 200005
#define PMAX 55
#define PRECISION 0.000001
#define INF 2000000000
#define FASTIO ios_base::sync_with_stdio(false);cin.tie(NULL)
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
#include <ext/pb_ds/detail/standard_policies.hpp>

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
using cd = complex<double>;
const double PI = acos(-1);

void fft(vector<cd>& a, bool invert)
{
    int n = a.size();
    for(int i = 1, j = 0; i < n; i++){
        int bit = n>>1;
        for(; j&bit; bit>>=1){
            j^=bit;
        }
        j ^= bit;
        if(i < j)
            swap(a[i], a[j]);
    }

    for(int len = 2; len <= n; len <<= 1){
        double ang = 2*PI/len*(invert ? -1 : 1);
        cd wlen(cos(ang), sin(ang));
        for(int i = 0; i < n; i += len){
            cd w(1);
            for(int j = 0; j < len/2; j++){
                cd u = a[i+j], v = a[i+j+len/2]*w;
                a[i+j] = u+v;
                a[i+j+len/2] = u-v;
                w *= wlen;
            }
        }
    }

    if(invert){
        for(cd &x: a)
            x /= n;
    }
}
vector<int> multiply(vector<int> const& a, vector<int> const&b)
{
    vector<cd> fa(a.begin(), a.end());
    vector<cd> fb(b.begin(), b.end());
    int n = 1;
    while(n < a.size()+b.size())
        n <<= 1;
    fa.resize(n);
    fb.resize(n);
    fft(fa, false);
    fft(fb, false);

    for(int i = 0; i < n; i++)
        fa[i] *= fb[i];

    fft(fa, true);

    vector<int> result(n);
    for(int i = 0; i < n; i++)
        result[i] = round(fa[i].real());
    return result;
}
//Number Theoretic Transformation
/*
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

const int mod = 998244353;
const int root = 15311432;
const int root_1 = 469870224;
const int root_pw = 1 << 23;
void fft(vector<int> & a, bool invert) {
    int n = a.size();

    for (int i = 1, j = 0; i < n; i++) {
        int bit = n >> 1;
        for (; j & bit; bit >>= 1)
            j ^= bit;
        j ^= bit;

        if (i < j)
            swap(a[i], a[j]);
    }

    for (int len = 2; len <= n; len <<= 1) {
        int wlen = invert ? root_1 : root;
        for (int i = len; i < root_pw; i <<= 1)
            wlen = (int)(1LL * wlen * wlen % mod);

        for (int i = 0; i < n; i += len) {
            int w = 1;
            for (int j = 0; j < len / 2; j++) {
                int u = a[i+j], v = (int)(1LL * a[i+j+len/2] * w % mod);
                a[i+j] = u + v < mod ? u + v : u + v - mod;
                a[i+j+len/2] = u - v >= 0 ? u - v : u - v + mod;
                w = (int)(1LL * w * wlen % mod);
            }
        }
    }

    if (invert) {
        int n_1 = (int) ModuloInverse(n, mod);
        for (int & x : a)
            x = (int)(1LL * x * n_1 % mod);
    }
}

vector<int> multiply(vector<int> const& a, vector<int> const&b)
{
    vector<int> fa(a.begin(), a.end());
    vector<int> fb(b.begin(), b.end());
    int n = 1;
    while(n < a.size()+b.size())
        n <<= 1;
    fa.resize(n);
    fb.resize(n);
    fft(fa, false);
    fft(fb, false);

    for(int i = 0; i < n; i++)
        fa[i] = (int) (1LL*fa[i]*fb[i]%mod);

    fft(fa, true);

    vector<int> result(n);
    for(int i = 0; i < n; i++)
        result[i] = fa[i];
    return result;
}
*/
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

char s[MAX];

int main()
{
//    READ;
//    WRITE;
//    FASTIO;

    int n;
    scanf("%s", s);
    n = strlen(s);
    vector<int> a(n), b(n);

    for(int i = 0; i < n; i++){
        if(s[i] == 'B'){
            b[(n-1)-i] = 1;
            a[i] = 0;
        }
        else{
            b[(n-1)-i] = 0;
            a[i] = 1;
        }
    }

    vector<int> c = multiply(b, a);
    for(int i = 0; i < c.size(); i++){
        int p = i-(n-1);
        if(1<=p && p<=n-1){
            printf("%d\n", c[i]);
        }
    }

    return 0;
}
