## Adelsbach Enhanced Threading Library

This library implements the C11 threading API using the commonly available POSIX pthreads 
for Linux, BSD and UNIX systems.
It is intended for systems where the standard C library does not implement this 
threading API.

In addition to the standard functions extensions are provided for further features
such as barriers, read/write mutexes and spinlocks.

### Compile using meson
Using meson, setup a build directory using
```
meson setup build
```

The you can build and install the library, as well as the manual pages:
```
cd build
ninja
ninja install
```

### Documentation
* [Documentation](https://techpubs.adelsbach-research.eu/d/dd-00013-001/html/threads_intro.html)

### License
Copyright 2024, Adelsbach UG (haftungsbeschraenkt)
Copyright 2014-2024, Jan Adelsbach jan@jadelsbach.de

MIT-License, see [LICENSE](LICENSE) file.
