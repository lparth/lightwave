lib_LTLIBRARIES = libssoafdclient.la

libssoafdclient_la_SOURCES = \
    active_directory_join_info_data.c \
    active_directory_join_request_data.c \
    ad_provider_resource.c \
    vecs_resource.c

libssoafdclient_la_CPPFLAGS = \
    -I$(top_srcdir)/vmidentity/ssoclients/common/include/ \
    -I$(top_srcdir)/vmidentity/ssoclients/common/include/public/ \
    -I$(top_srcdir)/vmidentity/ssoclients/restclient/coreclient/include/ \
    -I$(top_srcdir)/vmidentity/ssoclients/restclient/coreclient/include/public/ \
    -I$(top_srcdir)/vmidentity/ssoclients/restclient/afdclient/include/public/

libssoafdclient_la_LIBADD = \
    @top_builddir@/vmidentity/ssoclients/restclient/coreclient/src/libssocoreclient.la
