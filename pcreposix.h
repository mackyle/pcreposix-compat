/*************************************************
*       Perl-Compatible Regular Expressions      *
*************************************************/

#ifndef _PCREPOSIX_H
#define _PCREPOSIX_H

/* This is the header for the POSIX wrapper interface to the PCRE Perl-
Compatible Regular Expression library. It defines the things POSIX says should
be there. I hope.

            Copyright (c) 1997-2012 University of Cambridge
            Copyright (c) 2017 Kyle J. McKay <mackyle@gmail.com>
            All Rights Reserved

-----------------------------------------------------------------------------
Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met:

    * Redistributions of source code must retain the above copyright notice,
      this list of conditions and the following disclaimer.

    * Redistributions in binary form must reproduce the above copyright
      notice, this list of conditions and the following disclaimer in the
      documentation and/or other materials provided with the distribution.

    * Neither the name of the University of Cambridge nor the names of its
      contributors may be used to endorse or promote products derived from
      this software without specific prior written permission.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
POSSIBILITY OF SUCH DAMAGE.
-----------------------------------------------------------------------------
*/

/* Have to include stdlib.h in order to ensure that size_t is defined. */

#include <stdlib.h>

/* Allow for C++ users */

#ifdef __cplusplus
extern "C" {
#endif

/* Options, mostly defined by POSIX, but with some extras. */

#define REG_ICASE     0x0001   /* Maps to PCRE_CASELESS */
#define REG_NEWLINE   0x0002   /* Affects four different PCRE options */
#define REG_NOTBOL    0x0004   /* Maps to PCRE_NOTBOL */
#define REG_NOTEOL    0x0008   /* Maps to PCRE_NOTEOL */
#define REG_DOTALL    0x0010   /* NOT defined by POSIX; maps to PCRE_DOTALL */
#define REG_NOSUB     0x0020   /* Maps to PCRE_NO_AUTO_CAPTURE */
#define REG_UTF8      0x0040   /* NOT defined by POSIX; maps to PCRE_UTF8 */
/* These next two overlap since there's no conflict */
#define REG_PEND      0x0080   /* BSD feature: pattern ends at re_endp addr */
#define REG_STARTEND  0x0080   /* BSD feature: pass subject string by so,eo */
#define REG_NOTEMPTY  0x0100   /* NOT defined by POSIX; maps to PCRE_NOTEMPTY */
#define REG_UNGREEDY  0x0200   /* NOT defined by POSIX; maps to PCRE_UNGREEDY */
#define REG_UCP       0x0400   /* NOT defined by POSIX; maps to PCRE_UCP */
#define REG_MULTILINE 0x0800   /* NOT defined by POSIX; maps to PCRE_MULTILINE */
#define REG_NOSPEC    0x2000   /* BSD feature: treat pattern as literal string */
#define REG_EXPANDED  0x4000   /* NOT defined by POSIX; maps to PCRE_EXTENDED */

#define REG_BASIC     0        /* BSD define */
#define REG_EXTENDED  0x1000   /* Maps to !PCRE_POSIX_BASIC_ESC */

/* REG_PCRE and friends */

/* When REG_PCRE is set in the cflags (3rd) argument to the regcomp function
then the following behavior occurs:

(The notation "!REG_EXTENDED" below means the "REG_EXTENDED" flag was NOT
 included in the cflags argument and similarly for other "!REG_..." notation.)

  a) Setting REG_PCRE implies REG_EXTENDED which means that
     PCRE_POSIC_BASIC_ESC will no longer be set for !REG_EXTENDED.
     Do not try and use Basic Regular Expressions (BREs) with REG_PCRE!

  b) Setting REG_PCRE makes REG_NEWLINE strictly an alias for REG_MULTILINE.
     In other words all of the extra "macro" logic to activate the various
     "POSIX" semantics PCRE options for !REG_NEWLINE and REG_NEWLINE is
     disabled.  This means that !REG_NEWLINE will no longer force both
     PCRE_DOTALL and PCRE_DOLLAR_ENDONLY and REG_NEWLINE will only set
     PCRE_MULTILINE but will no longer force PCRE_NOT_EXCLUDES_NL.
*/

#define REG_PCRE          ((int) 0x8000)   /* cast needed with 16-bit ints */

/* The following table may be helpful when using REG_PCRE:

  PCRE & Perl  Option to use for regcomp  POSIX   REG_PCRE/!REG_PCRE Defaults
  -----------  -------------------------  ------  -----------------------------
  (?i) or /i   REG_ICASE                  Yes     Off/Off
  (?s) or /s   REG_DOTALL                 No      Off/On unless REG_NEWLINE set
  (?m) or /m   REG_MULTILINE/REG_NEWLINE  No/Yes  Off/Off (REG_NEWLINE => more)
  (?x) or /x   REG_EXPANDED               No      Off/Off

In !REG_PCRE (aka POSIX) mode, !REG_NEWLINE sets both PCRE_DOTALL and
PCRE_DOLLAR_ENDONLY whereas REG_NEWLINE sets both PCRE_MULTILINE and
PCRE_NOT_EXCLUDES_NL.  In REG_PCRE (aka PCRE) mode, REG_NEWLINE is strictly
an alias for REG_MULTILINE (all magic macro logic is disabled). */

/* The friends of REG_PCRE (only available when int is wider than 16 bits) */

/* Note that a cast to int is NOT included so that if any of these are used on
a 16-bit int platform, the compiler should catch it since the POSIX
specification for the regcomp function has the cflags parameter as an int
but on such a platform these constants will end up having type long instead. */

#define REG_DOLLARENDONLY 0x00010000       /* Maps to PCRE_DOLLAR_ENDONLY */
#define REG_ANCHORED      0x00020000       /* Maps to PCRE_ANCHORED */

/* Error values. Not all these are relevant or used by the wrapper. */

enum {
  REG_ASSERT = 1,  /* internal error ? */
  REG_BADBR,       /* invalid repeat counts in {} */
  REG_BADPAT,      /* pattern error */
  REG_BADRPT,      /* ? * + invalid */
  REG_EBRACE,      /* unbalanced {} */
  REG_EBRACK,      /* unbalanced [] */
  REG_ECOLLATE,    /* collation error - not relevant */
  REG_ECTYPE,      /* bad class */
  REG_EESCAPE,     /* bad escape sequence */
  REG_EMPTY,       /* empty expression */
  REG_EPAREN,      /* unbalanced () */
  REG_ERANGE,      /* bad range inside [] */
  REG_ESIZE,       /* expression too big */
  REG_ESPACE,      /* failed to get memory */
  REG_ESUBREG,     /* bad back reference */
  REG_INVARG,      /* bad argument */
  REG_NOMATCH      /* match failed */
};


/* The structure representing a compiled regular expression. */

typedef struct {
  void *re_pcre;
  size_t re_nsub;
  size_t re_erroffset;
  const char *re_endp; /* REG_PEND only */
} regex_t;

/* The structure in which a captured offset is returned. */

typedef int regoff_t;

typedef struct {
  regoff_t rm_so;
  regoff_t rm_eo;
} regmatch_t;

/* When an application links to a PCRE DLL in Windows, the symbols that are
imported have to be identified as such. When building PCRE, the appropriate
export settings are needed, and are set in pcreposix.c before including this
file. */

#if defined(_WIN32) && !defined(PCRE_STATIC) && !defined(PCREPOSIX_EXP_DECL)
#  define PCREPOSIX_EXP_DECL  extern __declspec(dllimport)
#  define PCREPOSIX_EXP_DEFN  __declspec(dllimport)
#endif

/* By default, we use the standard "extern" declarations. */

#ifndef PCREPOSIX_EXP_DECL
#  ifdef __cplusplus
#    define PCREPOSIX_EXP_DECL  extern "C"
#    define PCREPOSIX_EXP_DEFN  extern "C"
#  else
#    define PCREPOSIX_EXP_DECL  extern
#    define PCREPOSIX_EXP_DEFN  extern
#  endif
#endif

/* The functions */

PCREPOSIX_EXP_DECL int regcomp(regex_t *, const char *, int);
PCREPOSIX_EXP_DECL int regexec(const regex_t *, const char *, size_t,
                     regmatch_t *, int);
PCREPOSIX_EXP_DECL size_t regerror(int, const regex_t *, char *, size_t);
PCREPOSIX_EXP_DECL void regfree(regex_t *);

#ifdef __cplusplus
}   /* extern "C" */
#endif

#endif /* End of pcreposix.h */
