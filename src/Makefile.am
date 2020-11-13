bin_PROGRAMS = usg
lib_LTLIBRARIES = libusg.la

libusg_la_SOURCES = \
		archive.c \
		payload.c

libusg_la_CFLAGS = \
        @CFLAGS@ \
        @LIBZSTD_CFLAGS@

libusg_la_LIBADD = \
        @LIBZSTD_LIBS@

usg_SOURCES = main.c
usg_LDADD = libusg.la
