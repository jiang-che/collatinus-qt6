#!/bin/sh
# Regenerate the Qt Linguist source catalogs from the C++ sources.
#
#   scripts/update-translations.sh
#
# Run this after adding/removing tr() strings; then rebuild so that
# CMake's release_translations step recompiles and embeds the .qm files.
# Override the lupdate binary with LUPDATE=/path/to/lupdate if needed.

set -eu

here=$(cd "$(dirname "$0")" && pwd)
root=$(cd "$here/.." && pwd)

if [ -n "${LUPDATE:-}" ]; then
    lupdate="$LUPDATE"
elif command -v lupdate-qt6 >/dev/null 2>&1; then
    lupdate=lupdate-qt6
elif command -v lupdate6 >/dev/null 2>&1; then
    lupdate=lupdate6
else
    lupdate=lupdate
fi

"$lupdate" "$root/src" -I "$root/src" -ts \
    "$root/i18n/collatinus_fr.ts" \
    "$root/i18n/collatinus_en.ts" \
    "$root/i18n/collatinus_zh_CN.ts"

echo "Catalogs updated: i18n/*.ts"
echo "Rebuild to regenerate and embed the .qm files."
