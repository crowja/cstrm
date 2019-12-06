# Dev notes for cstrm

*   Main thing is to create a façade providing the functionality of `fgetc()`
    and `ungetc()` on top of a standard `FILE*` stream or character string.
*   `fmemopen()` would be ideal if it were standard, but it doesn't seem to be
    so use `cbuf()` in for now.
