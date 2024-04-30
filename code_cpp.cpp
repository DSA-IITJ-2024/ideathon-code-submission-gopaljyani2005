// using  libraries
#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include<climits>

using namespace std;

// algorithm class
class GeneticAlgorithmTSP {
//intialiaztion of the all parameter  
private:
    vector<vector<int>> graph;
    int populationSize;
    double mutationRate;
    int generations;
// constructor of the using class 
public:
    GeneticAlgorithmTSP(vector<vector<int>> graph, int populationSize = 10, double mutationRate = 0.01, int generations = 100) {
        this->graph = graph;
        this->populationSize = populationSize;
        this->mutationRate = mutationRate;
        this->generations = generations;
    }


// ------------------------------------------------------------------------------------------
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
    cout<<endl;
    return path;
}



    void printing(vector<vector<int>> graph){
        for(int i=0;i<graph.size();i++){
            for(int j=0;j<graph[0].size();j++){
                cout<<graph[i][j]<<" ";
            }
            cout<<endl;
        }
    }

//-----------------------------------------------------------------------------------------


    vector<vector<int>> initialPopulation() {
        vector<vector<int>> population;
        const int numCities = graph.size();

// this code is generate random path 
        /*for (int i = 0; i < populationSize; ++i) {
            vector<int> route(numCities);
            for (int j = 0; j < numCities; ++j) {
                route[j] = j;
            }
            random_shuffle(route.begin() + 1, route.end());
            population.push_back(route);
        }*/

//this code is generate path using greedy alrorithm 
        for(int i=0;i<graph.size();i++){
            population.push_back(sortestPath(graph,i));
        }
        
        return population;
    }

    double distance(int city1, int city2) {
        return graph[city1][city2];
    }

    double fitness(const vector<int>& route) {
        double totalDistance = 0;
        for (int i = 0; i < route.size() - 1; ++i) {
            totalDistance += distance(route[i], route[i + 1]);
        }
        totalDistance += distance(route.back(), route[0]);
        return 1 / totalDistance;
    }

    vector<int> selection(const vector<vector<int>>& population) {
        vector<pair<double, vector<int>>> rankedRoutes;
        for (const auto& route : population) {
            rankedRoutes.emplace_back(fitness(route), route);
        }
        sort(rankedRoutes.rbegin(), rankedRoutes.rend()); // Sort routes based on fitness
        return rankedRoutes[0].second;
    }

    vector<int> breed(const vector<int>& parent1, const vector<int>& parent2) {
        int start = rand() % parent1.size();
        int end = rand() % parent1.size();
        if (start > end) {
            swap(start, end);
        }

        vector<int> child(parent1.size(), -1);
        for (int i = start; i <= end; ++i) {
            child[i] = parent1[i];
        }

        int j = 0;
        for (int i = 0; i < parent2.size(); ++i) {
            if (j == start) {
                j = end + 1;
            }
            if (find(child.begin(), child.end(), parent2[i]) == child.end()) {
                child[j] = parent2[i];
                j++;
            }
        }

        return child;
    }

    void mutate(vector<int>& route) {
        for (int i = 0; i < route.size(); ++i) {
            if ((double)rand() / RAND_MAX < mutationRate) {
                int j = rand() % route.size();
                swap(route[i], route[j]);
            }
        }
    }

    void evolve() {
        vector<vector<int>> population = initialPopulation();
        for (int i = 0; i < generations; ++i) {
            vector<int> bestRoute = selection(population);
            cout << "Generation " << i + 1 << ", Best route: ";
            for (int city : bestRoute) {
                cout << city << " ";
            }
            cout << endl;
            vector<vector<int>> newPopulation;
            newPopulation.push_back(bestRoute);
            for (int j = 1; j < populationSize; ++j) {
                int parent1Index = rand() % population.size();
                int parent2Index = rand() % population.size();
                vector<int> child = breed(population[parent1Index], population[parent2Index]);
                mutate(child);
                newPopulation.push_back(child);
            }
            population = newPopulation;
        }
    }
};

int main() {
    srand(time(0));

    // intialization the number of the city in the our porblem 
    int n;
    cout<<"enter the number of the city in the our problem:";
    cin>>n;

    // intialization the distance matrix
    vector<vector<int>> graph;
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            cin>>graph[i][j];
        }
    }

    // vector<vector<int>> graph = {
    //     {0, 10, 20, 20, 6},
    //     {10, 0, 35, 25, 8},
    //     {15, 35, 0, 30, 11},
    //     {20, 25, 30, 0, 21},
    //     {10, 12, 34, 8, 0}
    // };

    GeneticAlgorithmTSP tspGA(graph);
    tspGA.evolve();

    return 0;
}
