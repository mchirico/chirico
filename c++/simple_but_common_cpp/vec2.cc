#include <iostream>
#include <algorithm>
template<typename T, size_t size> 
class vec
{
public:
  typedef T*       iterator;
  typedef const T* const_iterator;
  vec() { }

  template<typename O, size_t osize>
  vec( const vec<O,osize>& other )
  {
    std::copy( other.begin(),
          other.begin()+std::min(size,osize),
          begin() );
  }

  template<typename O, size_t osize>
  vec<T,size>&
  operator=( const vec<O,osize>& other )
  {
    std::copy( other.begin(),
          other.begin()+std::min(size,osize),
          begin() );
    return *this;
  }


  T& operator[](const int& i){
    return v_[std::min(size,(size_t)i)];
  }
  void add(int i,const T& t)
  {
    v_[std::min(size,(size_t)i)]=t;
  }

  T get(int i)
  {
    return  v_[std::min(size,(size_t)i)];
  }

  size_t         get_size() { return size; }
  iterator       begin() { return v_; }
  iterator       end() { return v_+size; }
  const_iterator begin() const { return v_; }
  const_iterator end()   const { return v_+size; }

private:
  T v_[size];
};

int main(void)
{
  vec<int,5> fv;
  vec<int,15> fv2;
  fv2.add(3,3);
  fv2.add(0,1);

  fv2[2]=2;  

  std::cout << fv.get_size() << std::endl;
  fv=fv2;
  std::cout << fv.get_size() << std::endl;
  std::cout << fv[0] << std::endl;
  std::cout << fv[2] << std::endl;
  


}
