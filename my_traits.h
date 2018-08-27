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
