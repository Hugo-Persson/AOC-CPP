#include <array>
#include <fstream>
#include <iostream>
#include <map>
#include <set>
#include <string>
#include <vector>

using namespace std;


vector<vector<bool>> room(4, vector<bool>(7, false));
int lastPos = 4; 
struct FallingChunk{
  vector<pair<int,int>> body;

  bool moveDown(){
    bool okMove = true;
    for(auto& p : body){
      if(p.second >= -1){
        // Check if ok move
        if(!(p.second+1 < room.size() && !room[p.second+1][p.first])) {
          okMove = false;
          break;
        }
      }
    }
    if(okMove){
      // DO the move
      for(auto& p : body){
        p.second+=1;
      }

    }
    else{

      // Place stuff
      int topBlock = room.size();
      for(auto p : body){
        room[p.second][p.first] = true;
        topBlock = min(topBlock, p.second);
      }
      for(int i = 0; i<topBlock-room.size(); ++i){

      }

      return false;
    }
  }

  void push(char dir){

  }
};




FallingChunk createChunkFromStart(vector<pair<int,int>> start){
  return {start};
}

int main() {
  ifstream in("day_2022_17");

  vector<vector<pair<int,int>>> shapes;
  shapes.push_back({{2,0}, {3,0}, {4,0}, {5,0}}); // -
  shapes.push_back({{2,-1}, {3,-1}, {3,-2}, {3,0}, {4,-1}});
  shapes.push_back({{2,0}, {3,0}, {4,0}, {4,-1}, {4,-2}});
  shapes.push_back({{2,0}, {2,-1}, {2,-2}, {2,-3}});
  shapes.push_back({{2,0}, {2,-1}, {3,0}, {3,-1}});


  string wind;
  in >> wind;
  int currShapeIndex = 1;
  FallingChunk currentChunk = createChunkFromStart(shapes[0]);
  int stoppedRocks = 0;
  int windIndex = 0;
  while(stoppedRocks < 2022){
    currentChunk.push(wind[windIndex++]);
    if(!currentChunk.moveDown()){
      stoppedRocks++;
      currentChunk = createChunkFromStart(shapes[currShapeIndex++]);

    }
  }


  cout << "answer" << endl;

  return 1;
}
