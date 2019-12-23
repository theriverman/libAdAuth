# libAdAuth
Active Directory authentication library wrapper written in C++

# Building
The `libAdAuth` library is cross-platform (Linux + Windows) library with a single platform dependency. <br>
To build the library, a C/C++ compiler will be required on each build system.

## Dependencies
  * Linux: [libldap](http://www.openldap.org/software/man.cgi?query=ldap)
  * Windows: [winldap](https://docs.microsoft.com/en-us/windows/win32/api/winldap/)

## Linux
The recommended compiler is `g++` 5.4.0 or newer. <br>
To be able to link against `libldap`, it must be installed first.

To install `libldap` on Debian/Ubuntu, execute the following command: <br>
`sudo apt-get install libldap2-dev`

## Windows
The recommended compiler is `MSVC` 2017 or newer. <br>
To be able to link against `winldap`, it must be installed first.

To install `winldap`, the [Windows 10 SDK](https://developer.microsoft.com/en-us/windows/downloads/windows-10-sdk) must be installed.

# Implementation
The `libAdAuth` library is compiled to a [Shared Library](https://en.wikipedia.org/wiki/Library_(computing)#Shared_libraries) on all platforms. <br>
  * **Linux**: `libAdAuth.so`
  * **Windows**: `libAdAuth.dll`

The `libAdAuth` library exposes a single C function interface in **Release** build and an optional debug function called `foo` in **Debug** build mode.

```c
// Release Build
int auth(char *username, char *password, char *host, char *domain, int *port);

// Debug Build only [ with -DDEBUG ]
int foo(); // "Hello from foo()"
```

## Python
For a Python reference implementation for each platform, see the following files:
  * [reference_implementations/linux.py](reference_implementations/linux.py)
  * [reference_implementations/windows.py](reference_implementations/windows.py)

## Copyright
Copyright © 2019 - 2020 [github.com/theriverman](https://github.com/theriverman)
