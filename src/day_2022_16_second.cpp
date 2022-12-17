#include <array>
#include <fstream>
#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include "Split.hpp"
#include "FloydDude.hpp"
#include "SetCompare.hpp"
#include <algorithm>


using namespace std;


ofstream out("output.txt");

struct Valve{
  string name;
  int flow;
  unordered_set<string> jumps;
  
  
  friend ostream& operator<<(ostream& os, const Valve& valve){
    os << "Valve " << valve.name << " with rate " << valve.flow << " and leads to ";
    for(auto j : valve.jumps){
      os << " " << j;
    }
    os << endl;
    return os;
  }
};

array<unordered_map<string, pair<int, set<string>>>, 31> table;
unordered_map<string, Valve> valves;
int rateToInt(string chunk){
  return stoi(chunk.substr(5, chunk.length()-1));
}

unordered_map<string, unordered_map<string, int>> adj;

void calc(string currentNode, int budget, set<string> opened, int val, std::map<std::set<string>, int, bool(*)(const std::set<string>&, const std::set<string>&)>& memo){
  if(budget<=0) return;
  opened.insert(currentNode);
  memo[opened] = max(memo[opened], val);
  for(auto [name, cost] : adj[currentNode]){
    if(opened.count(name)) continue;
    auto v = valves[name];
    if(v.flow == 0) continue;
    auto newBudget = budget-(cost+1);
    calc(name, newBudget, opened, val+v.flow*newBudget, memo);
  }
}



unordered_map<string, unordered_map<string, int>> createAdj(){
  unordered_map<string, unordered_map<string, int>> adj;
  for(const auto& [name1, v1] : valves){
    for(const auto& [name2, v2] : valves){
      if(v1.jumps.contains(name2)){
        adj[name1][name2] = 1;
      }
      else{
        adj[name1][name2] = 100;
      }
    }
  } 
  return adj;
}

int main() {
  ifstream in("day_2022_16_second");

  out << "Program started " << endl;
  string line;
  while(getline(in, line)){
    auto chunks = split(line, ' ');
    string name = chunks[1];
    unordered_set<string> jumps;
    for(int i = 9; i<chunks.size(); i++){
      jumps.insert(chunks[i].substr(0, 2));
    }
    Valve valve = {
      name, rateToInt(chunks[4]), jumps
    };
    valves[name] = valve;
  }


  adj = createAdj();
  floyd(adj);

  std::map<std::set<string>, int, bool(*)(const std::set<string>&, const std::set<string>&)> memo(SetCompare);
  calc("AA", 26, {}, 0, memo);
  int maxV = 0;
  for(auto [opened, val] : memo){
    for(auto [opened2, val2] : memo){
      set<string> overlap;
      set_intersection(opened.begin(), opened.end(), opened2.begin(), opened2.end(), inserter(overlap, overlap.begin()));
      if(overlap.size() > 1) continue;
      maxV = max(maxV, val+val2);
    }
  }  
  cout << maxV;

  return 1;
}




// 2241 too low