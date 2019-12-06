/**
 *  @file cstrm.c
 *  @version 0.1.0-dev0
 *  @date Thu Nov  1 08:33:12 CDT 2018
 *  @copyright %COPYRIGHT%
 *  @brief FIXME
 *  @details FIXME
 */

#include <stdlib.h>
#include <stdio.h>                               /* FIXME */
#include <string.h>                              /* FIXME */
#include "cstrm.h"
#include "cbuf.h"

#ifdef  _IS_NULL
#undef  _IS_NULL
#endif
#define _IS_NULL(p)   ((NULL == (p)) ? (1) : (0))

#ifdef  _FREE
#undef  _FREE
#endif
#define _FREE(p)      ((NULL == (p)) ? (0) : (free((p)), (p) = NULL))

struct cstrm {
   int         is_str;
   struct cbuf *cp;
   FILE       *fp;
};


/*** cstrm_new() ***/

struct cstrm *
cstrm_new(void)
{
   struct cstrm *tp;

   tp = (struct cstrm *) malloc(sizeof(struct cstrm));
   if (_IS_NULL(tp))
      return NULL;

   tp->is_str = 0;
   tp->cp = NULL;
   tp->fp = NULL;

   return tp;
}


/*** cstrm_version() ***/

const char *
cstrm_version(void)
{
   return "0.1.0-dev0"; 
}


/*** cstrm_open() ***/

int
cstrm_open(struct cstrm *p, void *x, int is_str)
{
   /* NOTE use return val 0 for success */

   if (is_str) {                                 /* reading from a string */
      p->is_str = 1;
      if (_IS_NULL(x)) {                         /* "string" is actually a NULL pt */
         p->cp = cbuf_new();
         cbuf_init(p->cp, (char *) x);
      }

      else {                                     /* usual case */
         p->cp = cbuf_new();
         cbuf_init(p->cp, (char *) x);
      }

      return 0;
   }

   else {
      p->is_str = 0;
      if (_IS_NULL(x)) {                         /* use stdin */
         p->fp = stdin;
         return _IS_NULL(p->fp) ? 1 : 0;
      }

      else {                                     /* regular file */
         p->fp = fopen((const char *) x, "rb");

         return _IS_NULL(p->fp) ? 1 : 0;
      }
   }
}


/*** cstrm_close() ***/

void
cstrm_close(struct cstrm *p)
{
   if (p->is_str)
      cbuf_free(p->cp);

   else
      _IS_NULL(p->fp) || fclose(p->fp);

   _FREE(p);
}


/*** cstrm_getc() ***/

int
cstrm_getc(struct cstrm *p)
{
   int         c;

   if (p->is_str)
      c = cbuf_get(p->cp);

   else
      c = fgetc(p->fp);

   return c;
}


/*** cstrm_ungetc() ***/

int
cstrm_ungetc(struct cstrm *p, const int c)
{
   if (p->is_str)
      return cbuf_unget(p->cp, c);

   else
      return ungetc(c, p->fp);
}


#undef _IS_NULL
#undef _FREE
