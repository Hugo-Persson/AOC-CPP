#include <array>
#include <fstream>
#include <iostream>
#include <map>
#include <set>
#include <string>
#include <vector>

using namespace std;


int ctoi(char c){
  return c - 48;
}

bool canReachEdge(int r, int c,  vector<string>& map){
  

  bool canReachUp = true;
  for(int i = 0; i<r; ++i){

    if(ctoi(map[i][c]) >= ctoi(map[r][c])){
      canReachUp = false;
      break;
    }
  }
  if(canReachUp) return true;

  bool canReachDown = true;
  for(int i = r+1; i<map.size(); ++i){

    if(ctoi(map[i][c]) >= ctoi(map[r][c])){
      canReachDown = false;
      break;
    }
  }
  if(canReachDown) return true;

  bool canReachLeft = true;
  for(int i = 0; i<c; ++i){

    if(ctoi(map[r][i]) >= ctoi(map[r][c])){
      canReachLeft = false;
      break;
    }
  }
  if(canReachLeft) return true;


  bool canReachRight = true;
  for(int i = c+1; i<map[0].length(); ++i){

    if(ctoi(map[r][i]) >= ctoi(map[r][c])){
      canReachRight = false;
      break;
    }
  }
  if(canReachRight) return true;


  
  //cout << "Returning false for " << x << ", " << y << endl;
  return false;
}


int calcScenic(int r, int c,  vector<string>& map){
  
  int upScenic = 0;
  for(int i = r-1; i>=0; --i){
    upScenic++;
    if(ctoi(map[i][c]) >= ctoi(map[r][c])){
      break;
    }
    
  }

  int downScenic = 0;
  for(int i = r+1; i<map.size(); ++i){
    downScenic++;
    if(ctoi(map[i][c]) >= ctoi(map[r][c])){
      break;
    }
  }

  int leftScenic = 0;
  for(int i = c-1; i>=0; --i){
    ++leftScenic;
    if(ctoi(map[r][i]) >= ctoi(map[r][c])){
      break;
    }
  }


  int rightScenic = 0;
  for(int i = c+1; i<map[0].length(); ++i){
    ++rightScenic;
    if(ctoi(map[r][i]) >= ctoi(map[r][c])){
      break;
    }
  }

  return leftScenic*rightScenic*upScenic*downScenic;
}


int main() {
  ifstream in("day_2022_8");

  vector<string> map;
  string line;
  while(in >> line){
    map.push_back(line);
  }
  
  int maxScenic = 0;
  for(int i = 1; i < map.size()-1; ++i){
    for(int n = 1; n<line.length()-1; ++n){
      int curr = calcScenic(i, n, map);
      if(curr > maxScenic) maxScenic = curr;
    }
  }
  //cout << "Total:" << total << endl;
  
  cout << maxScenic << endl;

  return 1;
}
