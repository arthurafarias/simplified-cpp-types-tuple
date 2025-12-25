#pragma once

#include <TupleContainer.hpp>

template <typename... ContainedTypes> struct Tuple {

  template <typename... InitializerTypes>
  Tuple(const InitializerTypes &...values) {
    initialize(root, values...);
  }

  template <size_t Index, typename ElementType>
  constexpr void set(const ElementType &value) {
    if constexpr (Index == 0) {
      root.value = value;
    } else {
      set_by_index<Index - 1>(root.next, value);
    }
  }
  template <size_t Index> constexpr auto &get() {
    if constexpr (Index == 0) {
      return root.value;
    } else {
      return get<Index - 1>(root.next);
    }
  }

private:
  template <size_t Index, typename ContainerType, typename ElementType>
  constexpr void set_by_index(ContainerType &container, const ElementType &value) {

    if constexpr (std::is_same<ContainerType, EmptyContainer>::value) {
      return;
    } else if constexpr (Index == 0) {
      container.value = value;
    } else {
      set_by_index<Index-1>(container.next, value);
    }
  }

  template <typename ElementType, typename FirstType>
  void initialize(ElementType &element, const FirstType &first) {
    element.value = first;
  }

  template <typename 
  ElementType, typename FirstType, typename... OtherTypes>
  void initialize(ElementType &element, const FirstType &first,
           const OtherTypes &...others) {
    element.value = first;
    initialize(element.next, others...);
  }

  template <size_t Index, typename ElementType>
  constexpr auto &get(const ElementType &current) {

    if constexpr (Index == 0) {
      return current.value;
    } else {
      return get<Index - 1>(current.next);
    }
  }

  TupleContainer<0, ContainedTypes...> root;
};