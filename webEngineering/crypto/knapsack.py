import random
import math
import time
import binascii

# unofficial modules : store in same directory
import prime
import gcd

class knapsack:

    def __init__(self,n:int):

        self.n = n
        self.private_key = self.generatePrivateKey()
        self.public_key = self.generatePublicKey()

    def generatePrivateKey(self) -> list:

        # to obtain random seeds
        random.seed(time.time())

        # generate the first number of the series
        self.sum = random.randint(100,500)

        # private key
        key = [self.sum]

        # generate the remaining values for private key
        for i in range(self.n-1):
            nextnum = random.randint(self.sum+1,self.sum+100)
            self.sum += nextnum
            key.append(nextnum)

        # store the modulo required for public key generation
        self.modulo = random.randint(self.sum+130,self.sum+150)

        # get the generator function
        prime_handle = prime.get_primes(self.sum+100)

        # get the first prime number : to ensure multiplier and modulo are co prime
        self.multiplier = prime_handle.send(None)

        # get the inverse of multiplier
        self.inverse = gcd.modinv(self.multiplier,self.modulo)

        self.private_key = key
        # return the private key
        return self.private_key

    def generatePublicKey(self) -> list:
        self.public_key = [ (x*self.multiplier)%self.modulo for x in self.private_key ]
        return self.public_key

    def string2bits(self,s=''):
        return [bin(ord(x))[2:].zfill(8) for x in s]

    def bits2string(self,b=None):
        return ''.join([chr(int(x, 2)) for x in b])

    def padding(self,extraspace:int) -> str:
        self.padtext = "0"*extraspace

    def convertToBinary(self) -> str:

        # convert string to binary
        self.binary = ''.join(self.string2bits(self.text))

        # to check if padding is needed or not
        length = len(self.binary)

        # add padding if needed to make proper multiple
        self.padtext = ""
        if(length%self.n != 0):
            extraspace = self.n - length%self.n
            self.padding(extraspace)
            self.binary = self.binary + self.padtext

    def encrypt(self,text:str) -> str:

        # store the plaintext
        self.text = text
        # convert the text to binary
        self.convertToBinary()

        self.encryptedlist = []
        traversals = int(len(self.binary)/self.n)

        # encode the string
        j = 0
        for i in range(traversals):
            temp = 0
            for val in self.public_key:
                if(self.binary[j] == '1'):
                    temp += val
                j += 1
            self.encryptedlist.append(temp)

        # convert the list to string
        self.encrypted_message = ''.join(map(lambda x: str(x),self.encryptedlist))
        return self.encrypted_message,self.encryptedlist

    def helper(self,num):
        # find out the binary value for given set using private key
        decryptbin = ""
        for val in reversed(self.private_key):
            if num >= val:
                num -= val
                decryptbin += "1"
            else:
                decryptbin += "0"
        return decryptbin[::-1]

    def decrypt(self,encryptlist:list) -> str:

        # decrypt the list
        self.decryptedlist = [ (x*self.inverse)%self.modulo for x in encryptlist ]

        self.decryptedbinary = ""
        for val in self.decryptedlist:
            self.decryptedbinary += self.helper(val)

        # remove the extra padded space
        length = len(self.decryptedbinary) - len(self.padtext)
        self.decryptedbinary = self.decryptedbinary[:length]

        # convert binary to string
        iterations = int(len(self.decryptedbinary)/8)

        # convert binary string to list to be sent to function
        decryption_list = []
        self.decrypted_message = ""
        string = self.decryptedbinary
        for i in range(iterations):
            decryption_list.append(string[:8])
            string = string[8:]

        # retreive the original decoded message
        self.decrypted_message = self.bits2string(decryption_list)

        # return the decrypted string
        return self.decrypted_message
