#include<bits/stdc++.h>
#include<math.h>
#include<vector>
#include<stdlib.h>
using namespace std;
#define MAX 400005
#define MOD 998244353
#define INF 2000000000
template <class T>
class treap
{
    struct item
    {
        int prior, cnt;
        T key;
        item *l,*r;
        item(T v)
        {
            key=v;
            l=NULL;
            r=NULL;
            cnt=1;
            prior=rand();
        }
    } *root,*node;
    int cnt (item * it)
    {
        return it ? it->cnt : 0;
    }

    void upd_cnt (item * it)
    {
        if (it)
            it->cnt = cnt(it->l) + cnt(it->r) + 1;
    }

    void split (item * t, T key, item * & l, item * & r)
    {
        if (!t)
            l = r = NULL;
        else if (key < t->key)
            split (t->l, key, l, t->l),  r = t;
        else
            split (t->r, key, t->r, r),  l = t;
        upd_cnt(t);
    }

    void insert (item * & t, item * it)
    {
        if (!t)
            t = it;
        else if (it->prior > t->prior)
            split (t, it->key, it->l, it->r),  t = it;
        else
            insert (it->key < t->key ? t->l : t->r, it);
        upd_cnt(t);
    }

    void merge (item * & t, item * l, item * r)
    {
        if (!l || !r)
            t = l ? l : r;
        else if (l->prior > r->prior)
            merge (l->r, l->r, r),  t = l;
        else
            merge (r->l, l, r->l),  t = r;
        upd_cnt(t);
    }

    void erase (item * & t, T key)
    {
        if (t->key == key)
            merge (t, t->l, t->r);
        else
            erase (key < t->key ? t->l : t->r, key);
        upd_cnt(t);
    }

    T elementAt(item * &t,int key)
    {
        T ans;
        if(cnt(t->l)==key) ans=t->key;
        else if(cnt(t->l)>key) ans=elementAt(t->l,key);
        else ans=elementAt(t->r,key-1-cnt(t->l));
        upd_cnt(t);
        return ans;
    }

    item * unite (item * l, item * r)
    {
        if (!l || !r)  return l ? l : r;
        if (l->prior < r->prior)  swap (l, r);
        item * lt, * rt;
        split (r, l->key, lt, rt);
        l->l = unite (l->l, lt);
        l->r = unite (l->r, rt);
        upd_cnt(l);
        upd_cnt(r);
        return l;
    }
    void heapify (item * t)
    {
        if (!t) return;
        item * max = t;
        if (t->l != NULL && t->l->prior > max->prior)
            max = t->l;
        if (t->r != NULL && t->r->prior > max->prior)
            max = t->r;
        if (max != t)
        {
            swap (t->prior, max->prior);
            heapify (max);
        }
    }

    item * build (T * a, int n)
    {
        if (n == 0) return NULL;
        int mid = n / 2;
        item * t = new item (a[mid], rand ());
        t->l = build (a, mid);
        t->r = build (a + mid + 1, n - mid - 1);
        heapify (t);
        return t;
    }
    void output (item * t,vector<T> &arr)
    {
        if (!t)  return;
        output (t->l,arr);
        arr.push_back(t->key);
        output (t->r,arr);
    }
public:
    treap()
    {
        root=NULL;
    }
    treap(T *a,int n)
    {
        build(a,n);
    }
    void insert(T value)
    {
        node=new item(value);
        insert(root,node);
    }
    void erase(T value)
    {
        erase(root,value);
    }
    T elementAt(int position)
    {
        return elementAt(root,position);
    }
    int size()
    {
        return cnt(root);
    }
    void output(vector<T> &arr)
    {
        output(root,arr);
    }
    int range_query(T l,T r) //(l,r]
    {
        item *previous,*next,*current;
        split(root,l,previous,current);
        split(current,r,current,next);
        int ans=cnt(current);
        merge(root,previous,current);
        merge(root,root,next);
        previous=NULL;
        current=NULL;
        next=NULL;
        return ans;
    }
};
