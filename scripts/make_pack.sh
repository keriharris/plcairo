#!/bin/bash

########################################################################
#  This file is part of PLcairo.
#
#   Copyright (C) 2015 Keri Harris <keri@gentoo.org>
#
#   PLcairo is free software: you can redistribute it and/or modify
#   it under the terms of the GNU Lesser General Public License as
#   published by the Free Software Foundation, either version 2.1
#   of the License, or (at your option) any later version.
#
#   PLcairo is distributed in the hope that it will be useful,
#   but WITHOUT ANY WARRANTY; without even the implied warranty of
#   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
#   GNU General Public License for more details.
#
#   You should have received a copy of the GNU General Public License
#   along with PLcairo.  If not, see <http://www.gnu.org/licenses/>.
#
########################################################################

SCRIPT=$(readlink -f "$0")
SCRIPTDIR=$(dirname "$SCRIPT")
TOPDIR=$SCRIPTDIR/..

VERSION=$(cat $TOPDIR/VERSION)
PACKDIR=pack-$VERSION/plcairo

cd $SCRIPTDIR
rm -rf pack-$VERSION

mkdir -p $PACKDIR
echo "name('plcairo')." > $PACKDIR/pack.pl
echo "title('plcairo - Prolog bindings for cairo graphics library')." >> $PACKDIR/pack.pl
echo "version('$VERSION')." >> $PACKDIR/pack.pl
echo "author('Keri Harris', 'keri@gentoo.org')." >> $PACKDIR/pack.pl
echo "download('http://dev.gentoo.org/~keri/plcairo/plcairo-*.tgz')." >> $PACKDIR/pack.pl
echo "requires('plgi')." >> $PACKDIR/pack.pl

mkdir -p $PACKDIR/prolog
cp $TOPDIR/prolog/plcairo.pl $PACKDIR/prolog/

mkdir -p $PACKDIR/src
cp $TOPDIR/src/*.{c,h} $PACKDIR/src/
cp $TOPDIR/src/config.h.in $PACKDIR/src/
cp $TOPDIR/src/Makefile.in $PACKDIR/src/
sed -i -e "s:@SWI_SOLIBDIR@:../\$(PACKSODIR):" \
       -e "s:@SWI_PLLIBDIR@:../prolog:" \
       -e "/\$(INSTALL_PROGRAM)/{h;N;N;N;N;N;x}" $PACKDIR/src/Makefile.in

mkdir -p $PACKDIR/examples
cp $TOPDIR/examples/*.pl $PACKDIR/examples/
cp $TOPDIR/examples/*.png $PACKDIR/examples/
cp $TOPDIR/examples/README $PACKDIR/examples/
mkdir -p $PACKDIR/examples/backends
cp $TOPDIR/examples/backends/*.pl $PACKDIR/examples/backends/

cp $TOPDIR/README $PACKDIR/
cp $TOPDIR/LICENSE $PACKDIR/
cp $TOPDIR/VERSION $PACKDIR/

cp $TOPDIR/configure.in $PACKDIR/
sed -i -e "/SWI_BASE/d" \
       -e "/SWI_ARCH/d" \
       -e "/SWI_SOLIBDIR/d" \
       -e "/SWI_PLLIBDIR/d" \
       -e "/PKG_CHECK_MODULES(SWI/{N;N;d}" $PACKDIR/configure.in
cp $TOPDIR/aclocal.m4 $PACKDIR/
cp $TOPDIR/install-sh $PACKDIR/
cp $TOPDIR/Makefile.in $PACKDIR/

cd pack-$VERSION
tar -cvzf plcairo-$VERSION.tgz plcairo
