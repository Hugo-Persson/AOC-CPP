#include <array>
#include <fstream>
#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <string>
#include <vector>

using namespace std;

int main() {
  ifstream in("day_2022_6");
  string line;
  while(getline(in, line)){
    vector<char> currentChunk;
    for(int i = 0; i<13; i++){
      currentChunk.push_back(line[i]);
    }
    for(int i= 13; i<line.length(); i++){
      currentChunk.push_back(line[i]);
      
      set<char> curr;
      for(auto c: currentChunk){
        curr.insert(c);
      }
      if(curr.size() == 14){
        cout << i+1 << endl;
        return 1;
      }
      
      currentChunk.erase(currentChunk.begin());
      
    }
  }

  return 1;
}
