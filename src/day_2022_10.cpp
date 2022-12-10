#include <array>
#include <fstream>
#include <iostream>
#include <map>
#include <set>
#include <string>
#include <vector>
#include <optional>

using namespace std;




vector<int> instructions; 

vector<vector<bool> > screen (6, vector<bool>(40));


int main() {
  ifstream in("day_2022_10");
  string token;
  while(in >> token){
    if(token == "noop"){
      instructions.push_back(0);
    }
    else if(token == "addx"){
     instructions.push_back(0);
      
      
      int increaser;
      in >> increaser;
      instructions.push_back(increaser);
    }
  }
  
  int xPos = 0;
  int yPos = 0;
  int x = 0;
  int sum = 0;
  for(auto i : instructions){
    
    bool currLit = xPos >= x && xPos < x+3;
    screen[yPos][xPos] = currLit;
    
        
    xPos++;
    if(xPos == 40){
      yPos++;
      xPos =0;
    }
    x+= i;
    
  }
  
  for(auto line : screen){
    for(auto pixel : line){
      cout << (pixel ? "#" : ".");
    }
    cout << endl;
  }

  return 1;
}
