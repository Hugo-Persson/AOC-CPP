#include <array>
#include <fstream>
#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <string>
#include <vector>

using namespace std;

struct Node{
    int value;
  Node* next = nullptr;
  Node* prev = nullptr;
};
Node* first = nullptr;
Node* last = nullptr;
Node* zero = nullptr;
queue<Node*> todo;

int main() {
  ifstream in("day_2022_20");

  string line;
  cin >> line;
  first = new Node{stoi(line)};
  last = first;
  todo.push(first);
  if(first->value == 0) zero = first;
  while(cin >> line){
    auto n = new Node{stoi(line), nullptr, last};
    last->next = n;
    last = n;
    todo.push(n);
    if(n->value == 0) zero = n;
  }

  while(!todo.empty()){
    auto e = todo.front(); todo.pop();
    auto move = e->value;
    auto newPrev = e;
    for(int i = 0; i<move; ++i){
      newPrev = e->next;
    }
    e->next->prev = e->prev;
    e->next = newPrev->next;
    e->prev = newPrev;
    newPrev->next = e;
  }

  int answer = 0;
  Node* curr = zero;
  for(int i = 1; i<=3000; ++i){
    curr = curr->next;

    if(i == 1000 || i == 2000 || i == 3000) answer+=curr->value;
  }
  
  cout << answer << endl;

  return 1;
}
