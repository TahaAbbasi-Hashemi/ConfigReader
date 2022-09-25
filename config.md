# Table of Contents  

 - [Config Reader](#config-reader)
   - [*FILE ../include/config_reader.hpp*](#file-../include/config_reader.hpp)
   - [*CODE configreader_class*](#code-configreader_class)
   - [Future Additions ](#future-additions)
   - [String Manipulation](#string-manipulation)
     - [*CODE configreader_string_manipulation*](#code-configreader_string_manipulation)
     - [*CODE configreader_startswith_function*](#code-configreader_startswith_function)
     - [*CODE configreader_key_function*](#code-configreader_key_function)
     - [*CODE configreader_value_function*](#code-configreader_value_function)
   - [Reading the config file](#reading-the-config-file)
     - [*CODE configreader_readconfig_function*](#code-configreader_readconfig_function)
     - [*CODE configreader_getvalue_function*](#code-configreader_getvalue_function)
   - [Testing ](#testing)
     - [*FILE ../test/config_reader_test.cpp*](#file-../test/config_reader_test.cpp)




# Config Reader
> ## *FILE ../include/config_reader.hpp*
This is a single hpp file that reads a configuration file. 
This class is used as a supplment in a bigger program.
This allows for custom modifications in a bigger program.
~~~ c++
#ifndef CONFIG_READER_HPP
#define CONFIG_READER_HPP

#include <string>     // std::string
#include <map>        // std::map
#include <fstream>    // std::ifstream, std::getline

// Declaration
@call{ConfigReader_Class}

// Definition
@call{ConfigReader_String_Manipulation}
@call{ConfigReader_ReadConfig_Function}
@call{ConfigReader_getValue_Function}

#endif

@call{license}
~~~ 

> ## *CODE configreader_class*
 - m_ means member 
 - f_ means function
 - p_ means pointer 
 - c_ means constant 
 - g_ means getter 
 - s_ means setter 
~~~ c++
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
~~~ 

## Future Additions 
In the future a modification can be added to include enviroment variables in the configuration.


## String Manipulation
> ### *CODE configreader_string_manipulation*
~~~ c++
@call{ConfigReader_startsWith_function}
@call{ConfigReader_key_function}
@call{ConfigReader_value_function}
~~~ 

> ### *CODE configreader_startswith_function*
Checks if the line starts with a "#" meaning a comment. 
~~~ c++
bool ConfigReader::mf_startsWith(std::string needle, std::string haystack) {
  return (haystack.find(needle) == 0);
};
~~~ 

> ### *CODE configreader_key_function*
"key=value"
This returns the key if there is one, otherwise returns an empty string.
~~~ c++
std::string ConfigReader::mf_key(std::string line) {
  std::string _key = "";
  
  std::size_t pos = line.find("=");
  if (pos != std::string::npos) {
    _key = line.substr(0, pos);
  };
  
  return _key;
};
~~~ 

> ### *CODE configreader_value_function*
"key=value"
This returns the value if there is one, otherwise returns an empty string.
~~~ c++
std::string ConfigReader::mf_value(std::string line) {
  std::string _value = "";
  
  std::size_t pos = line.find("=");
  if (pos != std::string::npos) {
    _value = line.substr(pos+1);
  };
  
  return _value;
};
~~~ 

## Reading the config file
> ### *CODE configreader_readconfig_function*
This function parses a file and saves the keys and values in a map. 
~~~ c++
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
~~~ 

> ### *CODE configreader_getvalue_function*
Returns the value from a given key
~~~ c++
std::string ConfigReader::g_value(std::string key) {
  return m_config[key];
};
~~~ 

## Testing 
> ### *FILE ../test/config_reader_test.cpp*
~~~ c++
// C++
#include <iostream>
// Custom 
#include "config_reader.hpp"

int main(){
  std::cout << "Starting config reader tests\n";
  ConfigReader config1; 
  config1.readConfig("../test/config_reader_test.conf");
  ConfigReader config2("../test/config_reader_test.conf");
  
  if (config1.g_value("ALPHA") != "key_a"){
    std::cout << "Error on value ALPHA\n";
  };
  if (config1.g_value("ALPHA") != config2.g_value("ALPHA")) {
    std::cout << "Error on both vaules of ALPHA being the same\n";
  };
  
  std::cout << "Config Reader Test completed. If no error then it works correctly\n";
  
};
~~~ 







