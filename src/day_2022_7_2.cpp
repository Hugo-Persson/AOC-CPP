#include <array>
#include <fstream>
#include <iostream>
#include <map>
#include <set>
#include <string>
#include <vector>
#include <unordered_map>
#include <experimental/filesystem>
#include <stack>
using namespace std;

struct Dir{
  vector<Dir*> subDir;
  long long fileSize;
  Dir* parent;
  string name;
  
  long long size(){
    int sum = 0;
    for(auto d: subDir){
      sum+= d->size();
    }
    sum+=fileSize;
    return sum;
  }
};

Dir* bestDeletion;
void checkDir(Dir* dir, long long neededSpace){
  
  long long currentSize = dir->size();
  if(currentSize >= neededSpace && currentSize < bestDeletion->size()){
   cout << dir->name << endl; 
   bestDeletion = dir;
  }  
  for(auto d :  dir->subDir){
    checkDir(d, neededSpace);
  }
}

int main() {
  ifstream in("day_2022_7_2");

  
  
  long long totalSize = 0;
  
  Dir* root = new Dir();
  Dir* currentDir = root;
  string token;
  while(in >> token){
    if(token == "$"){
       // Command
      in >> token;
      if(token == "cd"){
        string name; 
        in >> name;
        if(name == ".."){
          currentDir = currentDir->parent;
        }
        else{
          bool hasCurrent = false;
          for(auto subD : currentDir->subDir){
            if(subD->name == name){
              hasCurrent = true;
              currentDir = subD;
              break;
            }
          }
          if(hasCurrent) continue;
          Dir* newDir = new Dir();
          newDir->name = name;
          currentDir->subDir.push_back(newDir);
          newDir->parent = currentDir;
          currentDir = newDir;
        }
      }
    }
    else{
      if(token != "dir"){
        long long s = stoll(token);
        totalSize += s;
        currentDir->fileSize += s;
      }
      in >> token; // Waste
    }
  }
  bestDeletion = root;
  long long freeSpace = 70000000 - root->size();
  
  long long needed = 30000000 - freeSpace;
  cout << needed << endl;
  checkDir(root, needed);
  
  cout << bestDeletion->size();

  return 1;
}
