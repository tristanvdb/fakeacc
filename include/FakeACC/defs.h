
#ifndef __FAKEACC_DEFS_H__
#define __FAKEACC_DEFS_H__

#if defined(__FAKEACC_SPACE__) || defined(__FAKEACC_USER__) || defined(__FAKEACC_STATIC__) || defined(__FAKEACC_KERNEL__)
#error None of __FAKEACC_*__ macro should be defined.
#endif

#define __FAKEACC_NONE__     0
#define __FAKEACC_USER__     1
#define __FAKEACC_STATIC__   2
#define __FAKEACC_KERNEL__  3

#if defined(FAKEACC_FORCED)
#define __FAKEACC_SPACE__ __FAKEACC_NONE__
#elif  defined(FAKEACC_USER) && !defined(FAKEACC_STATIC) && !defined(FAKEACC_KERNEL)
#define __FAKEACC_SPACE__ __FAKEACC_USER__
#elif !defined(FAKEACC_USER) &&  defined(FAKEACC_STATIC) && !defined(FAKEACC_KERNEL)
#define __FAKEACC_SPACE__ __FAKEACC_STATIC__
#elif !defined(FAKEACC_USER) && !defined(FAKEACC_STATIC) &&  defined(FAKEACC_KERNEL)
#define __FAKEACC_SPACE__ __FAKEACC_KERNEL__
#elif !defined(FAKEACC_USER) && !defined(FAKEACC_STATIC) && !defined(FAKEACC_KERNEL)
#define __FAKEACC_SPACE__ __FAKEACC_NONE__
#else
#error More than one FAKEACC_* macro are defined.
#endif

#define FAKEACC_SPACE(s1) (__FAKEACC_SPACE__ == __FAKEACC_NONE__ || __FAKEACC_SPACE__ == s1)
#define FAKEACC_SPACE_(s1, s2) (__FAKEACC_SPACE__ == __FAKEACC_NONE__ || __FAKEACC_SPACE__ == s1 || __FAKEACC_SPACE__ == s2)

#endif /* __FAKEACC_DEFS_H__ */

