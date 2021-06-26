#include <iostream>
#include <boost/filesystem.hpp>
#include <boost/lambda/bind.hpp>
#include <boost/range/iterator_range.hpp>
#include "datafile.hpp"
#include <thread>
#define COUNT_OF_THREADS 4

int main() {
  using namespace boost::filesystem;
  using namespace boost::lambda;

  // std::string DirectoryName = "./input/", ResultFileName = "./result.txt";
  std::string DirectoryName, ResultFileName;
  std::cout << "Enter directory:";
  std::getline(std::cin, DirectoryName);

  std::cout << "Enter result file:";
  std::getline(std::cin, ResultFileName);

  path DirectoryPath(DirectoryName);

  int NumOfFiles = std::count_if(
    directory_iterator(DirectoryPath),
    directory_iterator(),
    static_cast <bool(*)(const path&)>(is_regular_file)
  );

  std::vector<DataFile> df;

  for(auto& file: boost::make_iterator_range(directory_iterator(DirectoryPath), {})) {
    DataFile df_fill(file.path().string());
    df.push_back(df_fill);
  }

  std::thread ParsingThreads[COUNT_OF_THREADS];
  int ParsingSuccess = 0, CurrentParsing = 0;
  while (NumOfFiles != ParsingSuccess) {
    for(int i = 0; i < COUNT_OF_THREADS; i++) {
      if(ParsingSuccess+CurrentParsing == NumOfFiles) {
        break;
      }
      ParsingThreads[i] = std::thread(&DataFile::ParseFile, &df[ParsingSuccess+i]);
      CurrentParsing++;
    }

    for(int i = 0; i < CurrentParsing; i++) {
      ParsingThreads[i].join();
      ParsingSuccess++;
    }

    CurrentParsing = 0;
  }

  for(auto datafile: df) {
    datafile.SplitData();
    datafile.WriteResult(ResultFileName);
  }
}