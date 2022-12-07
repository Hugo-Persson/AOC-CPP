#include <array>
#include <fstream>
#include <functional>
#include <iostream>
#include <map>
#include <set>
#include <string>
#include <vector>

using namespace std;

int main() {
  ifstream in("day_2022_1");
  
  vector<int> cals;
  string line;
  int currElf = 0;
  while(getline(in, line)){
    if(line == ""){
      cals.push_back(currElf);
      currElf = 0;
      continue;
    }
    currElf += stoi(line);
    
  }
  sort(cals.begin(), cals.end(), greater<int>());
  cout << cals[0] + cals[1] + cals[2] << endl;

  return 1;
}
