import rsa

if __name__ == '__main__':

    public, private = rsa.generate_keys()

    print ("Your public key is ", public ," and your private key is ", private)

    message = input("Enter a message to encrypt with your private key: ")
    encrypted_msg, cipher = rsa.encrypt(private, message)
    print ("Your encrypted message is: {}".format(encrypted_msg))

    print("---------------------")

    print ("Decrypting message with public key ", public ," . . .")
    print ("Your message is: ")
    print (rsa.decrypt(public, cipher))
