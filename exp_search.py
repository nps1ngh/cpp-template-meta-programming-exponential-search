"""
Here's the same algorithm but in python.
(Useful for quick testing etc.)

"""
from typing import Callable


def exponential_search(f: Callable[[int], int], max_value: int, x: int = 1):
    # see https://en.wikipedia.org/wiki/Exponential_search
    value = f(x)
    if value < max_value:
        return find(f, max_value, x * 2)
    elif value == max_value:
        return x
    else:
        x = binary_search(f, max_value, upper=x, lower=x // 2)
        if calc(x) > max_value:
            x -= 1
        return x


def binary_search(f: Callable[[int], int], max_value: int, upper: int, lower: int):
    if upper < lower:
        return upper

    mid = (upper + lower) // 2
    value = f(mid)

    if value < max_value:
        return binary_search(f, max_value, upper=upper, lower=mid + 1)
    elif value > max_value:
        return binary_search(f, max_value, upper=mid - 1, lower=lower)
    else:
        return mid
