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
 

