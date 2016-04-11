#ifndef __ZUOPAR_UTILS_PRINT_VECTOR_H__
#define __ZUOPAR_UTILS_PRINT_VECTOR_H__

#include <vector>
#include <iostream>

template<typename T>
std::ostream& operator<< (std::ostream& out, const std::vector<T>& v) {
  out << "[";
  size_t last = v.size() - 1;
  for(size_t i = 0; i < v.size(); ++i) {
    out << v[i];
    if (i != last) 
      out << ", ";
  }
  out << "]";
  return out;
}

#endif  //  
