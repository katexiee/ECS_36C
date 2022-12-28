#include <fstream>
#include <iostream>
#include "json.hpp"
using json = nlohmann::json;
using namespace std;

int main(int argc, char** argv)
{
  string fn1 = argv[1]; //save the first file into fn1
  string fn2 = argv[2]; //save the sec file into fn2
  ifstream file1;
  ifstream file2;
  file1.open(fn1);      //open file1
  file2.open(fn2);      //open file2
  json jsonObject1;    //create a json object to store the info from input file 
  json jsonObject2;    //create a json object to store the info from input file 
  json jsonResult;   // create a json object to store the result
  int arraySize = 0;  //store the size of array
  int numSamples = 0; //store the num of samples

  
  if(file1.is_open()){
    file1>>jsonObject1; //load all the info from input file1 to jsonobject1    
  }
  if(file2.is_open()) {
    file2>>jsonObject2;//load all the info from input file2 to jsonobject2    
  }

  arraySize = jsonObject1["metadata"]["arraySize"];
  numSamples = jsonObject1["metadata"]["numSamples"];

  int arr1[arraySize];
  int arr2[arraySize];
  int num_of_conflict = 0;
  
  for (int i =1; i <= numSamples; i++) {
    string sample_name ="";    
    bool is_conflict = false;
    if (i<10) {                        //create the name for the key for each array 0-9
      string num = to_string(i);
      sample_name = "Sample0" +num;    
    }
    else{                              //create the name for the key for each array 10+
      string num = to_string(i);  
      sample_name = "Sample" +num;     
    }
    string path1 = fn1;
    string path2 = fn2;
    

    for(int j = 0; j < arraySize; j++) {  
      arr1[j] = jsonObject1[sample_name][j];
    }
    for(int j = 0; j < arraySize; j++) {
      arr2[j] = jsonObject2[sample_name][j];
    }
    for(int a = 0; a < arraySize; a++) {
      jsonResult[sample_name][path1][a]= arr1[a];
      jsonResult[sample_name][path2][a]= arr2[a];
    }
    
    for (int j = 0; j < arraySize; j++) {
      if(arr1[j] != arr2[j]) {
        is_conflict = true; 
        string index = to_string(j);
        jsonResult[sample_name]["Mismatches"][index][0] = arr1[j];
        jsonResult[sample_name]["Mismatches"][index][1] = arr2[j];
      }
    }

    if(is_conflict)
      num_of_conflict++;
  }

  jsonResult["metadata"]["File1"]= jsonObject1["metadata"]; 
  jsonResult["metadata"]["File1"]["name"]= fn1; 
  jsonResult["metadata"]["File2"]= jsonObject2["metadata"]; 
  jsonResult["metadata"]["File2"]["name"]= fn2; 
  jsonResult["metadata"]["samplesWithConflictingResults"] = num_of_conflict;
  
  
  cout << jsonResult.dump(2) <<"\n";
  file1.close();
  file2.close();
}