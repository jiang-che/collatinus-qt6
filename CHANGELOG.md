CHANGELOG
=========

## 12.3.0-1 — 2026-09-27

First release of **Collatinus-Qt6**, a modernization fork of Collatinus
12.3.  The version inherits upstream's major.minor (12.3) and appends the
fork's own revision (.0).

Highlights since upstream 12.3:

* **Qt 6**: migrated every Qt 5-only API (`QRegExp` → `QRegularExpression`,
  `QTextStream::setCodec` → `setEncoding`, `QSettings::setIniCodec`,
  `QSet::toList`, `QPrintDialog` options, `QAction` include, …).
* **CMake + Ninja** build system (qmake kept only as historical reference).
* **QuaZip 1.x** (via the distribution package / pkg-config).
* **FHS/XDG data paths**: `--data-dir`, `COLLATINUS_DATA_DIR`, installed
  data directory, user data under `~/.local/share/collatinus`.
* **Simplified-Chinese interface** (`i18n/collatinus_zh_CN.ts`) with
  data-driven language selection and automatic detection.
* **Chinese morphology labels** (`bin/data/morphos.zh`), including the
  mandated terms mood = 式 and ablative = 夺格.
* Fixed a light appearance independent of the desktop theme.
* **Linux integration**: desktop entry, AppStream metadata, hicolor icons,
  man page.
* **Packaging**: native Debian (`debian/`, `scripts/build-deb.sh`) and
  Fedora RPM (`packaging/rpm/collatinus-qt6.spec`, `scripts/build-rpm.sh`).
* **CI/release**: GitHub Actions build and release workflows; source
  tarball via `scripts/build-source-tarball.sh`.

Licensing: LGPL-3.0-or-later (Collatinus was relicensed from GPL-3 to LGPL-3
in 2026 by its author; see `LICENSE`).
