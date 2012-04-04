#! /bin/sh

srcdir=`dirname "$0"`
test -z "$srcdir" && srcdir=.

SRCDIR=`(cd "$srcdir" && pwd)`
ORIGDIR=`pwd`

if test "x$SRCDIR" != "x$ORIGDIR"; then
	echo "Mesa cannot be built when srcdir != builddir" 1>&2
	exit 1
fi

MAKEFLAGS=""

autoreconf -v --install || exit 1

"$srcdir"/configure "$@"
