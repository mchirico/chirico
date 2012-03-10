/* See pg 117. see need to look at this

*/

class X{
public:
  template<class T>
  void f(const T& t) {}

private:
  int private_;
};

namespace {
  struct Y{};
}

template<>
void X::f(const Y&) {
  private_ = 2;
}

int main(void)
{
  

}
