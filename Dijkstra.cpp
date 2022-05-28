#include<bits/stdc++.h>
#include<stdio.h>
#define MAX_NODES 100
#define INF 1000000000
using namespace std;
struct Node{
    int Position,Cost;
    Node(int position,int cost)
    {
        Position=position;
        Cost=cost;
    }
};
struct Edge{
    int Position,Cost,Last_Filled_up_Oil,Last_Cost_per_Unit;
    Edge(int position,int cost,int last_filled_up_oil,int last_cost_per_unit)
    {
        Position=position;
        Cost=cost;
        Last_Filled_up_Oil=last_filled_up_oil;
        Last_Cost_per_Unit=last_cost_per_unit;
    }
};
bool operator<(Edge A,Edge B)
{
    return A.Cost>B.Cost;
}
int N,M,costs[MAX_NODES],oil_costs[MAX_NODES],capacity;
vector<Node> Graph[MAX_NODES];
priority_queue<Edge> List;
void setNodes()
{
    scanf("%d",&N);
}
void setEdges()
{
    scanf("%d",&M);
}
void setOilCost()
{
    int i;
    for(i=0;i<N;i++)
    {
        scanf("%d",&oil_costs[i]);
    }
}
void ConstructGraph()
{
    int i,first_node,second_node,cost;
    for(i=0;i<M;i++)
    {
        scanf("%d %d %d",&first_node,&second_node,&cost);
        Graph[first_node].push_back(Node(second_node,cost));
        Graph[second_node].push_back(Node(first_node,cost));
    }
}
void dijkstra(int root_node)
{
    int i,j,oil_cost_per_unit;
    for(i=0;i<N;i++)
    {
        costs[i]=INF;
    }
    costs[root_node]=0;
    List.push(Edge(root_node,0,capacity,oil_costs[root_node]));
    Edge check(0,0,0,0),Modifier(0,0,0,0);
    while(!List.empty())
    {
        check=List.top();
        List.pop();
        if(costs[check.Position]!=check.Cost) continue;
        for(i=0;i<Graph[check.Position].size();i++)
        {
            if(Graph[check.Position][i].Cost<=capacity)
            {
                Modifier.Position=Graph[check.Position][i].Position;
                if(check.Last_Cost_per_Unit<oil_costs[Graph[check.Position][i].Position]&&Graph[check.Position][i].Cost<capacity-check.Last_Filled_up_Oil)
                {
                    Modifier.Last_Cost_per_Unit=check.Last_Cost_per_Unit;
                }
                /*costs[Graph[check.Position][i].Position]=costs[check.Position]+Graph[check.Position][i].Cost;
                List.push(Edge(Graph[check.Position][i].Position,costs[Graph[check.Position][i].Position]));*/
            }
        }
    }
}
int main()
{
    int T;
    scanf("%d",&T);
    while(T--)
    {
        setNodes();
        setEdges();
        setOilCost();
        ConstructGraph();
    }
    return 0;
}
