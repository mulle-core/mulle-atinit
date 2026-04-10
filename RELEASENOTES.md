## 0.3.0








feature: add debug tracing and enforce static linking for mulle-atinit

* optional runtime tracing `(MULLE_ATINIT_DEBUG)` with detailed stderr logs for constructor, init, locking/unlocking, callback running and return paths
* refuse to be built as a shared library (compile-time error when `MULLE_INCLUDE_DYNAMIC)` to avoid incorrect dynamic-linker behavior
* improved Windows diagnostics and support (DllMain guard, export/trace pragmas) and clearer constructor naming `(mulle_atinit_load)`
* rework one-time init / symbol-export path for more robust initialization across translation units
