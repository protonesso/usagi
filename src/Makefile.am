bin_PROGRAMS = usg
lib_LTLIBRARIES = libusg.la

libusg_la_SOURCES = \
		archive.cc \
		payload.cc

libusg_la_CFLAGS = \
        @CFLAGS@ \
	@LIBSQLITE_CFLAGS@ \
        @LIBZSTD_CFLAGS@

libusg_la_LIBADD = \
	@LIBSQLITE_LIBS@ \
        @LIBZSTD_LIBS@

usg_SOURCES = main.cc
usg_LDADD = libusg.la
