#include<bits/stdc++.h>

using namespace std;


class segmentTree{
    public:
    int *initial;
    int *tree;
    int *lazy_tree;

    segmentTree(int n){
        initial = new int[n];
        int a_size = 2*n- 1;
        tree = new int[a_size];
        lazy_tree = new int[a_size];
    }

    //build 
    void build(int node,int start,int end);

    //update
    void update(int node,int value,int idx,int start,int end);

    //lazy_update
    void lazy_update(int node,int start,int end,int l,int r,int value);


    //query
    int query(int node,int start,int end, int l ,int r);

    //lazy_query
    int lazy_query(int node,int start,int end,int l,int r);


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
        initial[idx] += value;
        tree[node] += value;
    }
    else{
        int mid = (start + end)/2;
        if(idx<=mid) update(2*node+1,value,idx,start,mid);
        else update(2*node+2,value,idx,mid+1,end);

        tree[node] = min(tree[2*node+1],tree[2*node+2]);
    }
}

void segmentTree::lazy_update(int node,int start,int end,int l,int r,int value){

    if(lazy_tree[node] != 0){
        tree[node] += lazy_tree[node];
        if(start != end){
            lazy_tree[2*node+1] += lazy_tree[node];
            lazy_tree[2*node+2] += lazy_tree[node]; 
        }
        lazy_tree[node] = 0;
    }

    if(start > r || start > end || end < l) return;

    if(start >=l && end <= r){
        lazy_tree[node] += value;
        
        if(start != end){
            lazy_tree[2*node+1] += value;
            lazy_tree[2*node+2] += value;
        }
        return;
    }
    int mid = (start+end)/2;
    lazy_update(2*node+1,start,mid,l,r,value);
    lazy_update(2*node+2,mid+1,end,l,r,value);
    tree[node] = min(tree[2*node+1],tree[2*node+2]);
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

int segmentTree :: lazy_query(int node,int start,int end,int l,int r){
    if(start > end || start > r || end < l) return INT_MAX;

    if(lazy_tree[node] != 0){
        tree[node] += lazy_tree[node];

        if(start != end){
            lazy_tree[2*node+1] = tree[node];
            lazy_tree[2*node+2] = tree[node];
        }
        lazy_tree[node] = 0;
    }
    if(start >= l && end <= r) return tree[node];

    int mid = (start+end)/2;
    int left=lazy_query(2*node+1,start,mid,l,r);
    int right=lazy_query(2*node+2,mid+1,end,l,r);
    return min(left,right);

}


int main(){
    int n; cin>>n;
    segmentTree s(n);
    for(int i=0;i<n;i++){
        int data; cin>>data;
        *(s.initial+i) = data;
    }
}