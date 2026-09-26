#!/bin/sh
# Build the Debian package(s) for collatinus-qt6.
#
#   scripts/build-deb.sh            # binary package (.deb)          -> -b
#   scripts/build-deb.sh -S -us -uc # source package (.dsc/.tar.xz)  -> release
#
# Upstream build dependencies are listed in debian/control; on a Debian
# system check them first with:
#
#   dpkg-checkbuilddeps
#
# The build artefacts (../collatinus-qt6_*.deb, debian/files, obj-*/ …) are
# git-ignored.  To keep the source tree pristine, build from a copy instead:
#
#   cp -a . /tmp/collatinus-qt6 && (cd /tmp/collatinus-qt6 && ./scripts/build-deb.sh)

set -eu

here=$(cd "$(dirname "$0")" && pwd)
root=$(cd "$here/.." && pwd)
cd "$root"

if [ "$#" -eq 0 ]; then
    set -- -b
fi

exec dpkg-buildpackage -us -uc "$@"
