# C++ Multithreaded Chat Server

A simple **high-performance TCP chat server** built in **C++17**.  

## ✨ Features

- Multithreaded server that handles multiple clients concurrently
- Thread-safe client communication with `std::mutex`
- Uses **Winsock2 (Windows)** or **Berkeley Sockets (Linux)**
- Broadcasting messages from one client to all connected clients
- Unit tests with **GoogleTest**
- Static code analysis using `clang-tidy`
- Cross-platform (tested on Windows with MSYS2 and Linux)

## Project Structure

```
cpp-chat-server/
│── server_win.cpp        # Windows server implementation
│── client_win.cpp        # Windows client implementation
│── server_linux.cpp      # Linux server implementation
│── client_linux.cpp      # Linux client implementation
│── tests/
│   ├── test_broadcast.cpp  # GoogleTest unit test for
│   └── CMakeLists.txt
│── CMakeLists.txt        # Root CMake build file
│── README.md

```

## Demo

[![Chat Server Demo](demo-thumbnail.png)](https://github.com/user-attachments/assets/319fa3b5-25a7-4c92-9982-cc5662403f29)




### 🔹 Build (Windows / MSYS2 UCRT64)

```bash
g++ server_win.cpp -o server.exe -lws2_32 -std=c++17 -pthread
g++ client_win.cpp -o client.exe -lws2_32 -std=c++17 -pthread
```

### 🔹 Build (Linux)

```bash
g++ server_linux.cpp -o server -std=c++17 -pthread
g++ client_linux.cpp -o client -std=c++17 -pthread
```

### 🔹 Run Server

```bash
./server.exe   # Windows
./server       # Linux
```

### 🔹 Run Client

```bash
./client.exe   # Windows
./client       # Linux
```

### 🧪 Testing

```bash
cd tests
cmake .
make
./runTests
```

## 📖 Skills Demonstrated

- **C++17 development & testing**
- **Multithreading & synchronization**
- **Network programming (sockets)**
- **Cross-platform system programming**
- **Good software practices**: testing, static analysis, CI/CD

---

## 📌 Future Improvements

- Add authentication & private messaging
- Support for chat rooms
- GUI client using Qt
- TLS encryption for secure communication


