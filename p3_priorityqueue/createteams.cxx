#include"teamdata.h" 
#include<iostream>
#include<fstream>
#include <utility>
#include "json.hpp"
#include "priorityqueue.h"
#include <cmath>
using namespace std;
using json = nlohmann::json;

int main(int argc, char** argv) {
  string fn = argv[1];
  ifstream file; 
  file.open(fn);
  json json_obj;
  json ouput;
  
  if(file.is_open()) {
    file >> json_obj;
  }
  int numPlayers = json_obj["metadata"]["numPlayers"];
  int max_size = json_obj["teamStats"].size();
  // cout<<"max_size :" << max_size << endl;
  // cout<< "num of players: "<<numPlayers <<endl;

  PriorityQueue PQ(max_size);
  PQ.init();
  
  for (int i = 0; i < max_size; i++) {
    int p1 = json_obj["teamStats"][i]["playerOne"];
    int p2 = json_obj["teamStats"][i]["playerTwo"];
    Key percentage = json_obj["teamStats"][i]["winPercentage"];
    Key abs_50 = abs(percentage - 50);
    KeyValuePair pair = make_pair(abs_50,make_pair(p1, p2));
    PQ.insert(pair);
  }
  
  // cout<< "Here is the original player json file: " <<endl;
  // cout << PQ.JSON(0).dump(2) << "\n";
  
  /*
   KeyValuePair pair = PQ.min();
    Value inside_pair = pair.second;
    int choose1 = inside_pair.first;
    int choose2 = inside_pair.second;
    ouput["teams"][j][0] = choose1;
    ouput["teams"][j][1] = choose2;
*/
  for (int j = 0; j < 20; j++) {
    KeyValuePair pair = PQ.min();
    Value inside_pair = pair.second;
    int choose1 = inside_pair.first;
    int choose2 = inside_pair.second;
    ouput["teams"][j][0] = choose1;
    ouput["teams"][j][1] = choose2;
    
    
    for (int i = 1; i <= int(PQ.size()); i++) { 
      // cout<< "choose1: " << choose1 << "  choose2: " <<choose2 << endl;
      // cout<< "max_size: "<< int(PQ.size()) <<endl;
      // cout<< "i: "<<i <<endl;
      KeyValuePair temp = PQ.getNode(i);
      Value temp_inside = temp.second;
      int p1 = temp_inside.first;
      int p2 = temp_inside.second;
      // cout<< "p1: "<<p1 <<endl;
      // cout<< "p2: "<<p2 <<endl;
      
      if((p1 == choose1) || (p2 == choose1) || (p1 == choose2) || (p2 == choose2)) {
        // cout<< "in the if with p1 and p2 as: " <<  p1 << p2 << endl;
        PQ.removeNode(i);
         --i;
        // cout<< "--i: " << i << endl;  
    }
   // cout << PQ.JSON(0).dump(2) << "\n";
   }
  }
  
  // cout<< "Here is the final player json file: " <<endl;
  // cout << PQ.JSON(0).dump(2) << "\n";
  // cout<< "Here is the output json file: " <<endl;
  cout << ouput.dump(2) <<"\n";
  
}
