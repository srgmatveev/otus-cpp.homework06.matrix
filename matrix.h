#pragma once
#include <cstddef>
#include <iostream>
#include <memory>
#include <tuple>
#include <set>
#include <iterator>
#include <utility>
#include "my_traits.h"

template <typename T, T def_val, std::size_t dimension = 2>
class Matrix
{
private:
  class MatrixStorage
  {
  private:
    using index_tuple_type = typename generate_tuple<std::size_t, dimension>::type;
    using tuple_type = decltype(
        std::tuple_cat(index_tuple_type{},
                       std::make_tuple(T{})));
    std::set<tuple_type, my_less_tuple<dimension, tuple_type>> _storage_set;

  public:
    void set_element(const index_tuple_type &tupl, const T &val)
    {
      tuple_type tmp_tuple = std::tuple_cat(tupl, std::make_tuple(val));
      auto iter = _storage_set.find(tmp_tuple);
      if (iter != _storage_set.cend())
      {
        if (std::get<dimension>(*iter) != val)
          _storage_set.erase(iter);
      }
      if (val != def_val)
        _storage_set.insert(tmp_tuple);
    }
    auto get_size() const { return _storage_set.size(); }
    T get_element(const index_tuple_type &tupl)
    {
      tuple_type tmp_tuple = std::tuple_cat(
          tupl, std::make_tuple(T{}));
      auto iter = _storage_set.find(tmp_tuple);
      if (iter != _storage_set.cend())
      {
        return std::get<dimension>(*iter);
      }
      return def_val;
    }

    using iterator = typename std::set<tuple_type>::iterator;
    auto get_begin() noexcept { return _storage_set.begin(); }
    auto get_end() noexcept { return _storage_set.end(); }
    auto get_cbegin() const noexcept { return _storage_set.cbegin(); }
    auto get_cend() const noexcept { return _storage_set.cend(); }

    MatrixStorage() = default;
    MatrixStorage(const MatrixStorage &rhs)
    {
      this->_storage_set.clear();
      for (auto &item : rhs._storage_set)
        this->_storage_set.insert(item);
    }

    MatrixStorage &operator=(const MatrixStorage &rhs)
    {
      if (this == &rhs)
        return *this;
      this->_storage_set.clear();
      for (auto &item : rhs._storage_set)
        this->_storage_set.insert(item);
      return *this;
    }

    bool operator==(const MatrixStorage &);
  };

  template <typename TUPLE>
  class MatrixAdapter
  {
  public:
    explicit MatrixAdapter(Matrix *matrix, const TUPLE &my_tuple) : _matrix(matrix), _tuple(my_tuple) {}
    auto &operator=(const T &rhs)
    {
      if (_matrix->_storage)
        _matrix->_storage->set_element(_tuple, rhs);
      return *this;
    }

    auto operator[](const std::size_t &index)
    {
      using next_type = decltype(std::tuple_cat(_tuple, std::make_tuple(index)));
      return MatrixAdapter<next_type>(_matrix, std::tuple_cat(_tuple, std::make_tuple(index)));
    }
    operator T() const
    {
      if (_matrix->_storage)
        return _matrix->_storage->get_element(_tuple);
      return def_val;
    }

  private:
    Matrix *_matrix;
    std::size_t _index{0};
    TUPLE _tuple;
  };

public:
  Matrix() : _storage(std::make_shared<MatrixStorage>()) {}
  Matrix(const Matrix &);
  Matrix(Matrix &&);
  Matrix &operator=(const Matrix &);
  Matrix &operator=(Matrix &&);
  bool operator==(const Matrix &);
  std::size_t size() const
  {
    if (_storage)
      return _storage->get_size();
    return 0;
  }

  auto operator[](const std::size_t &index)
  {
    return MatrixAdapter<std::tuple<std::size_t>>(this,
                                                  std::make_tuple(index));
  }

  auto begin() noexcept { return _storage->get_begin(); }
  auto end() noexcept { return _storage->get_end(); }
  auto begin() const noexcept { return _storage->get_begin(); }
  auto end() const noexcept { return _storage->get_end(); }
  auto cbegin() const noexcept { return _storage->get_cbegin(); }
  auto cend() const noexcept { return _storage->get_cend(); }

private:
  std::shared_ptr<MatrixStorage> _storage{nullptr};
};

template <typename T, T def_val, std::size_t dimension>
Matrix<T, def_val, dimension>::Matrix(const Matrix<T, def_val, dimension> &rhs) : _storage{std::make_shared<MatrixStorage>(*rhs._storage)}
{
}

template <typename T, T def_val, std::size_t dimension>
Matrix<T, def_val, dimension>::Matrix(Matrix<T, def_val, dimension> &&rhs)
{
  if (this != &rhs)
  {
    std::swap(_storage, rhs._storage);
  }
}

template <typename T, T def_val, std::size_t dimension>
Matrix<T, def_val, dimension> &Matrix<T, def_val, dimension>::operator=(const Matrix<T, def_val, dimension> &rhs)
{
  if (this == &rhs)
    return *this;
  *(_storage) = *(rhs._storage);
  return *this;
}

template <typename T, T def_val, std::size_t dimension>
Matrix<T, def_val, dimension> &Matrix<T, def_val, dimension>::operator=(Matrix<T, def_val, dimension> &&rhs)
{
  if (this != &rhs)
  {
    if (_storage)
      _storage = nullptr;
    std::swap(_storage, rhs._storage);
  }
  return *this;
}

template <typename T, T def_val, std::size_t dimension>
bool Matrix<T, def_val, dimension>::operator==(const Matrix<T, def_val, dimension> &rhs)
{
  if (this == &rhs)
    return true;
  if (this)
  {
    if (this->_storage == rhs._storage)
      return true;
    if (*this->_storage == *rhs._storage)
      return true;
  }
  return false;
}

#define M_Storage_type Matrix<T, def_val, dimension>::MatrixStorage

template <typename T, T def_val, std::size_t dimension>
bool M_Storage_type::operator==(const M_Storage_type &rhs)
{
  if (this->_storage_set == rhs._storage_set)
    return true;

  return false;
}
#undef M_Storage_type