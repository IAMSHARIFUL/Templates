#include <bits/stdc++.h>
#include <vector>
#include<math.h>
#include<string.h>
using namespace std;
#define MAX 200005
#define MOD 1000000007
#define INF 10000000000
#define EPS 0.0000000001
#define FASTIO ios_base::sync_with_stdio(false);cin.tie(NULL)
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
#include <ext/pb_ds/detail/standard_policies.hpp>
class LiChaoTree
{
    long long L,R;
    bool minimize;
    int lines;
    struct Node
    {
        complex<long long> line;
        Node *children[2];
        Node(complex<long long> ln= {0,1000000000000000000})
        {
            line=ln;
            children[0]=0;
            children[1]=0;
        }
    } *root;
    long long dot(complex<long long> a, complex<long long> b)
    {
        return (conj(a) * b).real();
    }
    long long f(complex<long long> a,  long long x)
    {
        return dot(a, {x, 1});
    }
    void clear(Node* &node)
    {
        if(node->children[0])
        {
            clear(node->children[0]);
        }
        if(node->children[1])
        {
            clear(node->children[1]);
        }
        delete node;
    }
    void add_line(complex<long long> nw, Node* &node, long long l, long long r)
    {
        if(node==0)
        {
            node=new Node(nw);
            return;
        }
        long long m = (l + r) / 2;
        bool lef = (f(nw, l) < f(node->line, l)&&minimize)||((!minimize)&&f(nw, l) > f(node->line, l));
        bool mid = (f(nw, m) < f(node->line, m)&&minimize)||((!minimize)&&f(nw, m) > f(node->line, m));
        if(mid)
        {
            swap(node->line, nw);
        }
        if(r - l == 1)
        {
            return;
        }
        else if(lef != mid)
        {
            add_line(nw, node->children[0], l, m);
        }
        else
        {
            add_line(nw, node->children[1], m, r);
        }
    }
    long long get(long long x, Node* &node, long long l, long long r)
    {
        long long m = (l + r) / 2;
        if(r - l == 1)
        {
            return f(node->line, x);
        }
        else if(x < m)
        {
            if(node->children[0]==0) return f(node->line, x);
            if(minimize) return min(f(node->line, x), get(x, node->children[0], l, m));
            else return max(f(node->line, x), get(x, node->children[0], l, m));
        }
        else
        {
            if(node->children[1]==0) return f(node->line, x);
            if(minimize) return min(f(node->line, x), get(x, node->children[1], m, r));
            else return max(f(node->line, x), get(x, node->children[1], m, r));
        }
    }
public:
    LiChaoTree(long long l=-1000000001,long long r=1000000001,bool mn=false)
    {
        L=l;
        R=r;
        root=0;
        minimize=mn;
        lines=0;
    }
    void AddLine(pair<long long,long long> ln)
    {
        add_line({ln.first,ln.second},root,L,R);
        lines++;
    }
    int number_of_lines()
    {
        return lines;
    }
    long long getOptimumValue(long long x)
    {
        return get(x,root,L,R);
    }
    ~LiChaoTree()
    {
        if(root!=0) clear(root);
    }
};
int main()
{
    return 0;
}
