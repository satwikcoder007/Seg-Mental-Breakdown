
#include <bits/stdc++.h>
using namespace std;

using ll = long long;
ll mod = 1e9;


class segTree{
    public:
       
    vector<int> nums;
    int n;
    vector<int> seg;
    vector<int> lazy;
    
    segTree(int n,vector<int> &nums){
        this->n = n;
        this->nums = nums;
        seg.resize(4*n);
        for(int i=0;i<4*n;i++) lazy.push_back(-1);
    }

    void createTree(int l,int h,int ind){
        
        if(l==h){
            seg[ind] = nums[l];
            return;
        }
        int m = (l+h)/2;
        createTree(l,m,2*ind+1);
        createTree(m+1,h,2*ind+2);

        seg[ind] = min(seg[2*ind+1],seg[2*ind+2]);
    }

    void updateQuery(int l,int h,int L,int H,int val,int ind){
        if(lazy[ind]!=-1){
            seg[ind] = lazy[ind];
            if(l!=h){
                lazy[2*ind+1] = lazy[ind];
                lazy[2*ind+2] = lazy[ind];
            }
            lazy[ind] = -1;
        }
        if(l>H || h<L){
            return;
        }
        if(L<=l && h<=H){
            seg[ind] = val;
            if(l!=h){
                lazy[2*ind+1] = val;
                lazy[2*ind+2] = val;
            } 
        }
        else{
            int m = (l+h)/2;

            updateQuery(l,m,L,H,val,2*ind+1);
            updateQuery(m+1,h,L,H,val,2*ind+2);

            seg[ind] = min(seg[2*ind+1],seg[2*ind+2]);

        }
    } 

    int findQuery(int l,int h,int L,int H,int ind){

        if(lazy[ind]!=-1){
            seg[ind] = lazy[ind];
            if(l!=h){
                lazy[2*ind+1] = lazy[ind];
                lazy[2*ind+2] = lazy[ind];
            }
            lazy[ind] = -1;
        }
        if(L>h || H<l){
            return INT_MAX; 
        }
        if(l>=L && h<=H){ 
            return seg[ind];
        }

        else{  
            int m = (l+h)/2;
            int x = findQuery(l,m,L,H,2*ind+1);
            int y = findQuery(m+1,h,L,H,2*ind+2);
            return min(x,y);
        }
    } 
};
void solve(int n,vector<int> &nums,vector<vector<int>> &queries) {
   
    segTree s1(n,nums);
    s1.createTree(0,n-1,0);
    for(auto it:queries){
        if(it[0]==1){
            s1.updateQuery(0,n-1,it[1],it[2],it[3],0);
        }
        else{
            cout<<s1.findQuery(0,n-1,it[1],it[2],0)<<endl;
        }
    }

}

int main() {
    int n,m;
    cin>>n>>m;
    vector<int> nums(n);
    for(int i=0;i<n;i++) cin>>nums[i];

    vector<vector<int>> queries;

    for(int i=0;i<m;i++){
        int t;
        cin>>t;
        if(t==1){
            int l,r,v;
            cin>>l>>r>>v;
            queries.push_back({t,l,r,v});
        }
        else{
            int l,r;
            cin>>l>>r;
            queries.push_back({t,l,r});
        }
    }
    solve(n,nums,queries);
}




//5 4 2 8 3 5
