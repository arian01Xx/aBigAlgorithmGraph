#ifndef SOLUTION_HPP
#define SOLUTION_HPP

#include <iostream>
#include <vector>
#include <unordered_map>
#include <queue>

using namespace std;

class SolutionThirtyTwo{
public:
	bool DFS(int src, int time, unordered_map<int,int>& path, vector<bool>& visited, vector<vector<int>>& graph){
		path[src]=time; //registra el tiempo
		visited[src]=true;
		if(src==0) return true;
		for(auto adj: graph[src]){
			if(!visited[adj]){
				//el tiempo va incrementando en 1
				if(DFS(adj,time+1,path,visited,graph)){
					return true;
				}
			}
		}
		path.erase(src);
		return false;
	}
	int mostProfitablePath(vector<vector<int>>& edges, int bob, vector<int>& amount){
		int n=edges.size()+1;
		vector<vector<int>> graph(n);
		for(auto it: edges){
			graph[it[0]].push_back(it[1]);
			graph[it[1]].push_back(it[0]);
		}
		unordered_map<int,int> path; //registra el nodo al que a llegado con su tiempo
		vector<bool> visited(n,false);
		//la funcion se encargará de llenar el vector bool con cada nodo
		DFS(bob,0,path,visited,graph);
		queue<vector<int>> q; //push{src,time,income}
		q.push({0,0,0});
		visited.assign(n,false);
		int ans=INT_MIN;
		while(!q.empty()){
			int src=q.front()[0];
			int time=q.front()[1];
			int income=q.front()[2];
			q.pop();
			visited[src]=true;
			if(path.find(src)==path.end()){
				income+=amount[src];
			}else{
				if(time<path[src]){
					income+=amount[src];
				}else if(time==path[src]){
					income+=(amount[src]/2);
				}
			}
			if(graph[src].size()==1 && src!=0){
				ans=max(ans,income);
			}
			for(auto adj: graph[src]){
				if(!visited[adj]){
					q.push({adj,time+1,income});
				}
			}
		}
		return ans;
	}
};

#endif