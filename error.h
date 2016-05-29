// FIXME: errors should be better all around.

#ifdef __GNUC__
#define NORETURN __attribute__((noreturn))
#else
#define NORETURN
#endif

void error(const char*) NORETURN;
