#include <typeinfo>
#include <fstream>
#include <vector>
#include <iostream>
#include "json.hpp"
#include <ctime>
#include "insertionsort.h"
#include "mergesort.h"
#include "quicksort.h"
using json = nlohmann::json;
using namespace std;

int main(int argc, char** argv)
{
  vector<string> samplename; //create a vector to store sample name
  vector<double> instime; // create a vector to store insertsort runtime
  vector<double> mertime; // create a vector to store mergesort runtime
  vector<double> quitime;// create a vector to store quicksort runtime
  vector<int> inscomp; // create a vector to store insertsort comparison
  vector<int>mercomp;// create a vector to store mergesort comparison
  vector<int>quicomp;// create a vector to store quicksort comparison
  vector<int>insmem; // create a vector to store insertsort memery
  vector<int>mermem;// create a vector to store mergesort memery
  vector<int>quimem;// create a vector to store quicksort memery
  string fn1 = argv[1]; //save the first file into fn1
  ifstream file; //input file object 
  cout << "Sample,InsertionSortTime,InsertionSortCompares,InsertionSortMemaccess,MergeSortTime,MergeSortCompares,MergeSortMemaccess,QuickSortTime,QuickSortCompares,QuickSortMemaccess\n"; //print out the first line of csv file 
  file.open(fn1); //open the file 
  json jsonObject; // create a json object 
  
  if(file.is_open()) { 
    file >> jsonObject; //input file 
  }
  else {
    cout<< "Unable to Access"; //incase can't open file
  }
  int length = jsonObject["metadata"]["arraySize"]; //store length 
  int sample = jsonObject["metadata"]["numSamples"]; // store num of sample 
  int cnt = 0;  //number of cnt 
 
  for(int i = 1; i <= sample; i++) { //go through all the samples 
    int inscnt = 0; //insert sort comparison count 
    int mercnt = 0; // merge sort comparison count 
    int quicnt = 0;//quick sort comparison count 
    int insm = 0;//insert sort memory count 
    int merm = 0;//merge sort memory count 
    int quim = 0;//quick sort memory count 
    string samname = ""; //store name of sample 
    vector<int> arr; // = new vector<int>;
    if(i < 10) {                        // this if statement to create sample name 
      string num = to_string(i); 
      samname = "Sample0" + num;
      samplename.push_back(samname);
    }
    else{                      //if it's more than 10 
      string num = to_string(i);
      samname = "Sample" + num;
      samplename.push_back(samname);
    }

    for(int j = 0; j < length; j++) {  // go through the array 
      int num = jsonObject[samname][j]; // store the array 
      arr.push_back(num);  //store to vector 
    } 
    vector<int> arr1 = arr;  //create 3 array for three sorting alg 
    vector<int> arr2 = arr;
    vector<int> arr3 = arr;
    
    clock_t insStart = clock(); //measure time insertion sort 
    InsertionSort(&arr1, inscnt, insm); // get num comparison and memory access 
    clock_t insEnd = clock();
    instime.push_back(double(insEnd - insStart) / CLOCKS_PER_SEC); 
    inscomp.push_back(inscnt); //put comparison into vector 
    insmem.push_back(insm);//put memory access into vector 

    
    clock_t merStart = clock();//measure time merge sort 
    MergeSort(&arr2, mercnt, merm);// get num comparison and memory access 
    clock_t merEnd = clock();
    mertime.push_back(double(merEnd - merStart) / CLOCKS_PER_SEC);
    mercomp.push_back(mercnt);//put comparison into vector
    mermem.push_back(merm);//put memory access into vector 

    clock_t quiStart = clock();//measure time for quick sort 
    QuickSort(&arr3, quicnt, quim);// get num comparison and memory access 
    clock_t quiEnd = clock();
    quitime.push_back(double(quiEnd - quiStart) / CLOCKS_PER_SEC);
    quicomp.push_back(quicnt);//put comparison into vector
    quimem.push_back(quim);//put memory access into vector 
    
  }
  
    for(int i = 0; i < sample; i++) { //print out csv file with , in between 
     cout << samplename[i] << ",";
     cout << instime[i] << ",";
     cout << inscomp[i] << ",";
     cout << insmem[i] << ",";
     cout << mertime[i] << ",";
     cout << mercomp[i] << ",";
     cout << mermem[i] << ",";
     cout << quitime[i] << ",";
     cout << quicomp[i] << ",";
     cout << quimem[i] << "\n";
  }
  file.close(); // close the file 
  
}