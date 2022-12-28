//Usage: .SearchNewBooks <newBooks.dat> <request.dat> <result_file.dat>

#include <string>
#include <fstream>
#include <iostream>
#include <vector>
#include <sstream>
#include <algorithm> 
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <chrono> // NOLINT (build/c++11)
using namespace std;

class Time{
public: 
  std::chrono::high_resolution_clock::time_point start;
  std::chrono::high_resolution_clock::time_point end;
  double elapsed_us = std::chrono::duration<double, std::micro>(end - start).count();
};

class Books{
  public: 
    string language;
    string status;
    int num;

  bool operator < (const Books& B) {
  if(num > B.num) {
    return true;
  }
  else if(num == B.num) {
    if(status == "new" && (B.status == "digital" || B.status == "used")) {
      return true; //
    }
    else if( status == "used" && B.status == "digital") {
      return true; 
    }
    else if((status == "used" && B.status == "used") || (status == "new" && B.status == "new") || (status == "digital" && B.status == "digital")) {
      if( language.compare(B.language) == -1) {
        return false;
      }
      else if( language.compare(B.language) == 1) {
        return true;
      }
      else if( language.compare(B.language) == 0) {
        return false;
      }
      }
  }
    return false;
  }
};

int linear_search(vector<Books> const *newbooks, vector<Books> const *request){
  vector<Books> book = *newbooks;
  vector<Books> re = *request;
  vector<Books>::iterator i;
  vector<Books>::iterator j;
  int count = 0;
   for ( i = re.begin(); i != re.end(); i++ ){   
     for ( j = book.begin(); j != book.end(); j++ ) {
       if((i->num == j->num) && (i->language== j->language) && (i->status == j->status)) {
         count ++;
       }
     }
   }
  return count;
}

int binary_search(vector<Books> *newbooks, vector<Books> *request){
  vector<Books>::iterator i;
  vector<Books> book = *newbooks;
  vector<Books> re = *request;
  int count = 0;
  int k = 0; 
  int j = book.size(); //size of newbooks
  int r = re.size(); // size of request books
  sort(book.begin(), book.end());
  
  for(int a = 0; a < r; a++) {
    
    while(k<j) {
      int m = (k+j)/2;
      
      if(re[a].num < book[m].num) {
        k = m+1; //true
        }
        
      else if(re[a].num > book[m].num){
         j = m;
      }
        
      else if(re[a].num == book[m].num) {
        if(re[a].status == "new" && (book[m].status == "digital" || book[m].status == "used")) {
           j = m; //return true; 
          
          }
      else if(re[a].status == "used" && book[m].status == "digital") {
       j = m;//return true; 
        }
        
      else if((re[a].status == "used" && book[m].status == "used") || (re[a].status == "new" && book[m].status == "new") || (re[a].status == "digital" && book[m].status == "digital")) {
      if( re[a].language.compare(book[m].language) == -1) {
        j = m;
      }
      else if( re[a].language.compare(book[m].language) == 1) {
        k = m+1;
      }
      else if( re[a].language.compare(book[m].language) == 0) {
        count ++; 
        break;
      }
       }
        else{
          k = m+1;
        }
  }
}      
    k = 0;
    j = book.size();
  }
  return count;
}

int main(int argc, char** argv)
{
  Books book;
  Time ct;
  vector<Books> newbooks;
  vector<Books> request;
  vector<Books>::iterator i;
  vector<Books>::reverse_iterator it;
  string num;
  int number = 0;
  string lang;
  int numpos = 0;
  int lanpos = 0;
  string useranswer;
  int count = 0; 
  // bool conti = true;

  if(argc != 4) {
    cout<< "Usage: .SearchNewBooks <newBooks.dat> <request.dat> <result_file.dat>" << endl;
    return 0;
  }
  

  string fn1 = argv[1];
  string fn2 = argv[2];
  string fn3 = argv[3];
  ifstream f1 ("fn1");
  ifstream f2 ("fn2");
  ofstream f3 (fn3);

  f1.open(argv[1]);
  string input;
  if (f1.is_open()){ 
    while(f1){
      getline(f1,input);
      
      if(input != ""){
        for (int i = 0; i < (int)input.length(); i++) {
          if (input.substr(i,1) == ","){
            
            numpos = i;
            num = input.substr(0,i); // find the number here
            stringstream geek(num);
            geek >> number;        // convert string num to int num
            break;
            }
          }
      input = input.substr(numpos+1); // trunlanguage the word down to only lang and status 
       
      for (int i = 0; i <(int) input.length(); i++) {
        // int i;
        if (input.substr(i,1) == ","){
          lanpos = i;
          lang = input.substr(0,i); // find lang here 
          break;
          }
        }
      input = input.substr(lanpos+1); // trunlanguage again 
      book.status = input;
      book.language = lang; 
      book.num = number;
      newbooks.push_back(book);
      }
    }
  f1.close();
  }
  else{
     cout << "Error: cannot open file " <<argv[1]<<endl;
    return 0;
  }

  f2.open(argv[2]);
  if (f2.is_open()){
    while(f2){
      getline(f2,input);
      if(input != ""){
        for ( int i = 0; i < (int)input.length(); i++) {
          if (input.substr(i,1) == ","){
            numpos = i;
            num = input.substr(0,i); // find the number here
            stringstream geek(num);
            geek >> number;        // convert string num to int num
            break;
            }
          }
        
      input = input.substr(numpos+1); // trunlanguage the word down to only lang and status 
      for ( int i = 0; i < (int)input.length(); i++) {
        if (input.substr(i,1) == ","){
          lanpos = i;
          lang = input.substr(0,i); // find lang here 
          break;
          }
        }
        
      input = input.substr(lanpos+1); // trunlanguage again 
      book.status = input;
      book.language = lang; 
      book.num = number;
      request.push_back(book);
    }
    }
    f2.close();
  }
 else{
  cout << "Error: cannot open file " << argv[2] <<endl;
   return 0;
  }

  

    cout << "Choice of search method ([l]inear, [b]inary)?" << endl; 
    cin >> useranswer;
    while(useranswer != "l" && useranswer != "b" ) {
      cout << "Incorrect choice" << endl;
      cin >> useranswer;
    }

  if (useranswer == "l") {
    ct.start= std::chrono::high_resolution_clock::now();
    count = linear_search(&newbooks, &request); 
    cout << count << endl;
    ct.end = std::chrono::high_resolution_clock::now();
    double elapsed_us = std::chrono::duration<double, std::micro>(ct.end - ct.start).count();
    cout << "CPU time: " << elapsed_us << " microseconds";
  }
  else if (useranswer == "b") {
    ct.start= std::chrono::high_resolution_clock::now();
    count = binary_search(&newbooks, &request);
     cout << count << endl;
    ct.end = std::chrono::high_resolution_clock::now();
    double elapsed_us = std::chrono::duration<double, std::micro>(ct.end - ct.start).count();
    cout << "CPU time: " << elapsed_us << " microseconds";
  }
  
  if (f3.is_open())
  {
    f3 << count;
    f3.close();
  }
  else cout << "Unable to open file";
}

