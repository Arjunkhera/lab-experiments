import math
import random
import time

# unofficial modules : store in same directory
import prime
import gcd

# generate the public and private keys
def generate_keys():

    # to obtain random seeds
    random.seed(time.time())

    # generate a random number
    startforp = random.randint(100,200)
    # get the generator function
    prime_handle = prime.get_primes(startforp)

    # get the first prime number
    p = prime_handle.send(None)

    # put a respectable gap between the two
    startforq = startforp + 100

    # get the second prime number
    q = prime_handle.send(startforq)

    # obtain n
    n = p*q

    # obtain the euler totient of p and q
    phi = (p-1)*(q-1)

    # choosing standard value of e
    e = 65537

    # Use Extended Euclid's Algorithm to generate the private key
    # d = multiplicative_inverse(e, phi)
    d = gcd.modinv(e,phi)

    # Return public and private keypair
    # Public key is (e, n) and private key is (d, n)
    return ((e, n), (d, n))

def encrypt(pk:tuple, plaintext:str) -> str:
    # Unpack the key into it's components
    key, n = pk
    # Convert each letter in the plaintext to numbers based on the character using a^b mod m
    cipher = [(ord(char) ** key) % n for char in plaintext]
    # Convert the list into string
    encrypted_msg = (''.join(map(lambda x: str(x),cipher)))

    # Return the encrypted message
    return [encrypted_msg,cipher]

def decrypt(pk:tuple, ciphertext:str) -> str:
    # Unpack the key into its components
    key, n = pk
    # Generate the plaintext based on the ciphertext and key using a^b mod m
    plain = [chr((char ** key) % n) for char in ciphertext]
    # Return the array of bytes as a string
    return ''.join(plain)
