# 🌐 HTTP server

A lightweight, modern HTTP server built in **C++17** from scratch using raw **POSIX sockets** (IPv6-ready), with optional multithreading, logging, and support for static file serving.

---

## 🚀 Features

- ✅ Built with modern **OOP C++17**
- ✅ Fully **IPv6-compatible** (and IPv4 via dual-stack)
- 📁 Serves **static files** from a `/static` directory
- 🔍 Parses basic **HTTP GET** requests
- 🧠 Smart MIME type detection
- 🧱 Modular architecture (`net/`, `http/`, `server/`, `utils/`)
- 🧪 Minimal curl-style tests
- 📓 Optional logging support
- 🛠️ Ready for extensions: TLS/HTTPS, multithreading, middleware...

---

## 🏗️ Build Instructions

### 📦 Requirements

- C++17 compiler (e.g. `g++`, `clang++`)
- CMake ≥ 3.10
- POSIX-compatible OS (Linux, macOS, WSL, etc.)

### 🔧 Build Steps

```bash
git clone https://github.com/yourname/http-server.git
cd http-server
mkdir build && cd build
cmake ..
make
