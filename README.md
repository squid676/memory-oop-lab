# Memory & Systems Programming Lab

A small C++20 project that demonstrates four systems-programming topics in one runnable program. It uses only the C++ standard library and no third-party or garbage-collected runtime.

## Build and run

```sh
cmake -S . -B build
cmake --build build
./build/memory_oop_lab
```

The program writes `records.bin` in its working directory.

## What it demonstrates

- **Manual and dynamic memory:** a fixed-capacity bump `Arena` uses aligned raw storage and placement new; `Unique<T>` shows exclusive ownership, move semantics, and deterministic deletion. The arena example explicitly runs object destructors before releasing storage.
- **OOP:** `Shape` is an abstract base class. `Circle` and `Rectangle` override virtual methods, and calls through `Shape*` demonstrate runtime polymorphism.
- **Templates and algorithms:** generic insertion sort and binary search work directly on caller-owned arrays; recursive factorial shows recursion.
- **Streams and serialization:** `record_io.hpp` writes and reads a compact binary format with a four-byte signature, little-endian integers, variable-length names, and raw IEEE-754 doubles. The parser checks signatures, bounds, truncation, and stream failures.

## Learning notes

The arena is intentionally simple: it does not reclaim individual allocations and it is not thread-safe. Its caller owns object lifetimes. `Unique<T>` is an educational single-object owner; production code should generally prefer `std::unique_ptr`. The serialized double uses the host's `double` representation, so the format documents its assumptions rather than claiming universal portability.
