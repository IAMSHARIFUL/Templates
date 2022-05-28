#include<bits/stdc++.h>
using namespace std;
#define MOD 998244353
#define MAX 200005
#define MAX_BIT 50
#define PRECISION 0.00000000001
#define INF 2000000000
void remove(int idx);  // TODO: remove value at idx from data structure
void add(int idx);     // TODO: add value at idx from data structure
int get_answer();  // TODO: extract the current answer of the data structure
int block_size;
struct Query {
    int l, r,k, idx;
    bool operator<(Query other) const
    {
        if(l/block_size!=other.l/block_size) return (l<other.l);
        return (l/block_size&1)? (r<other.r) : (r>other.r);
    }
};
vector<int> mo_s_algorithm(vector<Query> queries) {
    vector<int> answers(queries.size());
    sort(queries.begin(), queries.end());

    // TODO: initialize data structure

    int cur_l = 0;
    int cur_r = -1;
    // invariant: data structure will always reflect the range [cur_l, cur_r]
    for (Query q : queries) {
        while (cur_l > q.l) {
            cur_l--;
            add(cur_l);
        }
        while (cur_r < q.r) {
            cur_r++;
            add(cur_r);
        }
        while (cur_l < q.l) {
            remove(cur_l);
            cur_l++;
        }
        while (cur_r > q.r) {
            remove(cur_r);
            cur_r--;
        }
        answers[q.idx] = get_answer();
    }
    return answers;
}

int main()
{
    return 0;
}
