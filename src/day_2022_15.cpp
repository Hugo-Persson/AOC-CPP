#include <array>
#include <fstream>
#include <iostream>
#include <map>
#include <set>
#include <string>
#include <vector>
#include "Split.cpp"
#include <math.h>

using namespace std;

set<int> occupiedPos;

  int checkY = 2000000;

void markPosition(pair<int,int> position, pair<int, int> beaconPos){
  if(position.second != checkY) return;
  occupiedPos.insert(position.first);
}

void markImpossiblePositions(pair<int,int> sensorPosition, pair<int,int> beaconPosition){
  int distance = (abs(sensorPosition.first-beaconPosition.first) + abs(sensorPosition.second - beaconPosition.second)); // X diff + y Diff 
  for(int i = 0; i<=distance; ++i){
    if(sensorPosition.second + i != checkY && sensorPosition.second -i != checkY) continue;

    for(int dX = 0; dX<=distance-i; ++dX){
      markPosition({sensorPosition.first+dX, sensorPosition.second+i}, beaconPosition);
      markPosition({sensorPosition.first-dX, sensorPosition.second+i}, beaconPosition);
      markPosition({sensorPosition.first+dX, sensorPosition.second-i}, beaconPosition);
      markPosition({sensorPosition.first-dX, sensorPosition.second-i}, beaconPosition);
    }
  }
}




int chunkToInt(string s){
  return stoi(s.substr(2));
}

int main() {
  ifstream in("day_2022_15");

  // Create a set of all the positions that can not have sensor
  // Take all positions - the set count to calculate all the possible positions
  // To calculate all positions store max x and y
  string line;
  set<int> beaconX;
  while(getline(in, line)){
    auto chunks = split(line, ' ');
    pair<int,int> sensorPosition = {chunkToInt(chunks[2]), chunkToInt(chunks[3])};
    pair<int,int> beaconPosition = {chunkToInt(chunks[8]), chunkToInt(chunks[9])};
    if(beaconPosition.second == checkY) beaconX.insert(beaconPosition.first);
    
    markImpossiblePositions(sensorPosition, beaconPosition);  
    
  }  
  cout <<occupiedPos.size() - beaconX.size() << endl;

  return 1;
}
