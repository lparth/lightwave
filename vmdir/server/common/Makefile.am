#
# Copyright (c) VMware Inc.  All rights Reserved.
# Module Name: common Makefile
# Abstract: VMware Cloud Directory Platform.
# Created on: Oct 4, 2011
# Author: Sanjay Jain (sanjain@vmware.com)
#         Sriram Nambakam (snambakam@vmware.com)
#

noinst_LTLIBRARIES = libsrvcommon.la

libsrvcommon_la_SOURCES = \
    accnt_mgmt.c          \
    candidates.c          \
    dcconnthr.c           \
    entryencodedecode.c   \
    krbsrvutil.c          \
    nodeidentity.c        \
    oidctovmdirerror.c    \
    oprequestutil.c       \
    security-sd.c         \
    srp.c                 \
    util.c                \
    vectorutils.c         \
    vmafdlib.c            \
    vmdirentry.c          \
    vmdirtoldaperror.c

libsrvcommon_la_CPPFLAGS = \
    -I$(top_srcdir)/vmdir/include \
    -I$(top_srcdir)/vmdir/include/public \
    -I$(top_srcdir)/vmdir/thirdparty/openldap/include \
    -I$(top_srcdir)/vmdir/thirdparty/openldap/libraries/liblber \
    -I$(top_srcdir)/vmdir/thirdparty/openldap/libraries/libldap \
    -I$(top_srcdir)/vmdir/thirdparty/heimdal \
    -I$(top_srcdir)/vmdir/thirdparty/heimdal/krb5-crypto \
    -I$(top_srcdir)/vmdir/thirdparty/heimdal/asn1 \
    -I$(top_srcdir)/vmdir/thirdparty \
    -I$(top_srcdir)/vmdir/server/include \
    -I$(top_srcdir)/vmmetrics/include/public \
    -I$(top_srcdir)/vmidentity/ssoclients/common/include/public \
    -I$(top_srcdir)/vmidentity/ssoclients/oidc/include/public \
    @OPENSSL_INCLUDES@ \
    @DCERPC_INCLUDES@ \
    @LW_INCLUDES@

libsrvcommon_la_LDFLAGS = \
    -static
