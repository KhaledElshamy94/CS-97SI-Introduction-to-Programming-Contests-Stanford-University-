#include <iostream> 
#include <vector>
#include <map> 
#include <algorithm>
using namespace std;


typedef vector<int> vi;
typedef pair<int,int> ii;
typedef vector<vector<pair<int,ii> > > vpii; 
typedef vector<vi> vii;

class UnionFind {

    private : 
      vi parent,rank;
    public: 
      UnionFind(int n) {
          parent.assign(n+1,0);
          rank.assign(n+1,0);
          for(int i=1;i<=n;i++)parent[i] = i ;
      }

      int findSet(int i) { return parent[i] == i ? i : (parent[i] = findSet(parent[i]));} 
      bool isSameSet(int i,int j) {return findSet(i) == findSet(j);} 
      void unionSet(int i,int j){
          if(!isSameSet(i,j)){
              int x = findSet(i), y = findSet(j);
              if(rank[x] > rank[y]) {
                  parent[y] = x ;
              }else {
                  parent[x] = y ;
                  if(rank[x] == rank[y]) rank[y]++;
              }
          }
      }
};


void dfs(int parent,vector<bool> &visited, vpii &adjList,int x,int y, vector<ii> &coordinates){
    visited[parent] = true ;
    coordinates[parent] = ii(x,y); 
    for(int i=0;i<(int)adjList[parent].size();i++){
        int child = adjList[parent][i].first;
        if(!visited[child]){
            int dx = adjList[parent][i].second.first;
            int dy = adjList[parent][i].second.second;
            dfs(child,visited,adjList,x+dx,y+dy,coordinates);
        }
    }
}


int main() {

    int n,m;
    cin>>n>>m;

    vpii adjList(n+1);
    vector<ii> nodes; 
    while (m--)
    {
        /* code */
        int node1,node2,dist;
        char dir;
        scanf("%d %d %d %c", &node1, &node2, &dist, &dir); 

        int dx = 0 , dy = 0 ;
        switch (dir)
        {
        case 'E':
            dx = dist;
            break;
        case 'W':
            dx = -dist;
            break;
        case 'N':
            dy = dist;
            break;
        case 'S':
            dy = -dist;
            break;
        default:
            break;
        }
        adjList[node1].push_back(make_pair(node2,ii(dx,dy)));  
        adjList[node2].push_back(make_pair(node1,ii(-dx,-dy)));  
        nodes.push_back(ii(node1,node2)); 
    }
    
    vector<bool> visited(n+1,false);
    vector<ii> coordinates(n+1); 
    dfs(1,visited,adjList,0,0,coordinates);

    int k;
    scanf("%d",&k);
    UnionFind UF(n); 

    vector<pair<int,ii> > testcases;
    int t = k ;

    while (k--)
    {
        /* code */
        int node1,node2,index;
        cin>>node1>>node2>>index; 
        testcases.push_back(make_pair(index,ii(node1,node2)));
    }
    
    sort(testcases.begin(),testcases.end());
    
    int index = 0; 
    int prevIndex = 0 ;

    while (index < t)
    {
        /* code */
        int Index = testcases[index].first;
        for(int i= 0;i<Index;i++){ 
            UF.unionSet(nodes[i].first,nodes[i].second); 
        }

        int node1 = testcases[index].second.first;
        int node2 = testcases[index].second.second;

        if(!UF.isSameSet(node1,node2)){
            printf("%d\n",-1);
        }else {
            printf("%d\n",abs(coordinates[node1].first - coordinates[node2].first) + abs(coordinates[node1].second - coordinates[node2].second));
        }
        index++;
        prevIndex = Index;
    }
    
    return 0 ;
}
