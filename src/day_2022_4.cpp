#include <array>
#include <cstdint>
#include <fstream>
#include <iostream>
#include <map>
#include <set>
#include <string>
#include <vector>
#include <sstream>
#include <cmath>

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
  ifstream in("day_2022_4");

  // Handle each pair assignment as bits
  // Do bit & with both of the pairs. If either pair equals that we have overlap
  // For example, 
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

    int first = 0;
    for(int i = firstStart; i<=firstEnd; ++i){
      int curr = (int) pow(2,i);
      first = first | curr;
    }
    

    int second= 0;
    for(int i = secondStart; i<=secondEnd; ++i){
      second = second | (int)pow(2, i);
    }
  
    int t = first & second;
    if(t == first || t == second) answer++;
    
  }
  
  cout << answer << endl;

  return 1;
}
