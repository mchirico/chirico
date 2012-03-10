/* Copyright (c) 2005 GPL Mike Chirico mchirico@users.sourceforge.net or mchirico@comcast.net

  This is an example of creating a insensitive case
  comparison structure. 

  Reference Problem 1 in 
    Exceptional C++: 47 Engineering Puzzles, Programming Problems, and Solutions
    By Herb Sutter

  Download:
   http://prdownloads.sourceforge.net/cpearls/simple_but_common_cpp.tar.gz?download

  Compile:
    g++ -o string_toupper -Wall -W -O2 -s -pipe -DUSE_CTRAITS=1  string_toupper.cc

    or if you are using an older version of the stl

    g++ -o string_toupper -Wall -W -O2 -s -pipe -DUSE_CTRAITS=0  string_toupper.cc

*/
#include <string>
#include <iostream>
#include <cctype>


#
#if USE_CTRAITS
struct ic_traits : public std::char_traits<char> {
#else
struct ic_traits : public std::string_char_traits<char> {
#endif /* USE_CTRAITS */

  static bool eq (const char& c1, const char& c2) {
    return std::toupper(c1)==std::toupper(c2);
  }
  static bool lt(const char& c1, const char& c2) {
    return std::toupper(c1)<std::toupper(c2);
  }
  static int compare(const char* s1, const char* s2,
		     std::size_t n) {
    for(std::size_t i=0; i<n; ++i) {
      if (!eq(s1[i], s2[i])) {
	return lt(s1[i],s2[i])?-1:1;
      }
    }
    return 0;
  }



};

typedef std::basic_string<char, ic_traits> icstring;

inline
std::ostream& operator << (std::ostream& strm, const icstring& s)
{
  return strm << std::string(s.data(), s.length());
}

icstring&
operator+(icstring& s1, std::string& s2) {  return s1+=s2.c_str();}

icstring&
operator+=(icstring& s1, std::string& s2) {  return s1+=s2.c_str();}

std::string&
operator+(std::string& s1, icstring& s2) {  return s1+=s2.c_str();}

std::string&
operator+=(std::string& s1, icstring& s2) {  return s1+=s2.c_str();}


using namespace std;
int main(void)
{
  string s;
  icstring ics;

  ics="***";


  s="one";
  s+=" two";

  ics+=s;

  cout << s << endl;

  s+=ics;
  cout << ics << endl;
  ics= ics + s;
  cout << ics << endl;

}
