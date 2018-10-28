import math

# check whether the number is prime or not
def is_prime(number:int) -> int:
    if number > 1:
        if number == 2:
            return True
        if number % 2 == 0:
            return False
        for current in range(3, int(math.sqrt(number) + 1), 2):
            if number % current == 0:
                return False
        return True
    return False

# get a prime number just greater than a given number
def get_primes(number:int) -> int:
    while True:
        if is_prime(number):
            number = yield number
        number += 1
