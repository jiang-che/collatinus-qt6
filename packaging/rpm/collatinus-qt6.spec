# Fedora RPM spec for the collatinus-qt6 modernization fork.
#
# Build in a clean mock buildroot (preferred):
#     mock -r fedora-rawhide-x86_64 packaging/rpm/collatinus-qt6.spec
# or locally (development only):
#     scripts/build-rpm.sh

Name:           collatinus-qt6
Version:        12.3.0
Release:        1%{?dist}
Summary:        Latin lemmatiser, morphological analyser and scansion tool

License:        LGPL-3.0-or-later
URL:            https://github.com/jiang-che/collatinus-qt6
Source0:        %{name}-%{version}.tar.gz

BuildRequires:  gcc-c++
BuildRequires:  cmake
BuildRequires:  ninja-build
BuildRequires:  pkgconf-pkg-config
BuildRequires:  cmake(Qt6Core)
BuildRequires:  cmake(Qt6Gui)
BuildRequires:  cmake(Qt6Widgets)
BuildRequires:  cmake(Qt6Network)
BuildRequires:  cmake(Qt6Svg)
BuildRequires:  cmake(Qt6PrintSupport)
BuildRequires:  cmake(Qt6LinguistTools)
BuildRequires:  cmake(QuaZip-Qt6)
BuildRequires:  qt6-linguist
# For %check.
BuildRequires:  desktop-file-utils
BuildRequires:  appstream
BuildRequires:  python3

# This package and the official "collatinus" package both ship
# /usr/bin/collatinus, so they cannot be installed together.
Conflicts:      collatinus

%description
Collatinus lemmatises Latin texts: for every word it gives the canonic form
(lemma), the morphology (case, number, gender, person, tense, mood, voice)
and a translation.  It can also generate inflected forms, tag parts of
speech and scan verse.

This package is a Qt 6 / CMake modernization of Collatinus 12.3 with a
Simplified-Chinese interface and morphology labels.

%prep
%autosetup -n %{name}-%{version}

%build
%cmake -G Ninja

%cmake_build

%check
desktop-file-validate resources/org.collatinus.Collatinus.desktop
appstreamcli validate --no-net resources/org.collatinus.Collatinus.metainfo.xml

%install
%cmake_install

%files
%license LICENSE
%doc README.md
%{_bindir}/collatinus
%{_datadir}/collatinus/
%{_datadir}/applications/org.collatinus.Collatinus.desktop
%{_metainfodir}/org.collatinus.Collatinus.metainfo.xml
%{_datadir}/icons/hicolor/256x256/apps/collatinus.png
%{_datadir}/icons/hicolor/scalable/apps/collatinus.svg
%{_mandir}/man1/collatinus.1*

%changelog
* Sun Sep 27 2026 Jiang Che <jiang@fastmail.com> - 12.3.0-1
- Initial package: Qt 6 / CMake modernization fork with Simplified-Chinese
  interface and morphology labels.
