#include <stdexcept>
using std::runtime_error;

class DivideByZeroException: public runtime_error
{
 public:
 DivideByZeroException(): runtime_error("attempted to divide by zero") {}
};

