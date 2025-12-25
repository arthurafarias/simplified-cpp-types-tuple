# TupleContainer - A C++ Type-Tuple Implementation

This project provides a simple implementation of a type-safe, recursive tuple-like container in C++. It demonstrates the use of template metaprogramming and recursive structures to simulate a tuple with custom behaviors.

to build this project use [cxpm](https://github.com/arthurafarias/cxpm) package manager.

## Overview

The `TupleContainer` and `Tuple` structures allow you to store different types in a sequence and access them in a type-safe manner. This implementation is inspired by tuples but uses recursive template structures to represent the different types. 

The design allows:

- Storing various types in a custom container, simulating a type-safe "tuple".
- Accessing and setting values by index.
- Recursive container handling to accommodate an arbitrary number of types.

## Key Components

### `TupleContainer`

A recursive template that stores a type and a reference to the next container. It is used to simulate a list of types, with each container holding one type and linking to the next one.

```cpp
template <size_t Index, typename ContainedType = EmptyContainer, typename... OtherTypes>
struct TupleContainer {
  using type = ContainedType;
  using next_type = typename std::conditional<std::is_same<ContainedType, EmptyContainer>::value,
                                               EmptyContainer,
                                               TupleContainer<Index + 1, OtherTypes...>>::type;
  type value;
  next_type next;
  constexpr size_t index() { return Index; }
};
```

### `Tuple`

This is the main container that users will interact with. It uses TupleContainer internally to store each type, and it provides methods to set and get values by index.

```cpp
template <typename... ContainedTypes> 
struct Tuple {
  Tuple(const InitializerTypes &...values);
  template <size_t Index, typename ElementType>
  constexpr void set(const ElementType &value);
  template <size_t Index> constexpr auto& get();
  
private:
  TupleContainer<0, ContainedTypes...> root;
};
```

### Key Functions

- Constructor (Tuple): Initializes the container with a variadic list of values.
- set(): Set the value of a given index in the container.
- get(): Retrieves the value stored at a specific index in the container.

### Example Usage

#### Tuple Container

```cpp
// Instantiate TupleContainer with int and double types
TupleContainer<0, int, double> member;

// Accessing values
auto value_int = member.value;  // int
auto value_double = member.next.value;  // double
```

#### Tuple Example

```cpp
// Instantiate a Tuple with an int and std::string
Tuple<int, std::string> tuple{1, "Hello Tuple"};

// Get values by index
auto value_int = tuple.get<0>(); // value_int is 1
auto value_string = tuple.get<1>(); // value_string is "Hello Tuple"
```

#### How it Works

1. `TupleContainer`: Each instantiation of `TupleContainer` holds a type and a reference to the next `TupleContainer`. This allows storing multiple types in a chain, with each container holding a single type and linking to the next one.

2. Recursion in `TupleContainer`: The recursion continues until `EmptyContainer` is reached, marking the end of the chain.

3. `TupleAccess`
    - `get<Index>()` traverses the chain of `TupleContainers` to retrieve the value at the specified index.
    - `set<Index>()` sets the value at a specific index, traversing the chain until it reaches the desired container.

4. **Initialization**: The `initialize()` function initializes the values recursively, accepting a list of values and assigning them to each container's value.

### Benefits

- **Type-safe**: Ensures that the correct types are stored and accessed.
- **Flexible**: Can store any number of types and retrieve them in a type-safe manner.
- **Recursive**: Uses recursion for type chaining, demonstrating advanced C++ template features.

### Requirements

This code should work on most modern C++ compilers (C++11 or later). For best compatibility, ensure you are using a C++14 or later compiler.

### License

This code is provided as-is under the MIT License.
