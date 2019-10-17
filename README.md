# mulle-atinit

🤱🏼 Compatibility library for deterministic initializers

This is a workaround for dynamic libraries initializers not being properly
sequenced (e.g. ELF bases shared library).

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



## Build

This is a [mulle-sde](https://mulle-sde.github.io/) project.

It has it's own virtual environment, that will be automatically setup for you
once you enter it with:

```
mulle-sde mulle-atinit
```

Now you can let **mulle-sde** fetch the required dependencies and build the
project for you:

```
mulle-sde craft
```
