

struct numbers{
    int a;
    int b;
};

program ADD_PROG{

    version ADD_VERS{
        int add(numbers)=1;
    }=1;

}=0x23451111;

// to generate the rpc files
// rpcgen -a -C add.x
// make -f Makefile.add

// to run the server
// sudo ./add_server

// to run the client
// sudo ./add_client localhost
