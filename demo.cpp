#include "ExponentialSearch.h"
#include <iostream>

/** Some helpers to show usage */
namespace usage {
/**
 * Base creator type to help create our type.
 */
template <size_t MaximumBytes, typename T, typename U, size_t ExtraConstant = 5>
struct BaseCreator {
private:
  /// The type we want to maximize N for.
  template <size_t N>
  using type_lambda =
      std::pair<std::array<T, N>, std::array<U, N + ExtraConstant>>;

  /// template lambda giving out size of above
  template <size_t N> struct size_lambda {
    static constexpr auto value = sizeof(type_lambda<N>);
  };

  static_assert(expsearch::IsSuitableLambda<size_lambda>,
                "Unsuitable size template lambda function!");

public:
  /// This returns the maximized N
  static constexpr auto get_maximized_N =
      expsearch::exponentialSearch<size_lambda, MaximumBytes>();

  /// This returns the resulting type
  using get_type = type_lambda<get_maximized_N>;
};
} // namespace usage

int main() {
  static constexpr auto MaxBytes = 4096;
  using Creator = usage::BaseCreator<MaxBytes, char, long>;
  constexpr auto N = Creator::get_maximized_N;
  using DoubleArrayStore = Creator::get_type;

  std::cout << "MaxBytes = " << MaxBytes << "\n"
            << "sizeof(DoubleArrayStore) = " << sizeof(DoubleArrayStore) << "\n"
            << "sizeof(DoubleArrayStore::first) = "
            << sizeof(DoubleArrayStore::first) << "\n"
            << "sizeof(DoubleArrayStore::second) = "
            << sizeof(DoubleArrayStore::second) << "\n"
            << "alignof(DoubleArrayStore) = " << alignof(DoubleArrayStore)
            << "\n"
            << "alignof(DoubleArrayStore::first) = "
            << alignof(DoubleArrayStore::first) << "\n"
            << "alignof(DoubleArrayStore::second) = "
            << alignof(DoubleArrayStore::second) << "\n"
            << "offsetof(DoubleArrayStore::first) = "
            << offsetof(DoubleArrayStore, first) << "\n"
            << "offsetof(DoubleArrayStore::second) = "
            << offsetof(DoubleArrayStore, second) << "\n"
            << "N = " << N << "\n"
            << std::endl;

  return 0;
}
