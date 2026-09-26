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
# The wrapper stages a source tarball built from git HEAD into a temporary
# rpmbuild tree, so the working directory is not polluted.

set -eu

here=$(cd "$(dirname "$0")" && pwd)
root=$(cd "$here/.." && pwd)

name=collatinus-qt6
# Keep in sync with CMakeLists.txt and packaging/rpm/%{name}.spec.
version=12.3.0

top=${RPMBUILD_TOPDIR:-$(mktemp -d /tmp/rpmbuild.XXXXXX)/rpmbuild}
mkdir -p "$top/BUILD" "$top/BUILDROOT" "$top/RPMS" "$top/SOURCES" "$top/SPECS" "$top/SRPMS"

if [ -d "$root/.git" ]; then
    (cd "$root" && git archive --format=tar --prefix="$name-$version/" HEAD) \
        | gzip -9 > "$top/SOURCES/$name-$version.tar.gz"
else
    (cd "$root" && tar --exclude=.git -cf - .) \
        | gzip -9 > "$top/SOURCES/$name-$version.tar.gz"
fi

cp "$root/packaging/rpm/$name.spec" "$top/SPECS/"

echo "rpmbuild tree: $top"
exec rpmbuild -ba --define "_topdir $top" "$top/SPECS/$name.spec" "$@"
