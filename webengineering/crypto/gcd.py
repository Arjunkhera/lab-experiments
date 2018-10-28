# Module to find GCD and Modular Inverse

# Euclids algorithm to find gcd
def gcd(a, b):
    while b != 0:
        a, b = b, a % b
    return a

# extended Euclidean algorithm for calculating modular inverse
def modinv(a, m):
    g, x, y = egcd(a, m)
    if g != 1:
        # this means a and m are not co prime and hence this algorithm cant work
        raise Exception('modular inverse does not exist')
    else:
        return x % m

# helper function for extended Euclidean
def egcd(a, b):
    if a == 0:
        return (b, 0, 1)
    else:
        g, x, y = egcd(b % a, a)
        return (g, y- (b // a) * x, x)
