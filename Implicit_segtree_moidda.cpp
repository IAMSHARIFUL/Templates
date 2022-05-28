#include <bits/stdc++.h>
using namespace std;


#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
#define ordered_set tree<int, null_type,less<int>, rb_tree_tag,tree_order_statistics_node_update>


#define INF             1e9
#define INFL            1e18
#define XX              first
#define YY              second
#define PB              push_back
#define MP              make_pair

#define NEWLINE         cerr << "\n";
#define HOISE           cerr << "hoise" << "\n"
#define PAUSE           system("pause")
#define DEBUG(x)        cerr << #x << " = " << x << "\n"
#define READ            freopen("alu.txt", "r", stdin)
#define WRITE           freopen("vorta.txt", "w", stdout)
#define FASTIO          ios_base::sync_with_stdio(false);cin.tie(NULL)
#define MASK(x)         for(int i = 0; i < 8; i++){ if(x&(1<<i)){ cout << i << " "; } } cout << endl;

typedef long long ll;
typedef pair<int, int > pii;
typedef pair<ll, ll> pll;
typedef pair<double, double> pff;

const int MAX = 2e5 + 2;
const int MAXLOG = log2(MAX) + 2;
const int MAXN = 1e6 + 2;
const int MOD = 998244353;
const double PY = acos(-1.0);

struct node
{
    int sum;
    node *lft;
    node *rt;

    node(){sum = 0; lft = NULL; rt = NULL;}
    node(int a = 0, node *x = NULL, node *y = NULL){sum = a; lft = x; rt = y;}

    void update(node *now, int L, int R, int idx, int val)
    {
        if(L == R){
            now->sum += val;
            return;
        }

        int mid = (L+R)/2;
        if(now->lft == NULL) now->lft = new node(mid-L+1, NULL, NULL);
        if(now->rt == NULL)  now->rt = new node(R-(mid+1)+1, NULL, NULL);

        if(idx <= mid) update(now->lft, L, mid, idx, val);
        else update(now->rt, mid+1, R, idx, val);

        now->sum = (now->lft)->sum + (now->rt)->sum;
    }

    int query(node *now, int L, int R, int kth)
    {
        if(L == R){
            return L;
        }

        int mid = (L+R)/2;
        if(now->lft == NULL) now->lft = new node(mid-L+1, NULL, NULL);
        if(now->rt == NULL)  now->rt = new node(R-(mid+1)+1, NULL, NULL);

        if(kth <= (now->lft)->sum) return query(now->lft, L, mid, kth);
        else return query(now->rt, mid+1, R, kth - (now->lft)->sum);
    }
};

/// Dynamic Range Sum
class Segtree{
public:
    int n;
    node *root;

    void Init(int nn)
    {
        root = new node(nn, NULL, NULL);
        n = nn;
    }
    void update(int idx, int val)
    {
        root->update(root, 1, n, idx, val);
    }
    int query(int kth)
    {
        return root->query(root, 1, n, kth);
    }
};

int n, q;
Segtree bst;

int32_t main()
{
#ifndef ONLINE_JUDGE
//    READ;
//    WRITE;
#endif

    FASTIO;

    cin >> n >> q;
    bst.Init(n);

    while(q--){
        char t;
        int x;
        cin >> t >> x;

        int xth = bst.query(x);

        if(t == 'L') cout << xth << "\n";
        else bst.update(xth, -1);
    }

    return 0;
}
