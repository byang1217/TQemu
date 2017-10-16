#!/bin/sh -e

aclocal
autoheader
automake --add-missing
autoconf

