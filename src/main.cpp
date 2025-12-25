#include <Tuple.hpp>
#include <string>

int main(int argc, char *argv[]) {

  // Tuple Container
  TupleContainer<0, int, double> member;

  // Current Value
  auto value_int = member.value;

  // Next Value
  auto value_double = member.next.value;

  Tuple<int, std::string> tuple{1, "Hello Tuple"};
  auto value = tuple.get<0>();
  return 0;
}