#pragma once

#include <fstream>
#include <iostream>
#include <filesystem>
#include <unistd.h>
#include <stdio.h>
#include <vector>
#include <iterator>
#include <algorithm>
#include <regex>
#include <tuple>
#include <boost/filesystem.hpp>
#include <boost/program_options.hpp>

// #include <easylogging++.h>
// #include <easylogging++.cc>




namespace homebrew{

  namespace fs = boost::filesystem;
  namespace po = boost::program_options;


  
  template<class T>
  int dump(const std::vector<T>& vec, const std::string& file)
  {
    std::ofstream out_f(file);
    if (!out_f.is_open())
    {
      // LOGF(INFO, "Could not open file (%s)",file);
      return -1;
    }
    std::copy(std::begin(vec),std::end(vec),std::ostream_iterator<T>(out_f,"\n"));
    out_f.close();
    return 0;
  }

  template<class T>
  int load(std::vector<T>& vec, const std::string& file)
  {
    std::ifstream in_f(file);
    if (!in_f.is_open())
    {
      // LOGF(INFO,"Could not open file (%s)", file);
      return -1;
    }
    std::string line;
    T var;
    while(std::getline(in_f, line))
    {
      std::istringstream iss(line);
      iss >> var;
      vec.push_back(var);
    }
    in_f.close();
    return 0;
  }

  std::vector<std::vector<std::string>> regex_file(const std::string& file, const std::string& regex);
  std::string make_usage_string(const std::string& program_name, const po::options_description& desc, po::positional_options_description& p);
  std::vector<std::string> _get_unlimited_positional_args(const po::positional_options_description& p);

  
}
