#include <array>
#include <fstream>
#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <string>
#include <vector>
#include <stack>


using namespace std;

struct Monkey{
  queue<int> items;
  
  
  char opp;
  int supplier;
  
  int testBy;
  int holdCount = 0;
  int trueJump;
  int falseJump;
  int name;
  
  int simulate_focus(vector<Monkey> &monkeys){
    while (!items.empty()) {
      holdCount++;
      // Pop an item off of the stack
      int item = items.front();
      items.pop();

      // cout << "Monkey " << name << " inspecting " << item << endl;
      // Apply the monkey's operation to the item
      if(opp == '*'){
        item *= supplier;
      }
      if(opp == '+'){
        item+= supplier;
      }
      else if(opp == '^'){
        item *= item;
      }

      // Divide the item's value by 3 and round down
      item /= 3;

      int throwTo;
      // Test the item's value
      if (item % testBy == 0) {
        // If the test is true, throw the item to the trueJump monkey
        throwTo = trueJump;
      }
      else{
        // Throw to falseJump monkey
        throwTo = falseJump;
      }
      // cout << "Throwing " << item << " To monkey " << throwTo << endl;
      monkeys[throwTo].items.push(item);
    }
  }
  
    // Constructor for the Monkey class
  Monkey(int testBy, int trueJump, int falseJump, queue<int> items, char opp, int supplier)
  : testBy(testBy), trueJump(trueJump), falseJump(falseJump), items(items), opp(opp), supplier(supplier) {}
};

int main() {
  ifstream in("day_2022_11");

  vector<Monkey> monkeys;

  queue<int> startingItems0;
  startingItems0.push(66);
  startingItems0.push(71);
  startingItems0.push(94);

  queue<int> startingItems1;
  startingItems1.push(70);

  queue<int> startingItems2;
  startingItems2.push(62);
  startingItems2.push(68);
  startingItems2.push(56);
  startingItems2.push(65);
  startingItems2.push(94);
  startingItems2.push(78);

  queue<int> startingItems3;
  startingItems3.push(89);
  startingItems3.push(94);
  startingItems3.push(94);
  startingItems3.push(67);

  queue<int> startingItems4;
  startingItems4.push(71);
  startingItems4.push(61);
  startingItems4.push(73);
  startingItems4.push(65);
  startingItems4.push(98);
  startingItems4.push(98);
  startingItems4.push(63);

  queue<int> startingItems5;
  startingItems5.push(55);
  startingItems5.push(62);
  startingItems5.push(68);
  startingItems5.push(61);
  startingItems5.push(60);

  queue<int> startingItems6;
  startingItems6.push(93);
  startingItems6.push(91);
  startingItems6.push(69);
  startingItems6.push(64);
  startingItems6.push(72);
  startingItems6.push(89);
  startingItems6.push(50);
  startingItems6.push(71);

  queue<int> startingItems7;
  startingItems7.push(76);
  startingItems7.push(50);

  Monkey monkey0(3, 7, 4, startingItems0, '*', 5);
  Monkey monkey1(17, 3, 0, startingItems1, '+', 6);
  Monkey monkey2(2, 3, 1, startingItems2, '+', 5);
  Monkey monkey3(19, 7, 0, startingItems3, '+', 2);
  Monkey monkey4(11, 5, 6, startingItems4, '*', 7);
  Monkey monkey5(5, 2, 1, startingItems5, '+', 7);
  Monkey monkey6(13, 5, 2, startingItems6, '+', 1);
  Monkey monkey7(7, 4, 6, startingItems7, '^', 1);
  
  monkeys.push_back(monkey0);
  monkeys.push_back(monkey1);
  monkeys.push_back(monkey2);
  monkeys.push_back(monkey3);
  monkeys.push_back(monkey4);
  monkeys.push_back(monkey5);
  monkeys.push_back(monkey6);
  monkeys.push_back(monkey7);

  
  for(int i = 0; i<20; i++){
    for(int n = 0; n<monkeys.size(); n++){
      Monkey& monkey = monkeys[n];
      monkey.simulate_focus(monkeys);
    }
  }

  for(auto m : monkeys){
    cout << "Monkey " << m.name << endl;
    cout << "Items: ";
    while(!m.items.empty()){
      cout << m.items.front() << " "; m.items.pop();
    }
    cout << endl;
    cout << m.holdCount << endl;
  }  

  return 1;
}
