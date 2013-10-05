#!/bin/sh
#gzip -9
VERSION="1.0.0"
VERSIONPKG="1"
PLATFORM="amd64"
ARCH=64
PKGNAME=qtdbf


./makeLinNativ.sh
./clean.sh
./copyfiles.sh

DEBNAME=${PKGNAME}_${VERSION}-${VERSIONPKG}_$PLATFORM.deb

SIZE=`du package/$PKGNAME --exclude=DEBIAN -s | sed -rn "s/^([0-9]+).*/\1/gp"`

gzip -9 -c package/changelog > package/qtdbf/usr/share/doc/qtdbf/changelog.gz

strip --strip-unneeded package/$PKGNAME/usr/bin/*

echo "Version: $VERSION" > package/$PKGNAME/DEBIAN/control
echo "Architecture: $PLATFORM" >> package/$PKGNAME/DEBIAN/control
echo "Installed-Size: $SIZE" >> package/$PKGNAME/DEBIAN/control
cat package/control >> package/$PKGNAME/DEBIAN/control
cd package/$PKGNAME
md5deep -r usr -l > DEBIAN/md5sums
cd ..
fakeroot dpkg-deb --build $PKGNAME
mv $PKGNAME.deb $DEBNAME
lintian $DEBNAME
cd ..
#alien --to-rpm --scripts ./$DEBNAME
#alien --to-tgz --scripts ./$DEBNAME
#gzip -c -9 install/* >> $PKGNAME-$VERSION.tgz
#mv $PKGNAME-$VERSION.tgz ../distr/$PKGNAME-$VERSION-$PLATFORM-$VERSIONPKG.tgz
mv package/$DEBNAME distr/$DEBNAME
#mv *64.rpm ../distr/
