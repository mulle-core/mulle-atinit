## 0.2.0



feature: add weak symbol support for static linking

* ``_mulle_atinit`` function now declared with ``MULLE_C_WEAK`` attribute
* improved static linking compatibility when `dlsym` is unavailable
