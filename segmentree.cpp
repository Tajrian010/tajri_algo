//segmnet tree without lazy
#include<bits/stdc++.h>

using namespace std;

int ara[]={1,2,3,4,5,6,7,8};

int tree[40];


void build_tree(int node,int b,int e){
    if(b>e)return;
    if(b==e){
        tree[node]=ara[b];
        return;
    }
    int mid=(b+e)/2;
    int left=2*node;
    int right=2*node+1;
    build_tree(left,b,mid);
    build_tree(right,mid+1,e);
    tree[node]=tree[left]+tree[right];
    //cout<<tree[node]<<endl;
    return;
}




void update(int node,int b,int e,int pos,int v){ // pos bolte main array er position koto tai bujhacche
    if(b==e){
        tree[node]+=v;
        return;
    }
    int mid=(b+e)/2;
    int left=2*node;
    int right=2*node+1;
    if(pos<=mid)update(left,b,mid,pos,v);
    else update(right,mid+1,e,pos,v);
    tree[node]=tree[left]+tree[right];
    return;
}

int quary(int node,int b,int e,int l,int r)
{
    if(r<b || e<l)return 0;
    if(l<=b && e<=r)return tree[node];
    int mid=(b+e)/2;
    int left=2*node;
    int right=2*node+1;
    int x=quary(left,b,mid,l,r);
    int y=quary(right,mid+1,e,l,r);

    return x+y;

}

void update_range(int node,int b,int e,int l,int r,int v){
    if(r<b || e<l)return;
    if(b==e){
        tree[node]+=v;
        return;
    }
    int mid=(b+e)/2;
    int left=2*node;
    int right=2*node+1;
    update_range(left,b,mid,l,r,v);
    update_range(right,mid+1,e,l,r,v);
    tree[node]=tree[left]+tree[right];
    return;

}

int main()
{
    int i;
    build_tree(1,0,7);
    int l,r;
    cin>>l>>r;
    int z=quary(1,0,7,l,r);
    cout<<z<<endl;
    update(1,0,7,3,1);
    z=quary(1,0,7,l,r);
    //cout<<tree[1]<<endl;
    cout<<z<<endl;
    update_range(1,0,7,0,3,1);
    z=quary(1,0,7,l,r);
    cout<<z<<endl;


}


//segment tree with lazy

#include<bits/stdc++.h>

using namespace std;

int ara[]={1,2,3,4,5,6,7,8};

struct node{
    int prop=0;//intially propagataion 0;

    int value;
};

struct node tree[42];

void build_tree(int node,int b,int e){
    if(b>e)return;
    if(b==e){
        tree[node].value=ara[b];
        tree[node].prop=0;
        return;
    }
    int mid=(b+e)/2;
    int left=2*node;
    int right=2*node+1;
    build_tree(left,b,mid);
    build_tree(right,mid+1,e);
    tree[node].value=tree[left].value+tree[right].value;
    tree[node].prop=0;
    //cout<<tree[node]<<endl;
    return;
}

void update_range(int node,int b,int e,int i,int j,int x){
    if(i>e || j<b) return;
    if(b>=i && e<=j){
        tree[node].prop+=x;
        tree[node].value+=((j-i+1)*x);
        return;
    }
    int mid=(b+e)/2;
    int left=2*node;
    int right=2*node+1;
    update_range(left,b,mid,i,j,x);
    update_range(right,mid+1,e,i,j,x);
    tree[node].value=tree[left].value+tree[right].value;
    return;

}

int quary(int node,int b,int e,int i,int j,int carry)
{
    if(i>e || j<b)return 0;
    if(b>=i && e<=j)return tree[node].value+carry*(e-b+1);
    int mid=(b+e)/2;
    int left=2*node;
    int right=2*node+1;
    int x=quary(left,b,mid,i,j,carry+tree[node].prop);
    int y=quary(right,mid+1,e,i,j,carry+tree[node].prop);

    return x+y;

}

int main()
{
    build_tree(1,0,7);
    update_range(1,0,7,0,3,1);
    printf("%d\n",quary(1,0,7,3,3,0));


}

