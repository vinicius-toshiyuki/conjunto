AC_INIT([amparser], [1.0], [vtmsugimoto@gmail.com])
AM_INIT_AUTOMAKE([-Wall -Werror foreign])

AC_PROG_CC

AC_PROG_LEX
AC_PROG_YACC

AC_FUNC_ALLOCA
AC_FUNC_MALLOC
AC_FUNC_REALLOC
AC_TYPE_INT16_T
AC_TYPE_INT32_T
AC_TYPE_INT8_T
AC_TYPE_SIZE_T
AC_TYPE_UINT16_T
AC_TYPE_UINT32_T
AC_TYPE_UINT8_T

AC_CHECK_FUNCS(memset setlocale strdup)

AC_CHECK_HEADERS(libintl.h limits.h locale.h malloc.h stddef.h wchar.h)

AC_CHECK_TYPES(ptrdiff_t)

AC_CONFIG_HEADERS([include/config.h])
AC_ARG_WITH(
	[unicode],
	[AS_HELP_STRING(
		[--with-unicode],
		[support printing using unicode characters]
	)],
	[AC_DEFINE(
		[WITH_UNICODE],
		[1],
		[Support printing using unicode characters]
		)],
	[]
	)

AC_ARG_WITH(
	[truecolor],
	[AS_HELP_STRING(
		[--with-truecolor],
		[support printing using 24 bit colors]
	)],
	[AC_DEFINE(
		[WITH_TRUECOLOR],
		[1],
		[Support printing using 24 bit colors]
		)],
	[]
	)

AC_CONFIG_FILES([
	Makefile
	src/Makefile
])
AC_OUTPUT
