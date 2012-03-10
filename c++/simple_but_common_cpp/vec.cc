/*
   Simple vector class ... this is not finished.



*/



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
  vec( const vec<O,osize>& other ): index(0) 
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
  void push_back(const T& t)
  {
    if(index > size)
      {
        index=size;
        v_[index]=t;

      }else {
      v_[index++]=t;
      }
  }

  T at(int i)
  {
    return  v_[std::min(size,(size_t)i)];
  }

  size_t         get_size() { return size; }
  iterator       begin() { return v_; }
  iterator       end() { return v_+size; }
  const_iterator begin() const { return v_; }
  const_iterator end()   const { return v_+size; }

private:
  size_t index;
  T v_[size];
};

int main(void)
{
  vec<int,5> fv;
  vec<int,15> fv2;
  fv2.push_back(3);
  fv2.push_back(1);
  fv2.push_back(453);
  fv2.push_back(23);

  fv2[2]=2234;  


  std::cout << "fv.get_size() = " << fv.get_size() << std::endl;
  fv=fv2;
  std::cout << "fv.get_size() = " << fv.get_size() << std::endl;
  std::cout << "fv[0] = " <<  fv[0] << std::endl;
  std::cout << "fv[1] = " <<  fv[1] << std::endl;
  std::cout << "fv[2] = " <<  fv[2] << std::endl;
  std::cout << "fv[3] = " <<  fv[3] << std::endl;

  


}
