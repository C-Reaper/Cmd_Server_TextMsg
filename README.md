## Overview
This project appears to be a simple client-server application built using C programming language. It uses basic networking functions and signal handling mechanisms. The server listens on port 5000 and accepts connections from clients. Upon connecting, the server and client both print connection/disconnection messages. When messages are received, they are printed with the sender's socket id.

## Features
- Basic TCP/IP networking using sockets.
- Signal handling mechanism for different types of events (connect, disconnect, message).
- Non-blocking I/O operations.
- Simple input from console to send messages or exit the application.

## Project Structure

### Prerequisites
- C/C++ Compiler and Debugger (GCC)
- Standard development tools
- Libraries needed in specific projects (None explicitly mentioned)

## Build & Run
### Linux:
To build for Linux, navigate to the project directory and run:
```bash
make -f Makefile.linux all
```

To execute the application after building:
```bash
make -f Makefile.linux exe
```

### Windows:
To build for Windows, navigate to the project directory and run:
```bash
make -f Makefile.windows all
```

To execute the application after building:
```bash
make -f Makefile.windows exe
```

### Wine (Windows on Linux):
To build for Windows using Wine, navigate to the project directory and run:
```bash
make -f Makefile.wine all
```

To execute the application after building:
```bash
make -f Makefile.wine exe
```

### WebAssembly (for browsers):
To build for webassembly, navigate to the project directory and run:
```bash
make -f Makefile.web all
```
Then you can use a tool like `wasmtime` or include it in an HTML file to execute the application.

**Note:** The code provided does not include actual implementation of functions like `Client_Make`, `Server_Make`, etc., which are expected to be defined in header files included at the top of the source files. These should match with the headers mentioned and are assumed to provide necessary functionalities for networking, signal handling, and client-server communication.