import knapsack
import sys

if __name__ == '__main__':

    length = int(sys.argv[1])
    string = sys.argv[2]

    print(length)

    final = knapsack.knapsack(length)
    encryptedmsg,encryptedlist = final.encrypt(string)
    decryptedmsg = final.decrypt(encryptedlist)

    print("The encrypted message is : ",encryptedmsg)
    print(".......")
    print("The decrypted message is : ",decryptedmsg)
