#pragma once

#include <array>
#include <cstddef>

namespace expsearch {
/**
 * This makes sure that the lambda is suitable for the search.
 * @tparam Calc The lambda to check.
 */
template <template <size_t> typename Calc>
concept IsSuitableLambda = requires {
                             { Calc<0>::value } -> std::convertible_to<size_t>;
                           };

/**
 * Binary search needed for exponential search.
 * @tparam Calc The lambda to use.
 * @tparam Max  The maximum size to reach.
 * @tparam Upper The upper bound for N.
 * @tparam Lower The lower bound for N.
 * @return N such that Calc(N) <= Max < Calc(N+1)
 */
template <template <size_t> typename Calc, size_t Max, size_t Upper,
          size_t Lower>
  requires IsSuitableLambda<Calc>
constexpr size_t binarySearch() {
  if constexpr (Upper < Lower) {
    return Upper;
  }

  constexpr size_t Mid = (Upper + Lower) / 2;
  constexpr size_t Size = Calc<Mid>::value;
  if constexpr (Size < Max) {
    return binarySearch<Calc, Max, Upper, Mid + 1>();
  } else if constexpr (Size > Max) {
    return binarySearch<Calc, Max, Mid - 1, Lower>();
  } else {
    return Mid;
  }
}

/**
 * This is the exponential search algorithm.
 * See the python version, it's a pretty simple algorithm.
 * Also see https://en.wikipedia.org/wiki/Exponential_search
 * The terminology is a little different, as this one is used
 * optimizing some size.
 *
 * @tparam Calc The lambda to use.
 * @tparam Max  The maximum size to reach.
 * @tparam N    The current N.
 * @return N such that Calc(N) <= Max < Calc(N+1)
 */
template <template <size_t> typename Calc, size_t Max, size_t N = 1,
          size_t... Debug>
  requires IsSuitableLambda<Calc>
constexpr size_t exponentialSearch() {
  constexpr size_t Size = Calc<N>::value;
  if constexpr (Size < Max) {
    return exponentialSearch<Calc, Max, N * 2>();
  } else if constexpr (Size > Max) {
    return binarySearch<Calc, Max, N, N / 2>();
  } else {
    return N;
  }
}
} // namespace expsearch
