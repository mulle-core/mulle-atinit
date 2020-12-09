# mulle-atinit

#### 🤱🏼 Compatibility library for deterministic initializers

This is a workaround for dynamic libraries initializers not being properly
sequenced (e.g. ELF bases shared library).

| Release Version
|-----------------------------------
| ![Mulle kybernetiK tag](https://img.shields.io/github/tag/mulle-c/mulle-atinit.svg?branch=release) [![Build Status](https://github.com/mulle-c/mulle-atinit/workflows/CI/badge.svg?branch=release)](https://github.com/mulle-c/mulle-atinit/actions)


You must **statically** link this library with your executable. Ensure that
global symbols are exported and that the whole library is linked to the
executable and not optimized away by the linker.


Any participating shared library constructor uses

```
mulle_atinit( f, userinfo, priority);
```

to defer `atinit` to a later date. The function `f` will be called properly
sequenced before main. `userinfo` will be passed as the only parameter.
Use priority 0 normally. Use higher priorities to move initializers ahead
or postpone with lower priorities.


## Add

Use [mulle-sde](//github.com/mulle-sde) to add mulle-atinit to your project:

```
mulle-sde dependency add --c \
                         --github mulle-core \
                         --marks no-dynamic-link,no-intermediate-link,no-singlephase,all-load \
                         mulle-atinit
```


## Install

### mulle-sde

Use [mulle-sde](//github.com/mulle-sde) to build and install mulle-atinit and all dependencies:

```
mulle-sde install --prefix /usr/local \
   https://github.com/mulle-core/mulle-atinit/archive/latest.tar.gz
```

### Manual Installation


Install the requirements:

Requirements                                               | Description
-----------------------------------------------------------|-----------------------
[mulle-thread](//github.com/mulle-concurrent/mulle-thread) | Threads and atomics
[mulle-dlfcn](//github.com/mulle-core/mulle-dlfcn)         | Cross-platform dlfcn


Install into `/usr/local`:

```
mkdir build 2> /dev/null
(
   cd build ;
   cmake -DCMAKE_INSTALL_PREFIX=/usr/local \
         -DCMAKE_PREFIX_PATH=/usr/local \
         -DCMAKE_BUILD_TYPE=Release .. ;
   make install
)
```

