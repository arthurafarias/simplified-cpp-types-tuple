#pragma once

#include <EmptyContainer.hpp>
#include <cstddef>
#include <type_traits>

template <size_t Index, typename ContainedType = EmptyContainer,
          typename... OtherTypes>
struct TupleContainer {
  using type = ContainedType;
  using next_type =
      typename std::conditional<std::is_same<ContainedType, EmptyContainer>::value,
                                EmptyContainer,
                                TupleContainer<Index + 1, OtherTypes...>>::type;
  type value;
  next_type next;
  constexpr size_t index() { return Index; }
};