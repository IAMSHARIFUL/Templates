#include<bits/stdc++.h>
#include<vector>
using namespace std;
#define MAX 200
#define BEGIN 1
#define NOT_CALCULATED 2
#define CALCULATED 0
#define BEING_CALCULATED 1
#define HIGHEST 1000
#define INF 1000000000
struct Node
{
    int node,capacity,opposite_index,cost;
    bool LevelSetVisit;
    Node(int n,int c,int co,int oi,bool lsv)
    {
        node=n;
        capacity=c;
        cost=co;
        opposite_index=oi;
        LevelSetVisit=lsv;
    }
};
vector<Node>Graph[MAX+BEGIN];
int cost[MAX+BEGIN],parent[MAX+BEGIN][2];
void clearGraph(int N)
{
    int i;
    for(i=0; i<BEGIN+N; i++)
    {
        while(Graph[i].size()>0)
        {
            Graph[i].pop_back();

        }
    }
}
int ShortestPath(int source,int sink,int n)
{
    int M[MAX+BEGIN];
    int i,j;
    deque<int>q;
    for(i=0; i<BEGIN+n; i++)
    {
        cost[i]=INF;
        M[i]=NOT_CALCULATED;
    }
    cost[source]=0;
    M[source]=BEING_CALCULATED;
    q.push_back(source);
    //printf("%d is pushed\n",source);
    while(!q.empty())
    {
        int n=q.front();
        q.pop_front();
        M[n]=CALCULATED;
        for(i=0; i<Graph[n].size(); i++)
        {
            int child=Graph[n][i].node;
            if(Graph[n][i].capacity>0&&cost[child]>cost[n]+Graph[n][i].cost)
            {
                cost[child]=cost[n]+Graph[n][i].cost;
                //printf("Cost for %d = %d\n",child,cost[child]);
                parent[child][0]=n;
                parent[child][1]=i;
                if(M[child]==NOT_CALCULATED)
                {
                    M[child]=BEING_CALCULATED;
                    q.push_back(child);
                    //printf("%d is pushed back\n",child);
                }
                else if(M[child]==CALCULATED)
                {
                    q.push_front(child);
                    M[child]=BEING_CALCULATED;
                    //printf("%d is pushed front\n",child);
                }
            }
        }
    }
    return cost[sink];
}
int MinCostFlow(int source,int sink,int n,int demandFlow)
{
    int flow=0;
    int Cost=0;
    int cost=0;
    do
    {
        cost=ShortestPath(source,sink,n);
        int remaining=demandFlow-flow;
        if(cost<INF)
        {
            int node=sink;
            int f=remaining;
            while(node!=source)
            {
                int ind=parent[node][1];
                int p=parent[node][0];
                int possibleFlow=Graph[p][ind].capacity;
                if(possibleFlow<f)
                {
                    f=possibleFlow;
                }
                node=p;
            }
            Cost=Cost+cost*f;
            flow=flow+f;
            node=sink;
            while(node!=source)
            {
                int p=parent[node][0];
                int pind=parent[node][1];
                int ind=Graph[p][pind].opposite_index;
                Graph[p][pind].capacity-=f;
                //printf("Capacity from %d to %d is updated to %d\n",p,Graph[p][pind].node,Graph[p][pind].capacity);
                Graph[node][ind].capacity+=f;
                //printf("Capacity from %d to %d is updated to %d\n",node,Graph[node][ind].node,Graph[node][ind].capacity);
                node=p;
            }
        }
        //printf("Flow is %d, cost is %d\n",flow,Cost);
    }while(flow<demandFlow&&cost<INF);
    if(flow==demandFlow) return Cost;
    else return -1;
}
int main()
{
    int T,l;
    scanf("%d",&T);
    for(l=1;l<=T;l++)
    {
        int N;
        int i,j;
        scanf("%d",&N);
        clearGraph(N*2+1);
        for(i=1;i<=N;i++)
        {
            Graph[i].push_back(Node(0,0,0,Graph[0].size(),false));
            Graph[0].push_back(Node(i,1,0,Graph[i].size()-1,false));
            Graph[N+i].push_back(Node(2*N+1,1,0,Graph[2*N+1].size(),false));
            Graph[2*N+1].push_back(Node(N+i,0,0,Graph[N+i].size()-1,false));
        }
        for(i=1;i<=N;i++)
        {
            for(j=1;j<=N;j++)
            {
                int c;
                scanf("%d",&c);
                Graph[i].push_back(Node(j+N,1,HIGHEST-c,Graph[j+N].size(),false));
                Graph[j+N].push_back(Node(i,0,-(HIGHEST-c),Graph[i].size()-1,false));
            }
        }
        int cost=MinCostFlow(0,2*N+1,2*N+1,N);
        int profit=N*HIGHEST-cost;
        printf("Case %d: %d\n",l,profit);
    }
    return 0;
}
