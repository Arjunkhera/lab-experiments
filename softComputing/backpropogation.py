class BackPropagation():

    def __init__(self,networkFile,dataFile,outputClasses=1,epochs=5000,alpha=0.1):

        # no of output classes of the network
        self.outputClasses = outputClasses
        # number of epochs
        self.epochs = epochs
        # value of learning rate
        self.alpha = alpha
        # choose a random seed for reproducible results
        np.random.seed(1)

        # Call the input function to obtain the number of nodes of each layer
        self.networkExtract(networkFile)
        # Call the input function to obtain the input values
        self.dataExtract(dataFile)

        # number of hidden layers in the network
        self.noHiddenLayers = len(self.nodesPerLayer)
        # add the first and last layer node counts
        self.nodesPerLayer = [self.no_features] + self.nodesPerLayer + [self.outputClasses]
        # total number of layers in the network
        self.totalLayers = len(self.nodesPerLayer)

        # initialize the structure for the neural net
        self.initialize()

    def networkExtract(self,networkFile:str) -> None:

        # read the input from excel file
        excel_file = networkFile
        # convert it into a pandas dataframe
        dataframe = pd.read_excel(excel_file)
        # stores the number of nodes in every layer
        self.nodesPerLayer = dataframe.columns.tolist()


    def dataExtract(self,dataFile:str) -> None:

        # read the input from excel file
        excel_file = dataFile
        # convert it into a pandas dataframe
        dataframe = pd.read_excel(excel_file)
        # find out the number of features
        self.no_features = len(dataframe.columns) - 1
        # find out the number of inputs
        self.no_rows = len(dataframe.index)

        # Convert the dataframe into numpy array for analysis
        self.training_data = np.array([ dataframe.iloc[i,:self.no_features].tolist() for i in range(self.no_rows) ])
        # Obtain the output in a separate numpy column vector
        self.actual_op = np.array([dataframe['y'].tolist()]).T

    def initialize(self):

        self.weights = []
        # construct the weight matrices
        for i in range(self.totalLayers-1):
            # initialize weights randomly with mean 0 and range [-1, 1]
            self.weights.append(2*np.random.random((self.nodesPerLayer[i]+1,self.nodesPerLayer[i+1])) - 1)

    def run(self):
        for i in range(self.epochs):
            ll = self.singleCycle()
        return ll

    def singleCycle(self):

        # list of activations for all layers
        activations = []
        # list of errors for all layers
        errors = []
        # list of partial derivative matrices
        delta = []

        # Forward Propogation

        # initialize with training input
        inp = np.hstack((np.ones((self.training_data.shape[0], 1)), self.training_data))
        activations.append(inp)

        # Propogation for rest of the layers
        for i in range(self.totalLayers-2):
            newinp = np.hstack((np.ones((self.training_data.shape[0], 1)),self.sigmoid(np.dot(inp,self.weights[i]))))
            activations.append(newinp)
            inp = newinp
        # Do last layer separately to avoid adding bias term
        activations.append(self.sigmoid(np.dot(inp,self.weights[self.totalLayers-2])))

        # Backward Propogation
        err = activations[self.totalLayers-1] - self.actual_op
        errors.append(err)
        for i in range(self.totalLayers-2,0,-1):
            newerr = activations[i][:,1:] * (1 - activations[i][:,1:]) * np.dot(err,self.weights[i].T[:,1:])
            errors.append(newerr)
            err = newerr

        # Calculate the partial derivatives
        for i in range(self.totalLayers-1):
            delta.append(activations[0][:,:,np.newaxis] * errors[self.totalLayers-2-i][:,np.newaxis,:])

        # Take the average of the partial derivatives
        for i in range(self.totalLayers-1):
            delta[i] = np.average(delta[i],axis=0)

        # Update the weights
        for i in range(self.totalLayers-1):
            self.weights[i] += -self.alpha * delta[i]

        return activations[self.totalLayers-1]

    def forwardPropogate(self,activations:list,inparr:list):

        curinp = inparr
        for i in range(self.totalLayers-1):
                curinp = self.weights
                activations.append(np.dot(inparr))


    def sigmoid(self,x:float, derivative=False) -> float:

        if (derivative == True):
            return x * (1 - x)
        else:
            return 1 / (1 + np.exp(-x))
            
