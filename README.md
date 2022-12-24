# RPC ADD

This is a simple creation of a Remote Procedure Call using the RPCGen tool. I will outline the process of its creation then show how to use it.

## RPCGen

RPCGen is a compiler created by Sun Microsystems in the 1980s. It is a tool that generates code for remote procedure calls (RPCs) based on specifications provided in a .x file. RPCs allow a program running on one computer to request services from a program running on another computer, and RPCGen generates the necessary code to make this communication possible.

## Development process

1. Create the IDL.
   - IDL stands for Interface Definition Language. It resides in a .x file and contains C-like declarations of the main structure used in the program and the program versions. In this project, the IDL can be found in `add.x`
   - After this, compile the file to generate some more files that will have code based on what we described in the first file. Run this command:
     `rpcgen -C add.x`
   - A couple files are generated as shown: \
     1. `add.h` - Header file. Defines the structure defined in the .x file
     2. `add_svc.c` - Server program. Implements the main procedure that registers the service
     3. `add_clnt.c` - Contains the client stub function that implements the add_1 function
     4. `add_xdr.c` - Uses eXternal Data Representation libraries to convert the integers being parsed into standard form
2. Generate sample client and server code.
   - Run `rpcgen -a -C add.x` to generate the sample client and server code. This will generate the following files:
     1. `add_client.c` - Sample client code
     2. `add_server.c` - Sample server code
     3. `makefile.add` - Makefile for the project
   - Compile the code using the makefile. Run `make -f makefile.add` to generate the executables `add_client` and `add_server`
3. Test the client and the server to ensure that they can communicate
   - In the server's main function, replace the comments `insert server code here` with a simple print function to show that the server is running and listening for requests.
   - Recompile the code using the makefile. Run `make -f makefile.add`
4. Get the server to do some actual work

   - In the server's main function, replace the comments `insert server code here` with the actual code to add the two numbers. The code should look like this:

   ```c
   int *add_1_svc(addition *add, struct svc_req *rqstp) {
       static int result;
       result = add->a + add->b;
       return &result;
   }
   ```

   - Recompile the code using the makefile. Run `make -f makefile.add`

5. Make the client functional with regard to the main goal

   - In the client's main function, replace the comments `insert client code here` with the actual code to add the two numbers. The code should look like this:

   ```c
   int main(int argc, char *argv[]) {
       CLIENT *clnt;
       addition add;
       int *result_1;
       char *server;

       if (argc != 3) {
           printf("usage: %s server_host\n", argv[0]);
           exit(1);
       }
       server = argv[1];

       clnt = clnt_create(server, ADD_PROG, ADD_VERS, "udp");
       if (clnt == NULL) {
           clnt_pcreateerror(server);
           exit(1);
       }

       add.a = atoi(argv[2]);
       add.b = atoi(argv[3]);

       result_1 = add_1(&add, clnt);
       if (result_1 == (int *) NULL) {
           clnt_perror(clnt, "call failed");
       }
       printf("result = %d\n", *result_1);

       clnt_destroy(clnt);
       exit(0);
   }
   ```

   - Recompile the code using the makefile. Run `make -f makefile.add`

6. Cleanup the code.
