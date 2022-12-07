#include <algorithm>
#include <array>
#include <fstream>
#include <iostream>
#include <map>
#include <set>
#include <unordered_set>
#include <string>
#include <vector>
#include <cmath>
#include <sstream>

using namespace std;

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
  ifstream in("day_2022_4_2");

  string line;
  int answer = 0;
  while(getline(in, line)){
    auto chunk1 = split(line, ',');
    auto chunk2 = split(chunk1[0], '-');
    auto chunk3 = split(chunk1[1], '-');
    int firstStart = stoi(chunk2[0]);
    int firstEnd = stoi(chunk2[1]);
    int secondStart = stoi(chunk3[0]);
    int secondEnd = stoi(chunk3[1]);
    set<int> first;
    for(int i = firstStart; i<=firstEnd; ++i){
      first.insert(i);
    }
    

    set<int> second;
    for(int i = secondStart; i<=secondEnd; ++i){
      if(first.count(i)){
        answer++;
        break;
      }
    }
  
    //if(includes(first.begin(), first.end(), second.begin(), second.end()) ||
    //includes(second.begin(), second.end(), first.begin(), first.end())) answer++; // Check if either is subset of the other
    
  }
  
  cout << answer << endl;

  return 1;
}
