#include<bits/stdc++.h>
#include<math.h>
#include<vector>
using namespace std;
#define MAX 1001
#define MAX_TEXT 100009
#define BEGIN 0
#define DEFAULT_SEGMENT_TREE_VALUE 0
const int K = 26;
bool found[MAX];
struct Vertex
{
    int next[2][K];
    bool leaf = false;
    int p = -1,e= -1;
    char pch;
    int link = -1;
    int go[2][K];

    Vertex(int p=-1, char ch='$') : p(p), pch(ch)
    {
        fill(begin(next[0]), end(next[0]), -1);
        fill(begin(go[0]), end(go[0]), -1);
        fill(begin(next[1]), end(next[1]), -1);
        fill(begin(go[1]), end(go[1]), -1);
    }
};
bool visit[MAX*MAX];
vector<Vertex> t;
vector<int> Indices[MAX*MAX];
void add_string(int ind,char *s)
{
    int v = 0;
    while (*s)
    {
        char ch=*s;
        int c,f;
        if(ch>='a')
        {
            f=1;
            c=ch-'a';
        }
        else
        {
            f=0;
            c=ch-'A';
        }
        if (t[v].next[f][c] == -1)
        {
            t[v].next[f][c] = t.size();
            t.push_back(Vertex(v, ch));
        }
        v = t[v].next[f][c];
        s++;
    }
    t[v].leaf = true;
    Indices[v].push_back(ind);
}

int go(int v, char ch);

int get_link(int v)
{
    if (t[v].link == -1)
    {
        if (v == 0 || t[v].p == 0)
            t[v].link = 0;
        else
            t[v].link = go(get_link(t[v].p), t[v].pch);
    }
    return t[v].link;
}

int go(int v, char ch)
{
    int c,f;
    if(ch>='a')
    {
        f=1;
        c=ch-'a';
    }
    else
    {
        f=0;
        c=ch-'A';
    }
    if (t[v].go[f][c] == -1)
    {
        if (t[v].next[f][c] != -1)
            t[v].go[f][c] = t[v].next[f][c];
        else
            t[v].go[f][c] = v == 0 ? 0 : go(get_link(v), ch);
    }
    return t[v].go[f][c];
}

int find_exit(int v)
{
    if(t[v].e!=-1) return t[v].e;
    int link=get_link(v);
    if(t[link].leaf||link==0) t[v].e=link;
    else t[v].e=find_exit(link);
    return t[v].e;
}

void Clear()
{
    int i,j,n=t.size();
    for(i=n-1;i>=0;i--)
    {
        visit[i]=false;
        for(j=0;j<Indices[i].size();j++)
        {
            int current=Indices[i][j];
            found[current]=false;
        }
        t.pop_back();
        Indices[i].clear();
    }
    t.push_back(Vertex());
}
queue<int>Nodes;
void traverse(char *s)
{
    //printf("Traverse begun!\n");
    //printf("%s\n",s);
    int i=0,j,v=0;
    visit[v]=true;
    Nodes.push(v);
    while(*(s+i))
    {
        v=go(v,*(s+i));
        if(!visit[v]) Nodes.push(v);
        visit[v]=true;
        i++;
    }
    //printf("First loop done!\n");
    while(!Nodes.empty())
    {
        v=Nodes.front();
        Nodes.pop();
        for(i=0;i<Indices[v].size();i++)
        {
            found[Indices[v][i]]=true;
        }
        v=find_exit(v);
        if(!visit[v])
        {
            visit[v]=true;
            Nodes.push(v);
        }
    }
}
char test[MAX+5];
char text[MAX_TEXT];
int main()
{
    int k,T=1;
    scanf("%d ",&T);
    for(k=1;k<=T;k++)
    {
        gets(text);
        int n,i;
        scanf("%d ",&n);
        t.push_back(Vertex());
        for(i=0;i<n;i++)
        {
            gets(test);
            add_string(i,test);
        }
        //printf("Input done!\n");
        traverse(text);
        for(i=0;i<n;i++)
        {
            if(found[i])
            {
                printf("y\n");
            }
            else
            {
                printf("n\n");
            }
        }
        Clear();
    }
    return 0;
}
