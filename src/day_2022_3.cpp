#include <array>
#include <fstream>
#include <iostream>
#include <map>
#include <set>
#include <unordered_set>
#include <string>
#include <vector>

using namespace std;

int charToValue(char c){
  int dec = (int)c;
  if(dec >97){
    return dec - 96;
  }
  else{
    return dec - 38;
  }
}
bool itemsExistInString(char item, string line){
  for(char c: line){
    if(c == item) return true;
  }
}


int main() {
  ifstream in("day_2022_3");
  int sum = 0;

  string line;
  vector<string> lines;
  while(getline(in, line)){
    lines.push_back(line);
  }
  
  
  for(int i = 0; i<lines.size(); i+=3){
    for(int n = 0; n<lines[i].length(); ++n){
      if(itemsExistInString(lines[i][n], lines[i+1]) && itemsExistInString(lines[i][n], lines[i+2])){
        // Found item in all
        sum += charToValue(lines[i][n]);

        break;
      }
    }
  }
  cout << sum << endl;

  return 1;
}
