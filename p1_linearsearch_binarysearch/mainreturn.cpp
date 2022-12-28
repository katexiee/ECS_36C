#include <string>
#include <fstream>
#include <iostream>
#include <vector>
using namespace std;

int main(int argc, char** argv)
{

  cout << "You have entered " << argc
         << " arguments:" << "\n";
  
  string fn = argv[1];
  ifstream f ("fn");
  f.open(fn);
  string input;
  if (f.is_open()){
    cout<< "you have enter the if\n";
    while(f){
      cout<< "you have enter the while\n";
      getline(f,input);
      cout << input;
    }
  }
  else{
     cout << "you did not opend the file\n";
  }
  f.close();
}