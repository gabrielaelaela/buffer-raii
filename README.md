# Buffer

## Task

In C++ programs, it is sometimes necessary to interact with libraries written in C and with operating system system calls, whose wrappers are also almost always written in C. APIs in the C language often work with untyped memory buffers (a pair consisting of a `void *` pointer to the buffer and a `size_t` buffer size). Your task in this assignment is to write an RAII wrapper around such a buffer.

In the interfaces, you must place `const`, `explicit`, or `noexcept` where appropriate. Apart from that, the interfaces must not be changed.
