#include <iostream>
#include <vector>
#include<string>


using namespace std;
int main(){
    vector <string> vec;
    vec.push_back("hello world");
    vec.push_back("hello shin");
    string vecstr(vec.begin(), vec.end());
    cout << vecstr ;
}