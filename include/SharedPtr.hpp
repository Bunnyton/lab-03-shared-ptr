// Copyright 2021 Galaktionov Andrey <galaktionovaa@student.bmstu.ru>

#ifndef INCLUDE_SHAREDPTR_HPP_
#define INCLUDE_SHAREDPTR_HPP_

#include <atomic>
#include <iostream>
#include <utility>

template <typename T>
class SharedPtr {
 public:
  std::atomic_uint* _count;
  T* _ptr;

 public:
  SharedPtr() : _count(nullptr), _ptr(nullptr) {}


  explicit SharedPtr(T* ptr) : _ptr(ptr) {
    if (ptr) _count = new std::atomic_uint(1);
  }

  SharedPtr(const SharedPtr& r) {
    _ptr = nullptr;
    _count = nullptr;
    *this = r;
  }

  SharedPtr(SharedPtr&& r) {
    _ptr = nullptr;
    _count = nullptr;
    *this = std::forward<SharedPtr>(r);
    r._count = nullptr;
    r._ptr = nullptr;
  }

  ~SharedPtr() {
    if (_ptr) {
      if (_count->load() == 1) {
        delete _ptr;
        delete _count;
      } else {
        (*_count)--;
      }
    }
  }

  auto operator=(const SharedPtr& r) -> SharedPtr& {
    if (this == &r) return *this;

    if (_ptr) {
      if (_count->load() <= 1) {
        delete _ptr;
        delete _count;
      } else {
        (*_count)--;
      }
    }

    _ptr = r._ptr;
    _count = r._count;

    if (_ptr) (*_count)++;
    return *this;
  }

  auto operator=(SharedPtr&& r) -> SharedPtr& {
    if (this == &r) return *this;

    if (_ptr) {
      if (_count->load() == 1) {
        delete _ptr;
        delete _count;
      } else {
        (*_count)--;
      }
    }

    _ptr = r._ptr;
    _count = r._count;

    return *this;
  }

  // проверяет, указывает ли указатель на объект
  operator bool() const {
    if (_ptr) return true;
    return false;
  }

  auto operator*() const -> T& { return *_ptr; }

  auto operator->() const -> T* { return _ptr; }

  auto get() -> T* { return _ptr; }

  void reset() {
    if (_ptr) delete _count;
    _ptr = nullptr;
    _count = nullptr;
  }

  void reset(T* ptr) {
    if (_ptr) delete _count;
    _ptr = ptr;
    _count = new std::atomic_uint(1);
  }

  void swap(SharedPtr& r) {
    std::swap(_ptr, r._ptr);
    std::swap(_count, r._count);
  }

  // возвращает количество объектов SharedPtr, которые ссылаются на тот же
  // управляемый объект
  auto use_count() const -> size_t {
    if (_ptr == nullptr) return 0;
    return static_cast<size_t>(_count->load());
  }
};

#endif  // INCLUDE_SHAREDPTR_HPP_
