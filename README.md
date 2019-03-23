## dynamic alpha 1.0

a dynamic language framework

---

### version content

alpha 1.0: The first version. Just add classes *Object*, *ObjectPointer*, template class *PrimitiveData* and function *integer*.

---

license: *LGPL-3.0*

*GitHub* address: https://github.com/lrcno6/dynamic

---

*dynamic* is a class library that provides a way to implement dynamic types in *C++*

It's used to implement dynamic types. You can do somethings that need dynamic types by it. But it isn't perfect, maybe you can contribute to *dynamic*.

it runs everywhere (in theory) because it doesn't use platform-related features (tested on *linux(g++)*)

---

### how to use it

*Dynamic* is a static library. To use *dynamic*, you should *make* it first:

```bash
make # turn on the debug information
# or
make release # turn on O3 optimization
```

and let a program to link it:

```bash
g++ user.cpp -o user -Ldynamic -ldynamic
```

---

Welcome to contribute to *dynamic*!

by *lrcno6*