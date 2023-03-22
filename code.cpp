#include<bits/stdc++.h>
#define endl "\n"
#define ll long long
#define vll vector<ll>
#define pb push_back
#define mod 1000000007
#define MAX 1e9
#define MIN -1e9
#define apna_time_ayega ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
using namespace std;

const int N = 1e5;
vector<vector<ll>> v(N);
bool checkCycle(int v , vector<bool> visited , vector<bool> DFSvisited , vector<vector<ll>> &graph){
    visited[v] = true;
    DFSvisited[v] = true;
    for(auto child : graph[v]){
        if(!visited[child]){
            if(checkCycle(child,visited,DFSvisited,graph)) return true;
        }
        else if(DFSvisited[child]) return true;
    }
    DFSvisited[v] = false;
    return false;
}

bool isCycle(int n , vector<vector<ll>> &graph){
    vector<bool> visited(n+1,0);
    vector<bool> DFSvisited(n+1,0);
    for(int i=1;i<=n;i++){
        if(!visited[i]){
            if(checkCycle(i,visited,DFSvisited,graph)) return true;
        }
    }
    return false;
}

void toposortDFS(int v,vector<vector<ll>> &graph,bool visited[],stack<int> &st){
    visited[v] = true ;
    for(auto child : graph[v]){
        if(!visited[child]){
            toposortDFS(child,graph,visited,st);
        }
    }
    st.push(v);
}

int main()
{
    cout<<"Enter the string of the transaction : ";
    string s;
    getline(cin,s);
    ll len=s.length();
    vector<pair<ll,pair<ll,string>>>vp;
    set<ll>st;
    // 0 for R and 1 for W
    for(int i=0; i<len; i++){
        if(s[i]!=' '){
           if(s[i]=='R'){
               ll num=0;
               while(i+1<len && s[i+1]!='('){
                    i++;
                    num*=10;
                    num+=s[i]-'0';
               }
               st.insert(num);
               i++;
               string var_name="";
               while(i+1<len && s[i+1]!=')'){
                   i++;
                   var_name.push_back(s[i]);
               }
               i++;
               vp.push_back({num,{0,var_name}});
           }
           else if(s[i]=='W'){
               ll num=0;
               while(i+1<len && s[i+1]!='('){
                    i++;
                    num*=10;
                    num+=s[i]-'0';
               }
               i++;
                st.insert(num);
               string var_name="";
               while(i+1<len && s[i+1]!=')'){
                   i++;
                   var_name.push_back(s[i]);
               }
               i++;
               vp.push_back({num,{1,var_name}});
           }
           else{
               i+=8;
               ll num=0;
               while(i+1<len && s[i+1]!='('){
                    i++;
                    num*=10;
                    num+=s[i]-'0';
               }
               i++;
               st.insert(num);
               vp.push_back({num,{2,"-1"}});
           }
        }
    }
    
    ll sz=vp.size();
    ll num_of_tran=st.size();
    // for(int i=0; i<sz; i++){
    //     cout<<vp[i].first<<" "<<vp[i].second.first<<" "<<vp[i].second.second<<endl;
    // }
    for(int i=0; i<sz; i++){
          for(int j=i+1; j<sz; j++){
               if(vp[j].first==vp[i].first && vp[j].second.first==2){
                    break;
               }
               else if(vp[j].first==vp[i].first){
                   continue;
               }
               else{
                   if(vp[j].second.first==vp[i].second.first && vp[i].second.first==0){
                       continue;
                   }
                   else if(vp[j].second.second==vp[i].second.second){
                       v[vp[i].first].push_back(vp[j].first);
                   }
               }
          }
    }
    // for(int i=1; i<=num_of_tran; i++){
    //     ll sz=v[i].size();
    //     cout<<i<<"-->";
    //     for(int j=0; j<sz; j++){
    //         cout<<v[i][j]<<"-->";
    //     }
    //     cout<<endl;
    // }

    //  check for cycle

    if(isCycle(num_of_tran,v)){
        cout<<"Conflict serializable"<<endl;
    }
    else{
        cout<<"Sequence of transaction : "<<endl;
        bool visited[num_of_tran+1] = {false};
        stack<int> st; // for storing element 
        // here we take 1 as vertex 
        for(int i=1 ;i<=num_of_tran;i++){
            if(!visited[i]){
                toposortDFS(i,v,visited,st);
            }
        }

        while(!st.empty()){
            cout<<st.top()<<" ";
            st.pop();
        }
    }

}

// sample test :
// R1(A) R1(B) R2(B) R3(B) W1(A) W2(B)
// Output :
// Sequence of transaction : 
// 3 1 2

// sample test :
// R1(A) R2(A) R1(B) R2(B) R3(B) W1(A) W2(B)
// Output :
// Conflict serializable