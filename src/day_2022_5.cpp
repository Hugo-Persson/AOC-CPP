#include <array>
#include <fstream>
#include <iostream>
#include <map>
#include <set>
#include <stack>
#include <string>
#include <vector>
#include <unordered_map>
#include <sstream>
#include <regex>

using namespace std;

// 1, 5, 9

inline std::vector<std::string> split(const std::string& s, char delimiter) {
  std::vector<std::string> tokens;
  std::string              token;
  std::istringstream       tokenStream(s);
  
  while (std::getline(tokenStream, token, delimiter)) {
    tokens.push_back(token);
  }
  return tokens;
}


int main() {
  ifstream in("day_2022_5");

  int lines = 8;
  int piles = 9;
  // int lines = 3;
  // int piles = 3;
  
  vector<stack<char> >  crates(piles);
  string line;
  
  
  vector<string> readLines;
  for(int n = 0; n < lines; n++){
    getline(in, line);
    readLines.push_back(line);
  }
  
  while(lines--){
    line = readLines[lines];
    for(int i = 0; i< piles; i++){
     int charToGet = 1 + i*4; 
      
      if(line[charToGet] == ' ') continue;
      
      crates[i].push(line[charToGet]);
    }
  }
  getline(in, line);
  getline(in, line);
  // Read the first part, here comes second
  while(getline(in, line)){
    auto chunks = split(line, ' ');
    int count = stoi(chunks[1]);
    int from = stoi(chunks[3]) - 1;    
    int to = stoi(chunks[5]) - 1 ;
    stack<char> temp;
    for(int i = 0; i<count; i++){
      
      temp.push(crates[from].top());
      crates[from].pop();
    }
    for(int i = 0; i < count; i++){
      crates[to].push(temp.top());
      temp.pop();
    }
  }
  string output = "";
  for(auto s : crates){
    output += s.top();
  }  
  cout << output << endl;

  return 1;
}
