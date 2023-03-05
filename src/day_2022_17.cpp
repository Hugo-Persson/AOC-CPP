#include <array>
#include <fstream>
#include <iostream>
#include <map>
#include <set>
#include <string>
#include <vector>

using namespace std;


set<pair<int,int>> room;
int maxY = 0;
struct FallingChunk{
  vector<pair<int,int>> body;

  bool moveDown(){
    bool okMove = true;
    for(auto p : body){
      if(p.second > 1){
        // Check if ok move
        if(room.count({p.first, p.second-1})) {
          okMove = false;
          break;
        }
      }
      else{
        okMove = false;
        break;
      }
    }
    if(okMove){
      // DO the move
      for(auto& p : body){
        p.second-=1;
      }
      return true;

    }
    else{

      // Place stuff
      for(auto& b : body){
        //cout << "Placing " << b.first << "," << b.second << endl;
        maxY = max(b.second, maxY);
        room.insert(b);
      }
      

      return false;
    }
  }

  void push(char dir){
    int dX;
    if (dir == '<') dX = -1;
    else dX = 1;
    int reverse = false;
    for(auto& b : body){
      b.first+=dX;
      if(b.first<0 || b.first >= 7) reverse = true; 
    }
    if(reverse){
      
      for(auto& b : body){
         b.first -= dX; 
      }
    }
  }
};




FallingChunk createChunkFromStart(vector<pair<int,int>> start){
  for(auto& b: start){
    b.second=maxY+3+b.second;
  }
  return {start};
}

int main() {
  ifstream in("day_2022_17");

  vector<vector<pair<int,int>>> shapes;
  shapes.push_back({{2,0}, {3,0}, {4,0}, {5,0}}); // -
  shapes.push_back({{2,1}, {3,1}, {3,2}, {3,0}, {4,1}});
  shapes.push_back({{2,0}, {3,0}, {4,0}, {4,1}, {4,2}});
  shapes.push_back({{2,0}, {2,1}, {2,2}, {2,3}});
  shapes.push_back({{2,0}, {2,1}, {3,0}, {3,1}});


  string wind;
  in >> wind;
  int currShapeIndex = 1;
  FallingChunk currentChunk = createChunkFromStart(shapes[0]);
  int stoppedRocks = 0;
  int windIndex = 0;
  while(stoppedRocks < 2022){
    if(windIndex >= wind.length()) windIndex = 0;
    currentChunk.push(wind[windIndex++]);
    if(!currentChunk.moveDown()){
      if(currShapeIndex >= shapes.size()) currShapeIndex = 0;
      stoppedRocks++;
      currentChunk = createChunkFromStart(shapes[currShapeIndex++]);

    }
  }


  cout << maxY << endl;

  return 1;
}
