#include <bits/stdc++.h>
using namespace std;

using ll = long long;
ll mod = 1e9;


class segTree{
    public:
       
    vector<int> nums;
    int n;
    vector<int> seg;
    
    segTree(int n,vector<int> &nums){
        this->n = n;
        this->nums = nums;
        seg.resize(4*n);
    }

    void createTree(int l,int h,int ind){
        
        if(l==h){
            seg[ind] = nums[l];
            return;
        }
        int m = (l+h)/2;
        createTree(l,m,2*ind+1);
        createTree(m+1,h,2*ind+2);

        seg[ind] = max(seg[2*ind+1],seg[2*ind+2]);
    }

    int queryProcessing(int l,int h,int L,int H,int ind){
        if(L>h || H<l){
            return INT_MIN; // if the current range fall completelty outside of the asked query
        }
        if(l>=L && h<=H){ // if the current range fall completelty inside of the asked query
            return seg[ind];
        }

        else{  //partial case we check for both the subtree
            int m = (l+h)/2;
            int x = queryProcessing(l,m,L,H,2*ind+1);
            int y = queryProcessing(m+1,h,L,H,2*ind+2);
            return max(x,y);
        }
    }
};
void solve(int n,vector<int> &nums,vector<vector<int>> &queries) {
   
    segTree s1(n,nums);
    s1.createTree(0,n-1,0);
    for(auto it:queries){
        cout<<s1.queryProcessing(0,n-1,it[0],it[1],0)<<endl;
    }

}

int main() {
    int n,m;
    cin>>n>>m;
    vector<int> nums(n);
    for(int i=0;i<n;i++) cin>>nums[i];

    vector<vector<int>> queries;

    for(int i=0;i<m;i++){
        int l,r;
        cin>>l>>r;
        queries.push_back({l,r});
    }
    solve(n,nums,queries);
}




