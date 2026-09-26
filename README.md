# Collatinus-Qt6

Collatinus-Qt6 is an unofficial Linux fork of Collatinus, the Latin
lemmatiser, morphological analyser, dictionary and scansion tool written by
Yves Ouvrard and Philippe Verkerk with other contributors.

The Latin engine and its data are kept as they are. What changes is the
desktop application and the way it builds and installs on current Linux
systems. This is not an official release of the original project.

This fork is created and maintained by Che JIANG (蒋澈), Department of the
History of Science, Tsinghua University. Contact: jiang@fastmail.net or
jiangche@tsinghua.edu.cn.

## What is different here

- Qt 5 to Qt 6.
- qmake to CMake (Ninja or Make).
- QuaZip 0.x/5 to the system QuaZip 1.x for Qt 6.
- Desktop entry, icons, AppStream metadata, man page, standard data paths,
  and `.deb` and `.rpm` packages.
- A Simplified-Chinese user interface.

## Chinese

The interface can be set to Simplified Chinese, including the grammatical
terms. There is no Chinese dictionary in this release. The interface
language and the dictionary language are separate, so Chinese can be used
with the existing English, French, German and other dictionaries.

## Source basis

Based on the Collatinus 12.3 source preserved by Debian, including the
Debian 12.3-2 packaging fixes.

## Build

Needs a C++17 compiler, CMake, Ninja or Make, Qt 6 development packages
(Core, Gui, Widgets, Network, Svg, PrintSupport, LinguistTools) and QuaZip
1.x for Qt 6.

```sh
cmake -S . -B build -G Ninja -DCMAKE_BUILD_TYPE=Release
cmake --build build
./build/bin/collatinus                 # run a development build
sudo cmake --install build             # install
```

The data directory can be chosen with `--data-dir PATH` or the
`COLLATINUS_DATA_DIR` environment variable.

## Packages

- Debian and Ubuntu: `debian/`, built with `dpkg-buildpackage -us -uc -b`
  (helper: `scripts/build-deb.sh`).
- Fedora and RPM: `packaging/rpm/collatinus-qt6.spec`, built with
  `rpmbuild -ba` (helper: `scripts/build-rpm.sh`).
- Source tarball: `scripts/build-source-tarball.sh TAG`.

Both packages install `/usr/bin/collatinus`, so they conflict with a
distribution collatinus package.

## License

LGPL-3.0-or-later. Collatinus was relicensed from GPL-3 to LGPL-3 by its
author, Yves Ouvrard. The change is recorded in the Debian Collatinus 12.3-2
source package. The original copyright and authorship notices are kept.

## Bugs

Please report problems with this fork (Qt 6 port, build, packaging, Chinese
interface) here, not to the original Collatinus maintainers.
