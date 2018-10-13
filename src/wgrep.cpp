
#include <fstream>
#include <iostream>
#include <filesystem>
#include <unistd.h>
#include <stdio.h>
#include <vector>
#include <iterator>
#include <algorithm>
#include <boost/filesystem.hpp>
#include <boost/program_options.hpp>
#include <regex>
#include "homebrew/utils.hpp"

// #include <easylogging++.h>
// #include <easylogging++.cc>
// INITIALIZE_EASYLOGGINGPP

namespace fs = boost::filesystem;
namespace po = boost::program_options;


#define APP_NAME "wgrep"
#define VERSION "1.0.0"


int main(int argc, char* argv[])
{
  std::string file;
  std::string regex;
  std::vector<size_t> matches;

  std::string app_name = boost::filesystem::basename(argv[0]);
  po::options_description desc("Runs regex on a whole file. (I've always wanted this and its pretty dangeraous but ahhh, fuckt it!)");
  desc.add_options()
    ("help", "produce help message")
    ("file,f", po::value<std::string>(&file)->required(), "file to match against")
    ("match,m", po::value<std::vector<size_t>>(&matches)->multitoken(), "matches to print if there are more than one")
    ("expr,e", po::value<std::string>(&regex)->required(), "regex to run on the file");

  po::variables_map vm;
  po::positional_options_description positional_options; 
  positional_options.add("file", 1); 
  positional_options.add("expr", 1);

  
  po::store(po::command_line_parser(argc, argv).options(desc) 
            .positional(positional_options).run(), 
            vm); 
  if (vm.count("help"))
  {
    std::cout << "Programm: " << APP_NAME << "\n";
    std::cout << homebrew::make_usage_string(APP_NAME, desc, positional_options);
    std::cout << "Version: "  << VERSION << "\n";
    return 0;
  }
  
  try
  {
    po::notify(vm);
  }  
  catch(po::error& e) 
  { 
    std::cerr << "ERROR: " << e.what() << std::endl << '\n'; 
    std::cerr << desc << '\n'; 
    return -1; 
  }
  

  auto match = homebrew::regex_file(file, regex);

  if (!match.empty())
  {
    if (matches.size() == 0)
    {
      for (size_t i = 0; i < match.size(); ++i)
      {
        std::cout <<"Match " << i << ": " << match[i][0] << '\n';
        for (size_t j = 1; j < match[i].size(); ++j)
        {
          std::cout << "  Group " << j << ": " << match[i][j] << '\n';        
        }
      }
    }
    else
    {
      for (const auto& i : matches)
      {
        if(i >= match.size())
        {
          continue;
        }
        std::cout <<"Match " << i << ": " << match[i][0] << '\n';
        for (size_t j = 1; j < match[i].size(); ++j)
        {
          std::cout << "  Group " << j << ": " << match[i][j] << '\n';        
        }
      }
    }
    
  }

  return 0;
}
