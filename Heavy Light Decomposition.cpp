#include <bits/stdc++.h>
#include <vector>
#include<math.h>
#include<string.h>
using namespace std;
#define MAX 100005
#define MOD 1000000007
#define SMOD 998244353
#define GMAX 19
#define INF 2000000000000000000
#define EPS 0.0000000001
#define FASTIO ios_base::sync_with_stdio(false);cin.tie(NULL)
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
#include <ext/pb_ds/detail/standard_policies.hpp>
class HeavyLightDecomposition
{
    vector<int> *Graph;
    int *subtree,*heavy_child;
    int root,n;
    bool one_based;
    int subtree_size(int node,int parent=-1)
    {
        subtree[node]=1;
        heavy_child[node]=-1;
        int i,temp;
        for(i=0;i<Graph[node].size();i++)
        {
            if(parent==Graph[node][i]) continue;
            temp=subtree_size(Graph[node][i],node);
            if(heavy_child[node]==-1||subtree[heavy_child[node]]<temp)
            {
                heavy_child[node]=Graph[node][i];
            }
            subtree[node]+=temp;
        }
        return subtree[node];
    }
    void decompose(int node,vector<pair<int,pair<int,int> > > &arr,int parent=-1,int chain_head_position=0)
    {
        arr.push_back(make_pair(node,make_pair(parent,chain_head_position)));
        int i;
        for(i=0;i<Graph[node].size();i++)
        {
            if(parent==Graph[node][i]) continue;
            if(heavy_child[node]!=Graph[node][i]) continue;
            decompose(Graph[node][i],arr,node,chain_head_position);
            break;
        }
        for(i=0;i<Graph[node].size();i++)
        {
            if(parent==Graph[node][i]) continue;
            if(heavy_child[node]==Graph[node][i]) continue;
            decompose(Graph[node][i],arr,node,arr.size());
        }
    }
public:
    HeavyLightDecomposition(int n,int root=1,bool one=true)
    {
        this->n=n;
        this->root=root;
        one_based=one;
        Graph=new vector<int>[n+one_based];
        subtree=new int[n+one_based];
        heavy_child=new int[n+one_based];
    }
    bool add_edge(int u,int v)
    {
        int low=one_based,high=n-(!one_based);
        if(min(u,v)<low||max(u,v)>high) return false;
        Graph[u].push_back(v);
        Graph[v].push_back(u);
        return true;
    }
    void get_decomposed_tree(vector<pair<int,pair<int,int> > > &arr)
    {
        arr.clear();
        subtree_size(root);
        decompose(root,arr);
    }
    ~HeavyLightDecomposition()
    {
        int i;
        for(i=0;i<n+one_based;i++)
        {
            Graph[i].clear();
        }
        delete []Graph;
        delete []heavy_child;
        delete []subtree;
    }
};
vector<pair<int,pair<int,int> > > decomposed_graph;
int P[MAX],values[MAX],position[MAX];
bool queries[MAX];
vector<pair<int,int> > Non_Tree_Edges,Query_Edges;
int Find(int x)
{
    if(P[x]==x) return x;
    else
    {
        P[x]=Find(P[x]);
        return P[x];
    }
}
bool Join(int x,int y)
{
    int PoX=Find(x),PoY=Find(y);
    if(PoX==PoY) return false;
    else if(PoX<PoY)
    {
        P[PoY]=PoX;
    }
    else
    {
        P[PoX]=PoY;
    }
    return true;
}
pair<bool,int> segment_tree[MAX*4];
void build(int index,int l,int r)
{
    segment_tree[index].first=true;
    if(l==r)
    {
        segment_tree[index].second=values[decomposed_graph[l].first];
        return;
    }
    int m=(l+r)/2;
    build(index*2,l,m);
    build(index*2+1,m+1,r);
    segment_tree[index].second=segment_tree[index*2].first*segment_tree[index*2].second+segment_tree[index*2+1].first*segment_tree[index*2+1].second;
}
void update(int index,int l,int r,int L,int R)
{
    if(l>R||r<L||(!segment_tree[index].first)) return;
    if(L<=l&&r<=R)
    {
        segment_tree[index].first=false;
        return;
    }
    int m=(l+r)/2;
    update(index*2,l,m,L,R);
    update(index*2+1,m+1,r,L,R);
    segment_tree[index].second=segment_tree[index*2].first*segment_tree[index*2].second+segment_tree[index*2+1].first*segment_tree[index*2+1].second;
}
void update_tree(int u,int v,int n)
{
    u=position[u];
    v=position[v];
    for(;u>=0&&v>=0&&decomposed_graph[u].second.second!=decomposed_graph[v].second.second;v=position[decomposed_graph[decomposed_graph[v].second.second].second.first])
    {
        if(decomposed_graph[u].second.second>decomposed_graph[v].second.second) swap(u,v);
        update(1,0,n-1,decomposed_graph[v].second.second,v);
    }
    if(!(u>=0&&v>=0)) return;
    if(u!=v)
    {
        if(u>v) swap(u,v);
        update(1,0,n-1,u+1,v);
    }
}
int main()
{
    freopen("bridges.in","r",stdin);
    int n,m,k,i;
    int delta=0;
    scanf("%d %d",&n,&m);
    HeavyLightDecomposition hld(n);
    for(i=1;i<=n;i++)
    {
        P[i]=i;
        values[i]=(i!=1);
    }
    for(i=0;i<m;i++)
    {
        int u,v;
        scanf("%d %d",&u,&v);
        if(Join(u,v))
        {
            hld.add_edge(u,v);
            //printf("%d - %d\n",u,v);
        }
        else
        {
            Non_Tree_Edges.push_back(make_pair(u,v));
        }
    }
    scanf("%d",&k);
    for(i=0;i<k;i++)
    {
        int u,v;
        scanf("%d %d",&u,&v);
        if(Join(u,v))
        {
            hld.add_edge(u,v);
            //printf("%d - %d from query\n",u,v);
            delta--;
            queries[i]=true;
        }
        Query_Edges.push_back(make_pair(u,v));
    }
    fclose(stdin);
    for(i=2;i<=n;i++)
    {
        if(P[i]==i)
        {
            delta--;
            hld.add_edge(1,i);
            //printf("%d - %d\n",1,i);
        }
    }
    hld.get_decomposed_tree(decomposed_graph);
    for(i=0;i<decomposed_graph.size();i++)
    {
        position[decomposed_graph[i].first]=i;
        //printf("pos[%d]=%d\n",decomposed_graph[i].first,i);
    }
    build(1,0,n-1);
    //printf("Built!\n");
    for(i=0;i<Non_Tree_Edges.size();i++)
    {
        update_tree(Non_Tree_Edges[i].first,Non_Tree_Edges[i].second,n);
    }
    //printf("NTE done!\n");
    freopen("bridges.out","w",stdout);
    for(i=0;i<k;i++)
    {
        if(queries[i])
        {
            delta++;
        }
        else
        {
            update_tree(Query_Edges[i].first,Query_Edges[i].second,n);
        }
        printf("%d\n",delta+segment_tree[1].first*segment_tree[1].second);
    }
    fclose(stdout);
    return 0;
}
