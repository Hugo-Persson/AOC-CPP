#include <array>
#include <fstream>
#include <iostream>
#include <map>
#include <set>
#include <string>
#include <unordered_map>
#include <vector>
#include <sstream>
#include <math.h>
using namespace std;

inline std::vector<std::string> split(const std::string& s, char delimiter) {
  std::vector<std::string> tokens;
  std::string              token;
  std::istringstream       tokenStream(s);
  while (std::getline(tokenStream, token, delimiter)) {
    tokens.push_back(token);
  }
  return tokens;
}

pair<int,int> parsePositionString(string s){
  auto chunks = split(s, ',');
  return {stoi(chunks[0]), stoi(chunks[1])};
}


unordered_map<int, unordered_map<int, bool>> rockMap;

// Outer pair is instruciton with first element being from pos and second to pos
vector<pair<pair<int,int>, pair<int,int>>> instructions;



void executeInstructions(){
  for(auto p : instructions){
    auto [f, s] = p;
    if(f.first == s.first){
      
      for(int i = min(f.second, s.second); i<=max(f.second, s.second); ++i){
        // cout << "Setting " << f.first << "," << i<< endl;
        rockMap[i][f.first] = true;
      }      
    }
    else{
      
      for(int i = min(f.first, s.first); i<= max(f.first, s.first); ++i){
        // cout << "Setting " <<i<< " , " << f.second << endl;
        rockMap[f.second][i] = true;
      }      
    }
  }
}

int maxX = 0;
int maxY = 0;
bool simulateSandFall(int y, int x){
  
  if(y >= maxY) return false;
  if(!rockMap[y+1][x]) return simulateSandFall(y+1,x);
  if(!rockMap[y+1][x-1]) return simulateSandFall(y+1,x-1);
  if(!rockMap[y+1][x+1]) return simulateSandFall(y+1, x+1);
  
  cout << "Placing sand " << x << ", " << y << endl;
  rockMap[y][x] = true;
  return true;
}


int main() {
  ifstream in("day_2022_14");
  
  // Have a map of boolenas indicating if a certain block is blocked


  string line;
  while(getline(in, line)){
    auto positions = split(line, ' ');
    vector<string> parsedInstructions;
    for(auto p : positions){
      if(p == "->") continue;
      parsedInstructions.push_back(p);
    }
    for(int i = 0; i<parsedInstructions.size()-1; ++i){
      auto first = parsePositionString(parsedInstructions[i]);
      auto second = parsePositionString(parsedInstructions[i+1]);
      
      maxX = max(first.first, maxX);
      maxX = max(second.first, maxX);
      maxY = max(first.second, maxY);
      maxY = max(second.second, maxY);
      
      instructions.push_back({first, second});  
    }
  }  
  
  executeInstructions();
  int falls = 0;
  cout<< rockMap.size() << endl;
  while(simulateSandFall(0, 500)){
    falls++;
  }
  cout << falls << endl;

  return 1;
}
