# Desktop integration assets (SPEC phase 7)

* `org.collatinus.Collatinus.desktop` — freedesktop.org desktop entry
  (localized for French and Simplified Chinese).
* `org.collatinus.Collatinus.metainfo.xml` — AppStream metadata
  (localized description in English/French/Chinese).
* `icons/collatinus-256.png` — 256×256 application icon for the hicolor
  theme, generated from the project icon `collatinus.png` (512×512):

  ```sh
  convert collatinus.png -resize 256x256 resources/icons/collatinus-256.png
  ```

The scalable icon installed to `hicolor/scalable/apps/collatinus.svg` is the
project's own `res/collatinus.svg`.  All icons belong to the Collatinus
project (see `LICENSE`).

Validation:

```sh
desktop-file-validate resources/org.collatinus.Collatinus.desktop
appstreamcli validate --no-net resources/org.collatinus.Collatinus.metainfo.xml
```

(`--no-net` skips the reachability check on the homepage URL, which CI
runners may not be able to perform.)
