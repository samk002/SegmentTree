#include<bits/stdc++.h>

using namespace std;


class segmentTree{
    public:
    int *initial;
    int *tree;

    segmentTree(int n){
        initial = new int[n];
        int a_size = 2*n- 1;
        tree = new int[a_size];
    }

    //build 
    void build(int node,int start,int end);

    //update
    void update(int node,int value,int idx,int start,int end);


    //query
    int query(int node,int start,int end, int l ,int r);


    //print
    void print_array(int *a){
        for(int i=0;i<sizeof(a);i++) cout<<*(a+i)<<" ";
    }

};

void segmentTree::build(int node,int start,int end){
        if(start == end){
        tree[node] = initial[start];
        return;
    }

        int mid = (start+end)/2;
        build((2*node)+1 ,start,mid);
        build((2*node)+2,mid+1,end);

        tree[node] = min(tree[2*node+1],tree[2*node+2]);

}

void segmentTree::update(int node,int value,int idx,int start,int end){
    if(start == end){
        initial[idx] = value;
        tree[node] = value;
    }
    else{
        int mid = (start + end)/2;
        if(idx<=mid) update(2*node+1,value,idx,start,mid);
        else update(2*node+2,value,idx,mid+1,end);

        tree[node] = min(tree[2*node+1],tree[2*node+2]);
    }
}

int segmentTree :: query(int node,int start,int end, int l ,int r){
    if(r<start || l>end){
        return INT_MAX;
    }
    if(l<=start && r>=end){
        return tree[node];
    }

    int mid = (start+end)/2;

    int p = query(2*node+1,start,mid,l,r);
    int q = query(2*node+2,mid+1,end,l,r);

    return min(p,q);
}

int main(){
    int n; cin>>n;
    segmentTree s(n);
    for(int i=0;i<n;i++){
        int data; cin>>data;
        *(s.initial+i) = data;
    }
}