#include <array>
#include <fstream>
#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <string>
#include <unordered_map>
#include <vector>

using namespace std;


void floyd(unordered_map<string, unordered_map<string, int>>& adj){
    for(const auto& [k, waste] : adj){
        for(const auto& [i, adj2] : adj){
            for(const auto& [j, weight] : adj2){
                adj[i][j] = min(adj[i][j], adj[i][k] + adj[k][j]);
            }
        }
    }
}