#include "datafile.hpp"
#include <iostream>
#include <fstream>


void DataFile::ParseFile() {
  std::ifstream file(filename);
  if (!file.is_open()) {
    std::cout << filename << " isn't open" << std::endl;
    return;
  }

  getline(file, mainstring);
  while(1) {
    std::string separator;
    getline(file, separator);
    if (separator == "") break;
    separators.push_back(separator[0]);
  }

  result.push_back(filename);
  file.close();
}

void DataFile::SplitData() {
  if(mainstring.length() == 0) return;
  int prev = 0;
  std::string substrdata;
  for(int i = 0; i < mainstring.length(); i++) {
    if (mainstring[i] == separators[0]) {
      substrdata = mainstring.substr(prev, i - prev);
      if (substrdata != "") {
        result.push_back(substrdata);
      }
      prev = i+1;
    }
  }
  substrdata = mainstring.substr(prev);
  if (substrdata != "") {
    result.push_back(substrdata);
  }
  prev = 0;
  
  for(int i = 1; i < separators.size(); i++) {
    std::vector <std::string> rescopy;
    for(int j = 0; j < result.size(); j++) {
      for(int k = 0; k < result[j].length(); k++) {
        if(result[j][k] == separators[i]) {
          substrdata = result[j].substr(prev, k - prev);
          if (substrdata != "") rescopy.push_back(substrdata);
          prev = k+1;
        }
      }
      substrdata = result[j].substr(prev);
      if (substrdata != "") rescopy.push_back(substrdata);
      prev = 0;
    }
    result = rescopy;
  }
}

void DataFile::WriteResult(std::string path) {
  if(result.size() == 0) return;
  std::ofstream file(path, std::ios::app);
  for(auto data: result) file << data << std::endl;
  file.close();
}
