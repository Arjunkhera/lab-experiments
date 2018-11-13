from backpropagation import BackPropagation

if __name__ == '__main__':

    # For XOR
    print("Training on XOR")
    # provide the path to neural network structure and input file
    backprop = BackPropagation("./inputs/structure.xlsx","./inputs/binary-xor.xlsx")
    backprop.epochs = 2000
    backprop.alpha = 0.5

    # to train the model
    print(backprop.train())
    # output the accuracy on training data
    print("accuracy : {}%".format(backprop.accuracy()))
    # output the activation values
    print(backprop.activations[backprop.totalLayers-1])
    print("End of Training")

    # For XNOR
    print("Training on XNOR")
    # provide the path to neural network structure and input file
    backprop = BackPropagation("./inputs/structure.xlsx","./inputs/binary-xnor.xlsx")
    backprop.epochs = 2000
    backprop.alpha = 0.5

    # to train the model
    print(backprop.train())
    # output the accuracy on training data
    print("accuracy : {}%".format(backprop.accuracy()))
    # output the activation values
    print(backprop.activations[backprop.totalLayers-1])
    print("End of Training")
