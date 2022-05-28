#include<bits/stdc++.h>
#include<vector>
using namespace std;
#define MAX 100000
#define BEGINNING_INDEX 0
#define BEGINNING_TIME 0
struct Edge
{
    int u,v;
    Edge(int U,int V)
    {
        u=U;
        v=V;
    }
};
bool comp(Edge B,Edge A)
{
    return A.u>B.u||(A.u==B.u&&A.v>B.v);
}
vector<int>Graph[MAX+BEGINNING_INDEX];
vector<Edge>Critical_Links;
int dfsStartTime[MAX+BEGINNING_INDEX],dfsEndTime[MAX+BEGINNING_INDEX],lowTime[MAX+BEGINNING_INDEX],Time;
bool visited[MAX+BEGINNING_INDEX];
bool ArticulationVertex[MAX+BEGINNING_INDEX];
void initialize(int n)
{
    int i;
    Time=BEGINNING_TIME;
    //printf("Entered initialize()\n");
    for(i=BEGINNING_INDEX; i<BEGINNING_INDEX+n; i++)
    {
        //printf("Inside initialize(), i=%d\n",i);
        ArticulationVertex[i]=visited[i]=false;
        dfsStartTime[i]=dfsEndTime[i]=lowTime[i]=BEGINNING_TIME;
        while(Graph[i].size()>0) Graph[i].pop_back();
    }
    while(Critical_Links.size()>0)Critical_Links.pop_back();
}
void DFS(int from,int node)
{
    visited[node]=true;
    //printf("Entered from %d to %d.\n",from,node);
    dfsStartTime[node]=++Time;
    lowTime[node]=dfsStartTime[node];
    int i,components=0;
    for(i=0; i<Graph[node].size(); i++)
    {
        if(from==Graph[node][i]) continue;
        if(!visited[Graph[node][i]])
        {
            DFS(node,Graph[node][i]);
            components++;
            if(lowTime[Graph[node][i]]<lowTime[node])
            {
                lowTime[node]=lowTime[Graph[node][i]];
                //printf("%d updated lowTime to %d of %d\n",Graph[node][i],lowTime[node],node);
            }
            if(lowTime[Graph[node][i]]>dfsStartTime[node])
            {
                if(node<Graph[node][i]) Critical_Links.push_back(Edge(node,Graph[node][i]));
                else Critical_Links.push_back(Edge(Graph[node][i],node));
            }
            if(lowTime[Graph[node][i]]>=dfsStartTime[node]&&from!=node)
            {
                ArticulationVertex[node]=true;
            }
        }
        else if(dfsStartTime[Graph[node][i]]<lowTime[node])
        {
            lowTime[node]=dfsStartTime[Graph[node][i]];
            //printf("Back edge from %d updated lowTime to %d of %d\n",Graph[node][i],lowTime[node],node);
            //continue;
        }

    }
    if(from==node&&components>1)
    {
        ArticulationVertex[node]=true;
    }
    //printf("Exited from %d.\n",node);
    dfsEndTime[node]=Time;
}
int main()
{
    int n,T,k;
    //scanf("%d",&T);
    while(scanf("%d",&n)!=EOF)
    {
        int i,u,v,j,m;
        initialize(n);
        for(i=0; i<n; i++)
        {
            scanf(" %d ( %d )",&u,&m);
            for(j=0;j<m;j++)
            {
                scanf(" %d",&v);
                Graph[u].push_back(v);
            }
        }
        for(i=BEGINNING_INDEX; i<BEGINNING_INDEX+n; i++)
        {
            if(!visited[i])
            {
                DFS(i,i);
            }
        }
        sort(Critical_Links.begin(),Critical_Links.end(),comp);
        //printf("Case %d:\n",k);
        printf("%d critical links\n",Critical_Links.size());
        for(i=0 ;i<Critical_Links.size(); i++)
        {
            printf("%d - %d\n",Critical_Links[i].u,Critical_Links[i].v);
        }
        printf("\n");
    }

    return 0;
}
