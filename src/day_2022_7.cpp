#include <array>
#include <fstream>
#include <iostream>
#include <map>
#include <set>
#include <string>
#include <vector>
#include <unordered_map>
#include <optional>

using namespace std;

struct Entity{
  
  string name = "";
  
  virtual int size() = 0;
  
};

struct Dir : Entity{
  vector<Entity*> members;
  
  Dir* parent; 
  int size(){
    int sum = 0;
    for(auto e: members){
      sum += e->size();
    }  
    return sum;
  }
};
struct File : Entity{
  int _size;
  
  int size(){
    return _size;
  }
  
  
};

int main() {
  ifstream in("day_2022_7");

  string token;

  Dir root;

  root.name = "/"; 
  Dir* currentDir = &root;
  while(in >> token){

    cout << "Current dir " << currentDir->name << endl;
    cout << "Current token " + token << endl;
    if(token == "$"){
     in >> token; // waste
      if(token == "cd"){
        string name;
        in >> name;
        cout << "Cd in to " + name << endl;
        if(name == ".."){
          cout << "Goint to " << currentDir->parent->name << endl;
          currentDir = currentDir->parent;
        }
        else{
          cout << "Parrent name " << currentDir->name << endl;
          Dir newDir; // TODO: Check if dir exists
          string newDirName = currentDir->name + name;

          cout << "New dir name: " << newDirName << endl;
          cout << "Parrent name " << currentDir->name << endl;
          newDir.name = newDirName;
          newDir.parent = currentDir;
          currentDir->members.push_back(&newDir);
          currentDir = &newDir;
        }
      }
       
    }
    else{
      // Result
      if(token == "dir"){
        in >> token; // waste
      }
      else{
        // File
        string name;
        in >> name;
        
        
        File f;
        f.name = currentDir->name + name;
        f._size = stoi(token);
        currentDir->members.push_back(&f);
      }
    }
  }
  
  cout << root.members.size() << endl;

  return 1;
}
