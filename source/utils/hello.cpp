/*
author : Serhat Istin
	 istins@gmail.com
*/
#include <iostream>
#include <string>
int main(){
  [](const std::string& msg){ std::cout<<msg<<'\n';}("Hello");
  return 0;
}
