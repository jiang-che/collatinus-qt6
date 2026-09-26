#!/bin/sh
# Build the Fedora RPM(s) for collatinus-qt6.
#
#   scripts/build-rpm.sh            # binary + source RPM (rpmbuild -ba)
#
# This is a convenience wrapper for local development; the supported way to
# validate the package is a clean buildroot:
#
#   mock -r fedora-rawhide-x86_64 packaging/rpm/collatinus-qt6.spec
#
# The script stages a source tarball (with a fixed top-level directory) into a
# temporary rpmbuild tree, so the working directory is not polluted.

set -eu

here=$(cd "$(dirname "$0")" && pwd)
root=$(cd "$here/.." && pwd)

name=collatinus-qt6
# Keep in sync with CMakeLists.txt and packaging/rpm/%{name}.spec.
version=$(sed -n 's/^[[:space:]]*VERSION[[:space:]]*\([0-9][0-9.]*\).*/\1/p' \
    "$root/CMakeLists.txt" | head -1)
if [ -z "$version" ]; then
    echo "cannot determine the version from CMakeLists.txt" >&2
    exit 1
fi

top=${RPMBUILD_TOPDIR:-$(mktemp -d /tmp/rpmbuild.XXXXXX)/rpmbuild}
mkdir -p "$top/BUILD" "$top/BUILDROOT" "$top/RPMS" "$top/SOURCES" "$top/SPECS" "$top/SRPMS"

# Stage the sources under "collatinus-qt6-<version>/" and archive the staged
# directory.  This guarantees the expected top-level directory and avoids
# archiving the output tarball itself (the source must therefore live outside
# the staged directory).
stage=$(mktemp -d /tmp/collatinus-src.XXXXXX)
trap 'rm -rf "$stage"' EXIT INT TERM
mkdir -p "$stage/$name-$version"

if command -v git >/dev/null 2>&1 && [ -d "$root/.git" ]; then
    ( cd "$root" && git archive --format=tar HEAD ) \
        | tar -x -C "$stage/$name-$version"
else
    ( cd "$root" && tar --exclude=.git --exclude=./rpmbuild -cf - . ) \
        | tar -x -C "$stage/$name-$version"
fi

tar -C "$stage" -czf "$top/SOURCES/$name-$version.tar.gz" "$name-$version"

cp "$root/packaging/rpm/$name.spec" "$top/SPECS/"

echo "rpmbuild tree: $top"
rpmbuild -ba --define "_topdir $top" "$top/SPECS/$name.spec" "$@"
