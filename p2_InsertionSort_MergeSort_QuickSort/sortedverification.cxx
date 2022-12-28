#include <fstream>
#include <iostream>
#include "json.hpp"
using json = nlohmann::json;
using namespace std;

int main(int argc, char** argv)
{
  string fn1 = argv[1]; //save the file name into fn1
  ifstream file;
  file.open(fn1);      //open the file
  json jsonObject;    //create a json object to store the info from input file 
  json jsonResult;   // create a json object to store the result
  if (file.is_open()) { //load all the info from input file to jsonobject    
    file >> jsonObject; //loading... 
    }
   int length = jsonObject["metadata"]["arraySize"];   //the length of the array
  int sample = jsonObject["metadata"]["numSamples"];  //the how many sample are in the input file
  int num_of_invers = 0;  //count how many sample has invers
  bool has_no_invers= false;  //if it has no invers, then it will be true 
  int arr[length];   //initial an array 
  

  for (int i = 1; i <=sample; i++){  //go through all the samples
    string sample_name ="";    
    if (i<10) {                        //create the name for the key for each array 0-9
      string num = to_string(i);
      sample_name = "Sample0" +num;    
    }
    else{                              //create the name for the key for each array 10+
      string num = to_string(i);  
      sample_name = "Sample" +num;     
    }
    
    for (int j = 0; j<length; j++){ 
      arr[j] = jsonObject[sample_name][j];  //store all the value into arr. 
    }

    int smaller = 0;                  //if any is not in order 
    for(int j = 0; j<length-1; j++){ //go through the whole array except last element 
      if(arr[j] > arr[j+1]) { //compare the front one to the one after it
        string index = to_string(j); // make the key in json file 
        int arrtemp[] = {arr[j], arr[j+1]}; //compare 
        //cout<< arrtemp[0] << " | " <<arrtemp[1] << endl; //test 
        
        for(int a = 0; a < 2; a++) {  //add consecutiveInversions section in the result.json
          jsonResult[sample_name]["ConsecutiveInversions"][index][a] = arrtemp[a]; 
        }
        smaller++; 
      }
    }

    if(smaller!= 0) { //if there are numbers in wrong order, then num_of_invers +1 
      num_of_invers+=1;
    for (int i = 0; i < length; i++) {    //i is the 0 - array length-1, go through the array
      jsonResult[sample_name]["sample"][i] = arr[i]; //writing the sample in the json file
      }
    }
    // nlohmann::jsonResult sample = jsonObject[sample_name];
    
  }
  
  // string num_invers = to_string(num_of_invers);
  //../Examples/Example1.json
  string path = "../Examples/" + fn1; //create the string that store the path of the file that pass in.
  jsonResult["metadata"]["arraySize"] = length;//add arraysize in json file
  jsonResult["metadata"]["numSamples"] = sample;//add numsample in json file
  jsonResult["metadata"]["samplesWithInversions"] = num_of_invers; // add the number with inversions in the json file
  jsonResult["metadata"]["file"] = path;//add the passed in file's file. 
    cout << jsonResult.dump(2) << "\n"; //print out the json file. 
}