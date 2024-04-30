// import all the library
#include<iostream>
#include<vector>
#include<climits>

using namespace std;

// user define function 
void greedy_path(vector<vector<int>> & graph,int s,vector<int> &path,vector<bool> & visited){
    visited[s] = true;
    vector<int> adj = graph[s];
    int min = INT_MAX,child=-1;
    for(int i=0;i<adj.size();i++){
        if(!visited[i] && adj[i]<min && adj[i]!=0){
            child = i;
            min = adj[i];
        }
    }
    if(child!=-1){
    path.push_back(child);
    greedy_path(graph,child,path,visited);}
    return ; 
}

// this function return the sortest path travelling all the node of the graph using greedy algorithm
vector<int> sortestPath(vector<vector<int>> & graph,int source){
    int size = graph.size();
    vector<int> path;
    path.push_back(source);
    vector<bool> visited(size,false);
    greedy_path(graph,source,path,visited);
    for(int i=0;i<path.size();i++){
        cout<<path[i]<<" ";
    }
    cout<<endl;
    return path;
}



int main(){
    int n = 5;
    vector<vector<int>> graph = {
        {0, 10, 20, 20},
        {10, 0, 35, 25},
        {15, 35, 0, 30},
        {20, 25, 30, 0}
    };
    sortestPath(graph,3);
}