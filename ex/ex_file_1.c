#include <stdlib.h>
#include <stdio.h>
#include "cstrm.h"

int
main(int argc, char *argv[])
{
   struct cstrm *in;
   int         c;

   in = cstrm_new();

   if (argc > 1)                                 /* use input file */
      if (cstrm_open(in, argv[1], 0))
         exit(1);

   while (EOF != (c = cstrm_getc(in)))
      printf("%c", c);

   cstrm_close(in);

   return 0;
}
