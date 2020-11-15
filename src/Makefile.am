bin_PROGRAMS = usg
lib_LTLIBRARIES = libusg.la

libusg_la_SOURCES = \
		payload.c \
		archive.cc

libusg_la_CFLAGS = \
        @CFLAGS@ \
	@LIBSQLITE_CFLAGS@ \
        @LIBZSTD_CFLAGS@

libusg_la_LIBADD = \
	@LIBSQLITE_LIBS@ \
        @LIBZSTD_LIBS@

usg_SOURCES = main.c
usg_LDADD = libusg.la
