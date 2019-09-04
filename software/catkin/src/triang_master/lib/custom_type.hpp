#ifndef _CUSTOM_TYPE_HPP_
#define _CUSTOM_TYPE_HPP_

#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <string>

#include <atomic>
#include <vector>




template <typename T>
struct atomwrapper
{
  std::atomic<T> _a;

  atomwrapper()
    :_a()
  {}

  atomwrapper(const std::atomic<T> &a)
    :_a(a.load())
  {}

  atomwrapper(const atomwrapper &other)
    :_a(other._a.load())
  {}

  atomwrapper &operator=(const atomwrapper &other)
  {
    _a.store(other._a.load());
  }
};



#endif
