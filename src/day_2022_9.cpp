#include <array>
#include <fstream>
#include <iostream>
#include <map>
#include <set>
#include <string>
#include <vector>
#include <unordered_map>

using namespace std;

unordered_map<string, bool> visisted;
vector<pair<int, int> > body(10, make_pair(0,0));

int tailMoves = 1;

bool isConnected(pair<int, int> p1, pair<int, int> p2){
 
  const auto [h1, h2] = p2; 
 
  return 
    p1 == make_pair(h1-1, h2) ||
    p1 == make_pair(h1 +1, h2) ||
    p1 == make_pair(h1-1, h2 -1) ||
    p1 == make_pair(h1-1, h2+1) ||
    p1 == make_pair(h1+1, h2-1) ||
    p1== make_pair(h1+1, h2+1) ||
    p1 == make_pair(h1, h2+1) ||
    p1 == make_pair(h1, h2-1) ||
    p1== p2;
  
}

int transformCompare(int comp){
  if(comp == 0) return 0;
  if(comp < 0) return -1;
  if(comp > 0) return 1;
  return 0;
}
string tailToString(pair<int, int> p){
  return to_string(p.first) + "," + to_string(p.second);
}

void markTail(pair<int, int> p){
  visisted[tailToString(p)] = true;
}
bool tailBeenHere(pair<int, int> p){
  return visisted[tailToString(p)];
}

void countUpPair(pair<int,int> p){
  if(!tailBeenHere(p)){
    tailMoves +=1;
    markTail(p);
  }
}
void moveBody(){
  for(int i = 1; i<body.size(); i++){
    if(!isConnected(body[i], body[i-1])) {
      body[i].first += transformCompare(body[i - 1].first - body[i].first);
      body[i].second += transformCompare(body[i-1].second - body[i].second);
      if(i == body.size()-1){
        cout << "Counting up " << endl;        
       countUpPair(body[i]);
      }
    }
  }
}




// First is y 
// second x

int main() {
  ifstream in("day_2022_9");
  char dir;
  int steps;
  while(in >> dir >> steps){
    while(steps--){
      if(dir == 'R'){
        body[0].second++;
      }
      else if(dir == 'U'){
        body[0].first--;
      }
      else if(dir == 'D'){
        body[0].first++;
      }
      else if(dir == 'L'){
        body[0].second--;
    
      }
      moveBody();
      int i = 0;
      /*for(auto b : body){
        cout << i << ":" "(" << b.first << "," << b.second << ")" << endl;
        i++;
      }*/
    }
  }
  
  
  
  cout << tailMoves << endl;

  return 1;
}
