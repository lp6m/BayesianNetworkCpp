#include <bits/stdc++.h>

using namespace std;

#ifndef Define_Util
#define Define_Util

#define FOR(i,a,b) for(int i=(int)(a);i<(int)(b);i++)
#define REP(i,n) for(int i=0;i<(int)(n);i++)

class Util{
public:
  Util();
  static vector<string> string_split(const string& s, char delim){
    vector<string> elems;
    stringstream ss(s);
    string item;
    while (getline(ss, item, delim)) {
    if (!item.empty()) {
            elems.push_back(item);
        }
    }
    return elems;
  }
  static string string_trim(const std::string& string, const char* trimCharacterList = " \t\v\r\n"){
    std::string result;
    std::string::size_type left = string.find_first_not_of(trimCharacterList);
    if (left != std::string::npos){
      std::string::size_type right = string.find_last_not_of(trimCharacterList);
      result = string.substr(left, right - left + 1);
    }
      return result;
  }
  
};
// void showVI(vector<int> data){
//   cout << "[";
//   REP(i, data.size()){
//     cout << data[i];
//     if(i != data.size() - 1) cout << ", ";
//   }
//   cout << "]";
// }
// void showVVI(vector<vector<int>> data){
//   cout << "[";
//   REP(i, data.size()){
//     cout << "[";
//     REP(j, data[i].size()){
//       cout << data[i][j];
//       if(j != data[i].size() - 1) cout << ", ";
//     }
//     cout << "]";
//     if(i != data.size() - 1) cout << ", ";
//   }
//   cout << "]" << endl;
// }

#endif
