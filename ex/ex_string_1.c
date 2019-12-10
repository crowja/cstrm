#include <stdlib.h>
#include <stdio.h>
#include "cstrm.h"

char        str[] =
 "Enter Ghost.\n"
 "BARNARDO. In the same figure, like the King that’s dead.\n"
 "MARCELLUS. Thou art a scholar; speak to it, Horatio.\n"
 "BARNARDO. Looks it not like the King? Mark it, Horatio.\n"
 "HORATIO. Most like. It harrows me with fear and wonder.\n"
 "BARNARDO It would be spoke to.\n"
 "MARCELLUS. Question it, Horatio.\n"
 "HORATIO. What art thou that usurp’st this time of night, Together with\n"
 "that fair and warlike form In which the majesty of buried Denmark Did\n"
 "sometimes march? By heaven I charge thee speak.\n"
 "MARCELLUS. It is offended.\n" "BARNARDO. See, it stalks away.\n";

int
main(void)
{
   struct cstrm *in;
   int         c;

   in = cstrm_new();

   if (cstrm_open(in, str, 1)) {
      printf("BARF\n");
      exit(1);
   }

   while (EOF != (c = cstrm_getc(in)))
      printf("%c", c);

   cstrm_close(&in);

   return 0;
}
