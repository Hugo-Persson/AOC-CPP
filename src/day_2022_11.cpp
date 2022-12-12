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



int commonDivider = 9699690;
struct Monkey{
  vector<__uint128_t> items;
  
  
  char opp;
  int supplier;
  
  int testBy;
  long long holdCount = 0;
  int trueJump;
  int falseJump;
  int name;
  
  int simulate_focus(vector<Monkey> &monkeys){
    while (!items.empty()) {
      holdCount++;
      // Pop an item off of the stack
      __uint128_t item = items.back();
      // Remove last item from items
      items.pop_back();

      // cout << "Monkey " << name << " inspecting " << item << endl;
      // Apply the monkey's operation to the item
      if(opp == '*'){
        item = (item * supplier);
      }
      if(opp == '+'){
        item = (item + supplier);
      }
      else if(opp == '^'){
        item = (item * item);
      }

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
      monkeys[throwTo].items.push_back(item);
    }
  }
  
    // Constructor for the Monkey class
  Monkey(int testBy, int trueJump, int falseJump, vector<__uint128_t > items, char opp, int supplier)
  : testBy(testBy), trueJump(trueJump), falseJump(falseJump), items(items), opp(opp), supplier(supplier) {}
};

int main() {
  ifstream in("day_2022_11");

  vector<Monkey> monkeys;

  Monkey monkey0(3, 7, 4, {66, 71, 94}, '*', 5);
  monkey0.name = 0;
  Monkey monkey1(17, 3, 0, {70}, '+', 6);
  monkey1.name = 1;
  Monkey monkey2(2, 3, 1, {62,68,56,65,94,78}, '+', 5);
  monkey2.name = 2;

  Monkey monkey3(19, 7, 0, {89,94,94,67}, '+', 2);
  monkey3.name = 3;

  Monkey monkey4(11, 5, 6, {71,61,73,65,98,98,63}, '*', 7);
  monkey4.name = 4;

  Monkey monkey5(5, 2, 1, {55,62,68,61,60}, '+', 7);
  monkey5.name = 5;

  Monkey monkey6(13, 5, 2, {93,91,69,64,72,89,50,71}, '+', 1);
  monkey6.name = 6;

  Monkey monkey7(7, 4, 6, {76,50}, '^', 1);
  monkey7.name = 7;
  
  monkeys.push_back(monkey0);
  monkeys.push_back(monkey1);
  monkeys.push_back(monkey2);
  monkeys.push_back(monkey3);
  monkeys.push_back(monkey4);
  monkeys.push_back(monkey5);
  monkeys.push_back(monkey6);
  monkeys.push_back(monkey7);

  
  for(int i = 0; i<10000; i++){
    for(int n = 0; n<monkeys.size(); n++){
      Monkey& monkey = monkeys[n];
      monkey.simulate_focus(monkeys);
    }
  }

  vector<long long> holdCount;
  for(auto m : monkeys){
    cout << "Monkey " << m.name << endl;
    cout << "Items: ";
    cout << endl;
    cout << m.holdCount << endl;
    holdCount.push_back(m.holdCount);
  }  
  sort(holdCount.begin(), holdCount.end());
  cout << (holdCount[6] * holdCount[7]);

  return 1;
}
