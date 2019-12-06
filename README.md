# cstrm 0.1.0-dev0

*   A façade providing the functionality of `fgetc()` and `ungetc()` on top of a
    standard `FILE*` stream or character string.
*   Argument order for the ungetc() equivalent not the same as C89 ungetc().
*   Late Sep 2018: Not heavily tested at the moment.
*   `fmemopen()` would be ideal if it were standard, but it doesn't seem to be
    so using `cbuf()` in for now.
