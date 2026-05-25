# mc-hooks

> **For educational purposes only.** This project is intended to demonstrate reverse engineering concepts such as signature scanning and inline function hooking on Windows DLLs.

## Dependencies

- [libhat](https://github.com/BasedInc/libhat) — pattern/signature scanning library
- [safetyhook](https://github.com/cursey/safetyhook) — x86/x64 inline hooking library

## Build

Requires CMake 3.15+ and a MSVC toolchain targeting Windows x64.

```sh
cmake -B build
cmake --build build
```
