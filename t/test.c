#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "cstrm.h"
#include "t/tinytest.h"

#ifdef  COLOR_CODE
#undef  COLOR_CODE
#endif
#define COLOR_CODE       0x1B

#ifdef  COLOR_RED
#undef  COLOR_RED
#endif
#define COLOR_RED        "[1;31m"

#ifdef  COLOR_GREEN
#undef  COLOR_GREEN
#endif
#define COLOR_GREEN      "[1;32m"

#ifdef  COLOR_YELLOW
#undef  COLOR_YELLOW
#endif
#define COLOR_YELLOW     "[1;33m"

#ifdef  COLOR_RESET
#undef  COLOR_RESET
#endif
#define COLOR_RESET      "[0m"

static void
printf_test_name(char *name, char *info)
{
   printf("%c%s%s%c%s", COLOR_CODE, COLOR_YELLOW, name, COLOR_CODE, COLOR_RESET);

   if (NULL != info)
      printf(" [%s]\n", info);
   else
      printf("\n");
}

static void
test_open_close(void)
{
   struct cstrm *z;

   printf_test_name("test_open_close", NULL);

   z = cstrm_new();
   ASSERT("OPEN-CLOSE TEST", z);
   cstrm_open(z, NULL, 0);
   cstrm_close(&z);
   ASSERT_EQUALS(NULL, z);
}

int
main(void)
{
   printf("%s\n", cstrm_version());

   RUN(test_open_close);

   return TEST_REPORT();
}
