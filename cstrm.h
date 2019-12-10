/**
 *  @file cstrm.h
 *  @version 0.1.1-dev0
 *  @date Sat Dec  7 13:37:44 CST 2019
 *  @copyright %COPYRIGHT%
 *  @brief FIXME
 *  @details FIXME
 */

#ifndef _CSTRM_H_
#define _CSTRM_H_

#ifdef  _PACKAGE_NAME
#undef  _PACKAGE_NAME
#endif
#define _PACKAGE_NAME "cstrm"

struct cstrm;

/**
 *  @brief Constructor.
 *  @details Create and return a new cstrm object.
 *  @details FIXME longer description here ...
 */
struct cstrm *cstrm_new(void);

/**
 *  @brief Return the version of this package.
 *  @details FIXME longer description here ...
 */
const char *cstrm_version(void);

/**
 *  @brief Initialize a cstrm object.
 *  @details FIXME longer description here ...
 *  @param p Pointer to a cstrm object
 *  @param x FIXME
 */
int         cstrm_open(struct cstrm *p, void *x, int is_str);

/**
 *  @brief Clean up and free a cstrm structure.
 *  @details FIXME longer description here ...
 */
void        cstrm_close(struct cstrm **pp);

/**
 *  @brief Initialize a cstrm object.
 *  @details FIXME longer description here ...
 *  @param p Pointer to a cstrm object
 *  @param x FIXME
 */
int         cstrm_getc(struct cstrm *p);

/**
 *  @brief Initialize a cstrm object.
 *  @details FIXME longer description here ...
 *  @param p Pointer to a cstrm object
 *  @param x FIXME
 */
int         cstrm_ungetc(struct cstrm *p, const int c);

#endif
