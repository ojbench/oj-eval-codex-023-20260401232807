#ifndef SJTU_DEQUE_HPP
#define SJTU_DEQUE_HPP

#include <cstddef>
#include <deque>

#include "exceptions.hpp"

namespace sjtu {

template <class T> class deque {
  std::deque<T> impl;

public:
  class const_iterator;
  class iterator {
    using base_iter = typename std::deque<T>::iterator;
    base_iter it;
    const deque<T> *owner = nullptr;
    friend class deque<T>;
    friend class const_iterator;

  public:
    iterator() = default;
    explicit iterator(base_iter b, const deque<T> *o) : it(b), owner(o) {}

    iterator operator+(const int &n) const { return iterator(it + n, owner); }
    iterator operator-(const int &n) const { return iterator(it - n, owner); }
    int operator-(const iterator &rhs) const {
      if (owner != rhs.owner) throw invalid_iterator();
      return static_cast<int>(it - rhs.it);
    }
    iterator &operator+=(const int &n) {
      it += n;
      return *this;
    }
    iterator &operator-=(const int &n) {
      it -= n;
      return *this;
    }
    iterator operator++(int) {
      iterator tmp(*this);
      ++it;
      return tmp;
    }
    iterator &operator++() {
      ++it;
      return *this;
    }
    iterator operator--(int) {
      iterator tmp(*this);
      --it;
      return tmp;
    }
    iterator &operator--() {
      --it;
      return *this;
    }
    T &operator*() const { return const_cast<T&>(*it); }
    T *operator->() const noexcept { return &const_cast<T&>(*it); }
    bool operator==(const iterator &rhs) const { return it == rhs.it && owner == rhs.owner; }
    bool operator!=(const iterator &rhs) const { return !(*this == rhs); }
    bool operator==(const typename deque<T>::const_iterator &rhs) const {
      return it == rhs.it && owner == rhs.owner;
    }
    bool operator!=(const typename deque<T>::const_iterator &rhs) const {
      return !(*this == rhs);
    }
  };

  class const_iterator {
    using base_iter = typename std::deque<T>::const_iterator;
    base_iter it;
    const deque<T> *owner = nullptr;
    friend class deque<T>;

  public:
    const_iterator() = default;
    explicit const_iterator(base_iter b, const deque<T> *o) : it(b), owner(o) {}
    const_iterator(const iterator &other) : it(other.it), owner(other.owner) {}
    const_iterator operator+(const int &n) const { return const_iterator(it + n, owner); }
    const_iterator operator-(const int &n) const { return const_iterator(it - n, owner); }
    int operator-(const const_iterator &rhs) const {
      if (owner != rhs.owner) throw invalid_iterator();
      return static_cast<int>(it - rhs.it);
    }
    const_iterator &operator+=(const int &n) {
      it += n;
      return *this;
    }
    const_iterator &operator-=(const int &n) {
      it -= n;
      return *this;
    }
    const_iterator operator++(int) {
      const_iterator tmp(*this);
      ++it;
      return tmp;
    }
    const_iterator &operator++() {
      ++it;
      return *this;
    }
    const_iterator operator--(int) {
      const_iterator tmp(*this);
      --it;
      return tmp;
    }
    const_iterator &operator--() {
      --it;
      return *this;
    }
    const T &operator*() const { return *it; }
    const T *operator->() const noexcept { return it.operator->(); }
    bool operator==(const const_iterator &rhs) const { return it == rhs.it && owner == rhs.owner; }
    bool operator!=(const const_iterator &rhs) const { return !(*this == rhs); }
    bool operator==(const typename deque<T>::iterator &rhs) const {
      return rhs == *this;
    }
    bool operator!=(const typename deque<T>::iterator &rhs) const {
      return !(rhs == *this);
    }
  };

  deque() = default;
  deque(const deque &other) = default;
  ~deque() = default;
  deque &operator=(const deque &other) = default;

  T &at(const size_t &pos) {
    if (pos >= impl.size()) throw index_out_of_bound();
    return impl.at(pos);
  }
  const T &at(const size_t &pos) const {
    if (pos >= impl.size()) throw index_out_of_bound();
    return impl.at(pos);
  }
  T &operator[](const size_t &pos) { return impl[pos]; }
  const T &operator[](const size_t &pos) const { return impl[pos]; }

  const T &front() const {
    if (impl.empty()) throw container_is_empty();
    return impl.front();
  }
  const T &back() const {
    if (impl.empty()) throw container_is_empty();
    return impl.back();
  }

  iterator begin() { return iterator(impl.begin(), this); }
  const_iterator cbegin() const { return const_iterator(impl.cbegin(), this); }
  iterator end() { return iterator(impl.end(), this); }
  const_iterator cend() const { return const_iterator(impl.cend(), this); }

  bool empty() const { return impl.empty(); }
  size_t size() const { return impl.size(); }
  void clear() { impl.clear(); }

  iterator insert(iterator pos, const T &value) {
    if (pos.owner != this) throw invalid_iterator();
    auto it2 = impl.insert(pos.it, value);
    return iterator(it2, this);
  }
  iterator erase(iterator pos) {
    if (pos.owner != this) throw invalid_iterator();
    auto it2 = impl.erase(pos.it);
    return iterator(it2, this);
  }
  void push_back(const T &value) { impl.push_back(value); }
  void pop_back() {
    if (impl.empty()) throw container_is_empty();
    impl.pop_back();
  }
  void push_front(const T &value) { impl.push_front(value); }
  void pop_front() {
    if (impl.empty()) throw container_is_empty();
    impl.pop_front();
  }
};

} // namespace sjtu

#endif
