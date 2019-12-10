/**
 *  @file cstrm.c
 *  @version 0.2.0-dev0
 *  @date Sat Dec  7 13:37:44 CST 2019
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

const char *
cstrm_version(void)
{
   return "0.2.0-dev0";
}

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

void
cstrm_close(struct cstrm **pp)
{
   if ((*pp)->is_str)
      cbuf_free(&((*pp)->cp));

   else
      _IS_NULL((*pp)->fp) || fclose((*pp)->fp);

   _FREE(*pp);
   *pp = NULL;
}

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
