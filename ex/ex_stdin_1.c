#include <stdlib.h>
#include <stdio.h>
#include "cstrm.h"

int
main(void)
{
   struct cstrm *in;
   int         c;

   in = cstrm_new();
   cstrm_open(in, NULL, 0);                      /* use stdin */

   while (EOF != (c = cstrm_getc(in)))
      printf("%c", c);

   cstrm_close(&in);

   return 0;
}
