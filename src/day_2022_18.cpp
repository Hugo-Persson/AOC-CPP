#include <array>
#include <climits>
#include <fstream>
#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <string>
#include <unordered_map>
#include <vector>

using namespace std;

set<tuple<int,int,int>> m;

int countSides(tuple<int,int,int>& pos){
  int sum = 0;
  auto& [x,y,z] = pos;
  if(!m.count({x-1, y,z})) sum++;
  if(!m.count({x+1, y,z})) sum++;
  if(!m.count({x, y+1,z})) sum++;
  if(!m.count({x, y-1,z})) sum++;
  if(!m.count({x, y,z+1})) sum++;
  if(!m.count({x, y,z-1})) sum++;
  return sum;
}

set<tuple<int,int,int>> visited;





int maxX = 0;
int maxY = 0;
int maxZ = 0;

bool posInside(tuple<int,int,int> pos){
 return true; 
}


int main() {
  ifstream in("day_2022_18");
  int x,y,z;
  char garbage;
  while(in >> x >> garbage >> y >> garbage >> z){
    maxX = max(maxX, x);
    maxY = max(maxY, y);
    maxZ = max(maxZ, z);
    m.insert({x,y,z});
  }
  cout << "size " << m.size() << endl;
  int answer = 0;

  queue<tuple<int,int,int>> visistList;
  visistList.push({0,0,0});
  while(!visistList.empty()){
    auto curr = visistList.front(); visistList.pop();
    if(!posInside(curr)) continue;
    if(visited.count(curr)) continue;
    visited.insert(curr);

    answer+= countSides(curr);

    auto [x,y,z] = curr;
    
    visistList.push({x+1, y,z});
    visistList.push({x-1, y,z});
    visistList.push({x, y+1,z});
    visistList.push({x, y-1,z});
    visistList.push({x, y,z+1});
    visistList.push({x, y,z-1});
    
  }
  
  //assert(answer == 64);
  cout << answer << endl;
  return 1;
}
