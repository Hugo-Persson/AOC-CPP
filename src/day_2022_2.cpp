#include <array>
#include <fstream>
#include <iostream>
#include <map>
#include <set>
#include <string>
#include <vector>

using namespace std;

int calcScore(string opp, string outcome){
  int res = 0;
  if(outcome == "Y"){
    // Draw
    res += 3;
    if(opp == "A") res+=1;
    else if(opp == "B") res+=2;
    else if(opp == "C") res+=3;
  
  } 
  else if(outcome == "Z") {
    // WIN
    res += 6;    
    if(opp == "A") res+=2;
    else if(opp == "B") res+=3;
    else if(opp == "C") res+=1;
  }
  else if(outcome == "X"){
    // LOSS
    if(opp == "A") res+= 3;
    if(opp == "B") res += 1;
    if(opp == "C") res += 2;
  }
  return res;
}

int main() {
  ifstream in("day_2022_2");

  int score = 0;
  string A;
  string B;
  string token;
  int i = 0;
  while(in >> token){
    if(i%2 == 0){
      A = token;
    }
    else{
      B = token;

      score += calcScore(A, B);
  } 
    i++;
  }
  cout << score << endl;

  return 1;
}

