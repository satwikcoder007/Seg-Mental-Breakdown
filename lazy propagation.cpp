//it is just like normal segment tree
//only differnece is rather than updating the whole range evry time we keep the track of update value for later/lazy updation
//the lazy values are updated if needed and it is propagated down




#include <bits/stdc++.h>
using namespace std;

using ll = long long;
ll mod = 1e9;


class segTree{
    public:
       
    vector<int> nums;
    int n;
    vector<int> seg;

    //this is the replica of the segment tree and only contain zero intitaly 
    //and it will contain the remaining updates that are pending
    vector<int> lazy;
    
    segTree(int n,vector<int> &nums){
        this->n = n;
        this->nums = nums;
        seg.resize(4*n);
        lazy.resize(4*n);
    }

    void createTree(int l,int h,int ind){
        
        if(l==h){
            seg[ind] = nums[l];
            return;
        }
        int m = (l+h)/2;
        createTree(l,m,2*ind+1);
        createTree(m+1,h,2*ind+2);

        seg[ind] = seg[2*ind+1]+seg[2*ind+2];
    }

    void queryProcessing(int l,int h,int L,int H,int val,int ind){
        if(l>H || h<L){

            //even if it does not fall inside the range but the updation of the 
            //seg is done and the lazy values are propagated below
            seg[ind]+=(lazy[ind]*(h-l+1));
            if(l!=h){
                lazy[2*ind+1] += lazy[ind];
                lazy[2*ind+2] += lazy[ind];
            }
            lazy[ind] = 0;
            return;
        }

        if(L<=l && h<=H){

            //lazy updation and propagation 
            seg[ind]+=(lazy[ind]*(h-l+1));
            if(l!=h){
                lazy[2*ind+1] += lazy[ind];
                lazy[2*ind+2] += lazy[ind];
            }
            lazy[ind] = 0;

            //updating it with the actual increment
            //adding it to the lazy value of the children for future updation
            seg[ind]+=(val*(h-l+1));
            if(l!=h){
                lazy[2*ind+1] += val;
                lazy[2*ind+2] += val;
            }
        }
        else{
            //lazy updation and propagation 
            seg[ind]+=(lazy[ind]*(h-l+1));
            if(l!=h){
                lazy[2*ind+1] += lazy[ind];
                lazy[2*ind+2] += lazy[ind];
            }
            lazy[ind] = 0;
            int m = (l+h)/2;
            queryProcessing(l,m,L,H,val,2*ind+1);
            queryProcessing(m+1,h,L,H,val,2*ind+2);
            //updating the segtree
            seg[ind] = seg[2*ind+1]+seg[2*ind+2];
        }
    }    
};
void solve(int n,vector<int> &nums,vector<vector<int>> &queries) {
   
    segTree s1(n,nums);
    s1.createTree(0,n-1,0);
    for(auto it:queries){
        s1.queryProcessing(0,n-1,it[0],it[1],it[2],0);
        cout<<s1.seg[0]<<endl;
    }

}

int main() {
    int n,m;
    cin>>n>>m;
    vector<int> nums(n);
    for(int i=0;i<n;i++) cin>>nums[i];

    vector<vector<int>> queries;

    for(int i=0;i<m;i++){
        int l,r,v;
        cin>>l>>r>>v;
        queries.push_back({l,r,v});
    }
    solve(n,nums,queries);
}
