#!/bin/sh
# Build a source tarball of the project from a git ref.
#
#   scripts/build-source-tarball.sh [REF] [OUTDIR]
#
# REF defaults to HEAD (use a tag for a release).  OUTDIR defaults to the
# parent of the repository.  The tarball has a fixed top-level directory
# "collatinus-qt6-<version>/" and contains only tracked files (no .git,
# no build directories, no CI artefacts).

set -eu

here=$(cd "$(dirname "$0")" && pwd)
root=$(cd "$here/.." && pwd)

ref=${1:-HEAD}
outdir=${2:-$(cd "$root/.." && pwd)}

version=$(sed -n 's/^[[:space:]]*VERSION[[:space:]]*\([0-9][0-9.]*\).*/\1/p' \
    "$root/CMakeLists.txt" | head -1)
if [ -z "$version" ]; then
    echo "cannot determine the version from CMakeLists.txt" >&2
    exit 1
fi

name=collatinus-qt6
top="$name-$version"
out="$outdir/$top.tar.xz"

mkdir -p "$outdir"
( cd "$root" && git archive --format=tar --prefix="$top/" "$ref" ) \
    | xz -9 > "$out"

echo "$out"
