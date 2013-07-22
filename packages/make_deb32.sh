#!/bin/sh
#gzip -9
VERSION="1.5"
VERSIONPKG="1"
PLATFORM="i386"
ARCH=32
PKGNAME=protimer

SRCDIR=../bin$ARCH
DEBNAME=${PKGNAME}_${VERSION}-${VERSIONPKG}_$PLATFORM.deb

SIZE=`du $PKGNAME --exclude=DEBIAN -s | sed -rn "s/^([0-9]+).*/\1/gp"`

gzip -9 -c changelog > protimer/usr/share/doc/protimer/changelog.gz
rm $PKGNAME/usr/bin/*
cp $SRCDIR/* $PKGNAME/usr/bin/
chmod 0755 $PKGNAME/usr/bin/*

strip --strip-unneeded $PKGNAME/usr/bin/*

echo "Version: $VERSION" > $PKGNAME/DEBIAN/control
echo "Architecture: $PLATFORM" >> $PKGNAME/DEBIAN/control
echo "Installed-Size: $SIZE" >> $PKGNAME/DEBIAN/control
cat control >> $PKGNAME/DEBIAN/control
cd $PKGNAME
md5deep -r usr -l > DEBIAN/md5sums
cd ..
fakeroot dpkg-deb --build $PKGNAME
mv $PKGNAME.deb $DEBNAME
lintian $DEBNAME
alien --to-rpm --scripts ./$DEBNAME
alien --to-tgz --scripts ./$DEBNAME
                                                                             
mv $PKGNAME-$VERSION.tgz ../distr/$PKGNAME-$VERSION-$PLATFORM-$VERSIONPKG.tgz
mv $DEBNAME ../distr/$DEBNAME
mv *386.rpm ../distr/

