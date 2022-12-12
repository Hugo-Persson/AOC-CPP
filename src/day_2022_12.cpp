#include <algorithm>
#include <array>
#include <cstdint>
#include <fstream>
#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <string>
#include <tuple>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <numeric>

using namespace std;
vector<string> heightMap;
unordered_map<string, int> visited;


struct Edge {
  int toVertex;
  int weightToVertex;
};



string pairToStr(pair<int, int> p){
  return to_string(p.first) + "," + to_string(p.second);
}





int main() {
  ifstream in("day_2022_12");
  
  
  
  int t = INT16_MAX;
  cout << "max:::::::   "<< t << endl;
  string line;
  int currLine = 0;
  pair<int,int> startPos;
  unordered_set<string> visited;
  queue<tuple<int,int, int>> jumpToNode;
  
  while(in >> line){
    heightMap.push_back(line);
    int x = 0;
    for(auto c : line){
      if(c == 'S'){
        startPos = {currLine, x}; 
      } 
      x++;
    }
    currLine++;
  }
  
  int bestPath = std::numeric_limits<int>::max();
  
  jumpToNode.push({startPos.first, startPos.second, 0});
  while(!jumpToNode.empty()){
    
    auto [y,x, length] = jumpToNode.front();jumpToNode.pop();
    
    string place = pairToStr({y,x});
    if(visited.count(place)) continue;
    visited.insert(place);
      
    if(y < 0 || x < 0 || y >= heightMap.size() || x >= heightMap[0].length()){
      continue; // Outside MAP
    }  

    char currElement = heightMap[y][x]; 
    if(currElement == 'S') currElement = 'a';
    else if(currElement == 'E') currElement = 'z';
    
    
    if(heightMap[y][x] == 'E'){
      // Handle exit
      if(length<bestPath) bestPath = length;
      continue;
    }
    
    vector<pair<int,int>> potentialJumps = {{y+1, x}, {y-1, x}, {y, x+1}, {y,x-1}};
    for(auto j : potentialJumps){
      // Do checks
      auto [newY, newX] = j;
      char nextElement = heightMap[newY][newX];
      if(nextElement == 'S') nextElement = 'a';
      else if(nextElement == 'E') nextElement = 'z';

      if(nextElement > (currElement +1)) continue;
      
      jumpToNode.push({j.first, j.second, length+1});
    }
  }
  
  
  cout << "Best path " <<  bestPath  << endl;

  return 1;
}
