#pragma once
#include <cstddef>
#include <tuple>

template <typename T, std::size_t N>
class generate_tuple
{
private:
  template <typename = std::make_index_sequence<N>>
  struct impl;

  template <std::size_t... ISeq>
  struct impl<std::index_sequence<ISeq...>>
  {
    template <std::size_t>
    using wrap = T;
    using type = std::tuple<wrap<ISeq>...>;
  };

public:
  using type = typename impl<>::type;
};

template <std::size_t N, typename T>
struct my_less_tuple
{
  template <std::size_t... Is>
  bool compare_function(const T &lhs, const T &rhs, const std::index_sequence<Is...>) const
  {
    return std::tie(std::get<Is>(lhs)...) < std::tie(std::get<Is>(rhs)...);
  }

  bool operator()(const T &lhs, const T &rhs) const
  {
    using index_seq = typename std::make_index_sequence<N>;
    return compare_function(lhs, rhs, index_seq{});
  }
};