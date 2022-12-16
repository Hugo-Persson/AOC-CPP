#include <array>
#include <fstream>
#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <string>
#include <unordered_map>
#include <vector>
#include "Split.cpp"
using namespace std;


ofstream out("output.txt");

struct Valve{
  string name;
  int flow;
  vector<string> jumps;
  
  
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

struct Jump{
  string to;
  int time;
  int win;
  
  set<string> opened; 
};

queue<Jump> jumps;
void insertAllJumps(Jump& pos){
  auto& node = valves[pos.to];
  if(node.flow != 0 && pos.opened.count(pos.to) == 0){
    for(auto& j : node.jumps){

      Jump newJump = {j, pos.time-2, pos.win + node.flow * (pos.time-1), pos.opened};
      newJump.opened.insert(pos.to);

      jumps.push(newJump);
    }


  }  
  
  for(auto j : node.jumps){

    jumps.push({j, pos.time-1, pos.win, pos.opened});
  }
  
}

int main() {
  ifstream in("day_2022_16");
  out << "Program started " << endl;
  string line;
  while(getline(in, line)){
    auto chunks = split(line, ' ');
    string name = chunks[1];
    vector<string> jumps;
    for(int i = 9; i<chunks.size(); i++){
      jumps.push_back(chunks[i].substr(0, 2));
    }
    Valve valve = {
      name, rateToInt(chunks[4]), jumps
    };
    valves[name] = valve;
  }
  jumps.push({"AA", 30, 0});
  while(!jumps.empty()){
    auto j = jumps.front(); jumps.pop();
    
    if(j.time < 0) continue;

    auto t = table[j.time][j.to];
    bool shouldContinue = false;
    if(t.first <= j.win){
      //if(j.time < 10) out << "Improved jump for " << j.to << " new win is " << j.win << " ttl "  << j.time <<  endl;
      table[j.time][j.to] = {j.win, j.opened}; 
      shouldContinue=true;
    } 
    else if(!includes(j.opened.begin(), j.opened.end(), t.second.begin(), t.second.end())){
      shouldContinue = true;

    }

    if(shouldContinue){
      if(j.time == 0) continue;
      insertAllJumps(j);  
    }


    
    
    
  }
  
  int max = 0;
  for(auto [node, win] : table[0]){
    if(win.first > max) max = win.first;
  }
  
  cout << max << endl;


  return 1;
}




// 2241 too low