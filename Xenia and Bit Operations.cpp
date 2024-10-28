#include <bits/stdc++.h>
using namespace std;

using ll = long long;
ll mod = 1e9;


class segTree{
    public:
       
    vector<ll> nums;
    ll n;
    vector<ll> seg;
    
    segTree(ll n,vector<ll> &nums){
        this->n = n;
        this->nums = nums;
        seg.resize(4*n);
    }

    void createTree(ll l,ll h,ll ind,int flag){
        if(l==h){
            seg[ind] = nums[l];
            return;
        }
        ll m = (l+h)/2;
        createTree(l,m,2*ind+1,!flag);
        createTree(m+1,h,2*ind+2,!flag);

        if(flag){
            seg[ind] = seg[2*ind+1]|seg[2*ind+2];
        }
        else{
            seg[ind] = seg[2*ind+1]^seg[2*ind+2];
        }
        return;
    }

    void updateTree(ll l,ll h,ll ind,ll target,ll val,int flag){
        if(l==h){
            nums[target] = val;
            seg[ind] = val;
            return;
        }
        ll m = (l+h)/2;
        if(target<=m){
            updateTree(l,m,2*ind+1,target,val,!flag);
        }
        else{
            updateTree(m+1,h,2*ind+2,target,val,!flag);
        }
        if(flag){
            seg[ind] = seg[2*ind+1]|seg[2*ind+2];
        }
        else{
            seg[ind] = seg[2*ind+1]^seg[2*ind+2];
        }
    }
};
void solve() {
   
    ll n,m;
    cin>>n>>m;
    vector<ll> nums;
    vector<vector<ll>> queries;
    for(ll i=0;i<pow(2,n);i++){
        ll v;
        cin>>v;
        nums.push_back(v);
    }
    for(ll i=0;i<m;i++){
        ll x,y;
        cin>>x>>y;
        queries.push_back({x,y});
    }

    ll size = pow(2,n);
    segTree s1(pow(2,n),nums);
    int op = (n%2==0) ? 0 : 1;
    s1.createTree(0,size-1,0,op);


    for(auto it:queries){
        s1.updateTree(0,size-1,0,it[0]-1,it[1],op);
        cout<<s1.seg[0]<<endl;
    }
   
}

int main() {
    solve();
}
