#ifndef DEBUG_H_
#define DEBUG_H_

#ifdef DEBUG
# include <cstdio>

# ifdef __GNUC__
#  define return(EXP)                       \
{                                           \
    __typeof__ (EXP) _exp = (EXP);          \
    if (!(_exp)) {                          \
        std::fprintf(stderr,                \
            "DEBUG: %s: PARSE FAIL (%s)\n", \
            __FUNCTION__, #EXP);            \
    }                                       \
    return _exp;                            \
}

#  define DEBUG_PRINT_STR(str, pos)                         \
({                                                          \
    __typeof__ (pos) _pos = (pos);                          \
    std::printf("DEBUG: %s: PARSE STR [%s], POS [%zu]\n",   \
        __FUNCTION__, str + _pos, _pos);                    \
})
# elif
# warning "__GNUC__ is not supported"
# endif /* __GNUC__ */

#endif /* DEBUG */

#endif  // DEBUG_H_
