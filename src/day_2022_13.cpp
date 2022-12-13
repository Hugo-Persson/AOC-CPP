#include <algorithm>
#include <array>
#include <fstream>
#include <iostream>
#include <map>
#include <set>
#include <stack>
#include <string>
#include <vector>

using namespace std;


int ctoi(char c){
  return c - 48;
}

struct Element{
  bool isVector = false;
  vector<Element*> elements;
  int value = 0;
  
  Element* wrapInVector(){
    Element* newElement = new Element{true, {}, 0};
    newElement->elements.push_back(this);
    return newElement;  
  }
};

Element* getNumberElementFromChunk(string chunk){
  int num = stoi(chunk);
  chunk = "";
  Element* n = new Element{false, {}, num};
  return n;
}

Element* parseLine(string line){
  Element* outerElement = new Element{true, {}, 0};
  stack<Element*> elements;
  elements.push(outerElement);
  string chunk = "";

  for(int i = 1; i < line.length(); ++i){
    Element* curr = elements.top();
    char c = line[i];
    if(c == ',') {
      if(chunk.length()){
        curr->elements.push_back(getNumberElementFromChunk(chunk));

      }
      chunk = "";
      continue;
    }
    else if(c == '['){
      // Nest
      Element* newEl = new Element{true, {}, 0};
      curr->elements.push_back(newEl);
      elements.push(newEl);
    }
    else if(c == ']'){
      
      if(chunk.length()){
        curr->elements.push_back(getNumberElementFromChunk(chunk));

      }
      chunk = "";

      // Pop
      elements.pop();
    }
    else {
      // Number

      chunk += c;
      
    }
  }
  
  return outerElement;
}


void printElement(Element* e){
  if(e->isVector){
    cout << "Going deeper " << endl;
    for(auto d : e->elements){
      printElement(d);
    }
  }
  else{
    cout << e->value << endl;
  }
}

// Negative if right is bigger - we want this
// 0 if equal
// positive if left i bigger 
int compareElement(Element* first, Element* second){
  if(!first->isVector && !second->isVector) {
    //cout << "Comparing " << first->value << " and  " << second->value << endl;
    return first->value - second->value;

  }
  else if(first->isVector && !second->isVector){
    //cout << "Wrapping second " << endl;
    return compareElement(first, second->wrapInVector());  
  }
  else if(!first->isVector && second->isVector) {
    // cout << "Wrapping first " << endl;
    return compareElement(first->wrapInVector(), second);
  }

  else if(first->isVector && second->isVector){
    // Compare all the elements
    int lastCompare = 0;
    //cout << "Size " << first->elements.size() << endl;
    /* if(first->elements.size() == 1){
      cout << "Printing first "<< endl;
      printElement(first);
    } */
    // cout << "second size " << second->elements.size() << endl;
    //if(first->elements.size() == 0 && second->elements.size() == 0) return 0;
    for(int i = 0; i<first->elements.size(); ++i){
      //cout << "Start loop " << endl;
      if(i >= second->elements.size()){
        
        return 1; // The only way to reach this point is if left has been less or equal this far because otherwise we would have returned
      } 
      lastCompare = compareElement(first->elements[i], second->elements[i]);
      // cout << "Here   " << lastCompare << endl;
      if(lastCompare != 0){
        /* cout << "Ending here " << lastCompare << endl; 
        cout << first->elements[i]->value << endl;
        cout << second->elements[i]->value << endl; */
         return lastCompare; 
      }
      //cout << "Also here   " << i << endl;
    }
    // cout << "returning " << endl
    return first->elements.size() - second->elements.size();
  }
}



int main() {
  ifstream in("day_2022_13");

  string first;
  string second;
  int index = 1;
  int indicesInOrder = 0;
  while(in >> first >> second){
    //cout << "Starting loop " << endl;
    auto f = parseLine(first);
    auto s = parseLine(second);
    
    /* cout << "Printing first " <<endl;
    printElement(f);

    cout << "Printing second " << endl;
    printElement(s); */
    int compared = compareElement(f,s);
    //printElement(f);
    //cout << "Result for " << index << " is " << compared << endl; 
    if(compared < 0) {
      cout << "True for    " << index << endl;
      indicesInOrder+=index;
    }
    index++;
  }
  cout << "Result " << indicesInOrder << endl;
  return 1;
}
