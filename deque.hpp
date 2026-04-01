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
    long long idx = 0;
    const deque<T> *owner = nullptr;
    friend class deque<T>;
    friend class const_iterator;

  public:
    iterator() = default;
    explicit iterator(long long i, const deque<T> *o) : idx(i), owner(o) {}

    iterator operator+(const int &n) const { return iterator(idx + n, owner); }
    iterator operator-(const int &n) const { return iterator(idx - n, owner); }
    int operator-(const iterator &rhs) const {
      if (owner != rhs.owner) throw invalid_iterator();
      return static_cast<int>(idx - rhs.idx);
    }
    iterator &operator+=(const int &n) {
      idx += n;
      return *this;
    }
    iterator &operator-=(const int &n) {
      idx -= n;
      return *this;
    }
    iterator operator++(int) {
      iterator tmp(*this);
      ++idx;
      return tmp;
    }
    iterator &operator++() {
      ++idx;
      return *this;
    }
    iterator operator--(int) {
      iterator tmp(*this);
      --idx;
      return tmp;
    }
    iterator &operator--() {
      --idx;
      return *this;
    }
    T &operator*() const {
      if (owner == nullptr || idx < 0 || static_cast<size_t>(idx) >= owner->impl.size())
        throw invalid_iterator();
      return const_cast<T &>(owner->impl[static_cast<size_t>(idx)]);
    }
    T *operator->() const {
      if (owner == nullptr || idx < 0 || static_cast<size_t>(idx) >= owner->impl.size())
        throw invalid_iterator();
      return &const_cast<T &>(owner->impl[static_cast<size_t>(idx)]);
    }
    bool operator==(const iterator &rhs) const { return idx == rhs.idx && owner == rhs.owner; }
    bool operator!=(const iterator &rhs) const { return !(*this == rhs); }
  };

  class const_iterator {
    long long idx = 0;
    const deque<T> *owner = nullptr;
    friend class deque<T>;

  public:
    const_iterator() = default;
    explicit const_iterator(long long i, const deque<T> *o) : idx(i), owner(o) {}
    const_iterator(const iterator &other) : idx(other.idx), owner(other.owner) {}
    const_iterator operator+(const int &n) const { return const_iterator(idx + n, owner); }
    const_iterator operator-(const int &n) const { return const_iterator(idx - n, owner); }
    int operator-(const const_iterator &rhs) const {
      if (owner != rhs.owner) throw invalid_iterator();
      return static_cast<int>(idx - rhs.idx);
    }
    const_iterator &operator+=(const int &n) {
      idx += n;
      return *this;
    }
    const_iterator &operator-=(const int &n) {
      idx -= n;
      return *this;
    }
    const_iterator operator++(int) {
      const_iterator tmp(*this);
      ++idx;
      return tmp;
    }
    const_iterator &operator++() {
      ++idx;
      return *this;
    }
    const_iterator operator--(int) {
      const_iterator tmp(*this);
      --idx;
      return tmp;
    }
    const_iterator &operator--() {
      --idx;
      return *this;
    }
    const T &operator*() const {
      if (owner == nullptr || idx < 0 || static_cast<size_t>(idx) >= owner->impl.size())
        throw invalid_iterator();
      return owner->impl[static_cast<size_t>(idx)];
    }
    const T *operator->() const {
      if (owner == nullptr || idx < 0 || static_cast<size_t>(idx) >= owner->impl.size())
        throw invalid_iterator();
      return &owner->impl[static_cast<size_t>(idx)];
    }
    bool operator==(const const_iterator &rhs) const { return idx == rhs.idx && owner == rhs.owner; }
    bool operator!=(const const_iterator &rhs) const { return !(*this == rhs); }
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

  iterator begin() { return iterator(0, this); }
  const_iterator cbegin() const { return const_iterator(0, this); }
  iterator end() { return iterator(static_cast<long long>(impl.size()), this); }
  const_iterator cend() const { return const_iterator(static_cast<long long>(impl.size()), this); }

  bool empty() const { return impl.empty(); }
  size_t size() const { return impl.size(); }
  void clear() { impl.clear(); }

  iterator insert(iterator pos, const T &value) {
    if (pos.owner != this) throw invalid_iterator();
    long long p = pos.idx;
    if (p < 0 || p > static_cast<long long>(impl.size())) throw invalid_iterator();
    impl.insert(impl.begin() + p, value);
    return iterator(p, this);
  }
  iterator erase(iterator pos) {
    if (pos.owner != this) throw invalid_iterator();
    long long p = pos.idx;
    if (p < 0 || p >= static_cast<long long>(impl.size())) throw invalid_iterator();
    impl.erase(impl.begin() + p);
    // Return iterator to following element (same index p), or end() if erased last
    if (p > static_cast<long long>(impl.size())) p = static_cast<long long>(impl.size());
    return iterator(p, this);
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
