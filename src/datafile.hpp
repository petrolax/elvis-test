#pragma once
#include <string>
#include <vector>

class DataFile {
  private:
    std::string filename,
                mainstring;
    std::vector <char> separators;
    std::vector <std::string> result;
  public:
  DataFile(std::string name): filename(name) {}
  void ParseFile();
  void SplitData();
  void WriteResult(std::string path);
};