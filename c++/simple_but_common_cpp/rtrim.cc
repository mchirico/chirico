#include <string>
#include <iostream>

std::string rtrim(std::string& s, char c) {
  
  if (s.empty())
    return s;

  std::string::iterator p;
  for(p=s.end(); p!=s.begin() && *--p==c;);
  
  if(*p!=c)
    p++;
  
  s.erase(p,s.end());
  return s;
}
    
int main(void)
{
  std::string s = "more ";
  std::cout << "-->" << rtrim(s,' ') << "<--" << std::endl;


}
