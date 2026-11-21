# better
**better** - make your code better.

## Description
This is a small library that defines short types (**i32**, **u8**, **any**),
functions (**input()**, **trim_string()**) and macro (**cast()**, **nothing**)
to make code readable.

### Features
- **C89**/**C90** code standard.
- **Platform safety**: compiler will got error if *char* isn't 8 bits or
  cannot define **i16**/**u16**.
- **stb-style**: without hell of dependencies.

### Build
Needed:
- C Compiler
- CMake 3.10 and greater
- GNU Make

```bash
cmake -B build
cd build/
make
```

### Authors
TheCRatTime

### License
Project is under Apache 2.0 license
