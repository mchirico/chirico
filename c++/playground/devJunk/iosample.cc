#include <iostream>
#include <iomanip>
using namespace std;
int main() {
  const float tenth = 0.1;
  const float one   = 1.0;
  const float big   = 1234567890.0;
                            
  cout << "A. "                    << tenth << ", " << one << ", " << big << endl;
  cout << "B. " << fixed           << tenth << ", " << one << ", " << big << endl;
  cout << "C. " << scientific      << tenth << ", " << one << ", " << big << endl;
  cout << "D. " << fixed << setprecision(3) << tenth << ", " << one << ", " << big << endl;
  cout << "E. " << setprecision(20) << tenth << endl;
  cout << "F. " << setw(8) << setfill('*') << 34 << 45 << endl;
  cout << "G. " << setw(8) << 34 << setw(8) << 45 << endl;
    
  return 0;
}
