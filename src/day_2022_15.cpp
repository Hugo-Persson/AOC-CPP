#include <array>
#include <fstream>
#include <iostream>
#include <map>
#include <optional>
#include <set>
#include <string>
#include <vector>
#include "Split.hpp"
#include <math.h>

using namespace std;

struct Sensor{
  pair<int, int> pos;
  int range;
};

vector<Sensor> sensors;
int maxCoordValue = 4000000;
bool isCovered(pair<int, int> p){
  if(p.first < 0 || p.first > maxCoordValue|| p.second < 0 || p.second > maxCoordValue) return true;

  for(auto s : sensors){
    auto dX =  s.pos.first - p.first;
    auto dY = s.pos.second - p.second;
    auto distanceTo = abs(dX) + abs(dY);
    if(distanceTo <= s.range) return true;
    
  }  
  return false;
}


optional<pair<int,int>> checkEdge(Sensor sensor){
  int d = sensor.range+1;
  for(int dX = -d; dX<d; ++dX){
    int offset = d - abs(dX);
    int xToCheck = sensor.pos.first + dX;
    pair<int, int> firstPos = {xToCheck, sensor.pos.second + offset};
    if(!isCovered(firstPos)) return firstPos;
    pair<int, int> secondPos = {xToCheck, sensor.pos.second - offset};
    if(!isCovered(secondPos)) return secondPos;
  }
  return {};
}

Sensor createSensor(pair<int, int> sensorPosition, pair<int,int> beaconPosition){
  int distance = (abs(sensorPosition.first-beaconPosition.first) + abs(sensorPosition.second - beaconPosition.second)); // X diff + y Diff 

  return {sensorPosition, distance};
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
    auto s = createSensor(sensorPosition, beaconPosition);
    sensors.push_back(s);
      
  }  
  
  for(auto s : sensors){
      auto res = checkEdge(s);
      if(res){
        const long long x = res->first;
        const long long y = res->second;
        cout << x << ", " << y << endl;
        cout << x * 4000000 + y<< endl;
        return 1;
      }
      cout << "Checked one sensor" << endl;
  }  
  return 1;
}
