#include <stdlib.h>
#include <stdio.h>
#include "cstrm.h"

/* Read stdin, replace 'a' with 'A' */

int
main(void)
{
   struct cstrm *in;
   int         c;

   in = cstrm_new();
   cstrm_open(in, NULL, 0);                      /* use stdin */

   while (EOF != (c = cstrm_getc(in))) {
      if ('a' == c)
         cstrm_ungetc(in, 'A');
      else
         printf("%c", c);
   }

   cstrm_close(&in);

   return 0;
}
