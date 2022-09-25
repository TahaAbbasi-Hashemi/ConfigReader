// This is a single hpp file that reads a configuration file. 
// This class is used as a supplment in a bigger program.
// This allows for custom modifications in a bigger program.
#ifndef CONFIG_READER_HPP
#define CONFIG_READER_HPP

#include <string>     // std::string
#include <map>        // std::map
#include <fstream>    // std::ifstream, std::getline

// Declaration
//  - m_ means member 
//  - f_ means function
//  - p_ means pointer 
//  - c_ means constant 
//  - g_ means getter 
//  - s_ means setter 
class ConfigReader {
  private:
    std::map<std::string, std::string> m_config;
    
    // String manipulation
    bool mf_startsWith(std::string needle, std::string haystack);
    std::string mf_key(std::string line);
    std::string mf_value(std::string line);
    
  public:
    ConfigReader(){};
    ConfigReader(std::string filename) { readConfig(filename); };
    
    void readConfig(std::string filename);
    
    // Getter and Setter
    std::string g_value(std::string key);
};
 

// Definition
// Checks if the line starts with a "#" meaning a comment. 
bool ConfigReader::mf_startsWith(std::string needle, std::string haystack) {
  return (haystack.find(needle) == 0);
};
 
// "key=value"
// This returns the key if there is one, otherwise returns an empty string.
std::string ConfigReader::mf_key(std::string line) {
  std::string _key = "";
  
  std::size_t pos = line.find("=");
  if (pos != std::string::npos) {
    _key = line.substr(0, pos);
  };
  
  return _key;
};
 
// "key=value"
// This returns the value if there is one, otherwise returns an empty string.
std::string ConfigReader::mf_value(std::string line) {
  std::string _value = "";
  
  std::size_t pos = line.find("=");
  if (pos != std::string::npos) {
    _value = line.substr(pos+1);
  };
  
  return _value;
};
 
 
// This function parses a file and saves the keys and values in a map. 
void ConfigReader::readConfig(std::string filename){
  // Open the file 
  std::ifstream configFile(filename);
  
  // Iterating line by line.
  if (configFile.is_open()) {
    std::string _line;
    while (std::getline(configFile, _line)) {
      // If the line is a comment ignore. 
      if (mf_startsWith("#", _line)) {
        continue;
      };
      // If the line is empty, also ignore.
      if (_line.empty()) {
        continue;
      };
      
      // If there is no '=' then both values are empty. 
      m_config[mf_key(_line)] = mf_value(_line);
    };
    configFile.close();
  };
  
};
 
// Returns the value from a given key
std::string ConfigReader::g_value(std::string key) {
  return m_config[key];
};
 

#endif

// Copyright (C) 2022 Taha Abbasi-Hashemi
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, version 3.
// This program is distributed in the hope that it will be useful, but
// WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
// or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for more details.
// You should have received a copy of the GNU General Public License along
// with this program. If not, see <https://www.gnu.org/licenses/>.
 
 

