# mulle-atinit

👼 Compatibility library to fix ELF initializer deficiencies

This is a workaround for dynamic libraries initiializers not being properly
sequenced (ELF).

This library must be **statically** linked. Then its constructor is
guaranteed to be called after all shared library initializations.

Any participating shared library constructor uses

```
mulle_atinit( f, userinfo, priority);
```

to defer `atinit` to a later date. The function `f` will be called properly
sequenced before main. `userinfo` will be passed as the only parameter.
Use priority 0 normally. Usse higher priorities to move initializers ahead
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
