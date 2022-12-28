#include<iostream>
#include<fstream>
#include <utility>
#include "json.hpp"
#include "priorityqueue.h"

using namespace std;
using json = nlohmann::json;

int main(int argc, char** argv) {
  string name = argv[1];
  ifstream file;
  file.open(name);
  json json_Obj;
  pair<int, int> val(0, 0);
  
  if(file.is_open()) {
    file >> json_Obj;
  }

  size_t maxSize = json_Obj["metadata"]["maxHeapSize"];
  size_t numOpe = json_Obj["metadata"]["numOperations"];

  PriorityQueue PQ(maxSize);
  PQ.init();

  for(size_t i = 1; i <= numOpe; i++) {
    if(numOpe >= 100) {
      if(i < 10) {
        string nm = "";
        nm = "Op00" + to_string(i);
        if(json_Obj[nm]["operation"] == "insert"){
          Key k = json_Obj[nm]["key"];
          int a = 0, b =0; 
          PQ.insert(k, a, b);
        }
        else if(json_Obj[nm]["operation"] == "removeMin") {
          PQ.removeMin();
        }
      }
        else if(i<100){
          string nm = "";
          nm = "Op0" + to_string(i);
          if(json_Obj[nm]["operation"] == "insert"){
            Key k = json_Obj[nm]["key"];
            int a = 0, b =0;
            PQ.insert(k, a, b);
          }
        else if(json_Obj[nm]["operation"] == "removeMin") {
          PQ.removeMin();
          }
        }
        else {
          string nm = "";
          nm = "Op" + to_string(i);
          if(json_Obj[nm]["operation"] == "insert"){
            Key k = json_Obj[nm]["key"];
            int a = 0, b =0;
            PQ.insert(k, a, b);
          }
        else if(json_Obj[nm]["operation"] == "removeMin") {
          PQ.removeMin();
          }
        }
    }
    else {
      if(i < 10) {
        string nm = "";
        nm = "Op0" + to_string(i);
        if(json_Obj[nm]["operation"] == "insert"){
          Key k = json_Obj[nm]["key"];
          int a = 0, b =0; 
          PQ.insert(k, a, b);
        }
        else if(json_Obj[nm]["operation"] == "removeMin") {
          PQ.removeMin();
        }
      }
      else {
        string nm = "";
        nm = "Op" + to_string(i);
        if(json_Obj[nm]["operation"] == "insert"){
          Key k = json_Obj[nm]["key"];
          int a = 0, b =0; 
          PQ.insert(k, a, b);
        }
        else if(json_Obj[nm]["operation"] == "removeMin") {
          PQ.removeMin();
        }
      }
    }
  }

  cout << PQ.JSON(numOpe).dump(2) << "\n";
}
