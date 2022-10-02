# kpDict

A simple online dictionary result aggregator.

# Compare to similar projects

[GoldenDict](https://github.com/xiaoyifang/goldendict) has a robust legacy of supporting off-line dictionaries, but it is kinda bloat for users who only use online dictionaries. This project was born due to my frustration with GoldenDict (CopperDict -> KopperDict -> kpDict).

[Crow Translate](https://github.com/crow-translate/crow-translate) uses [online translator's API](https://github.com/crow-translate/QOnlineTranslator/blob/1.6.0/src/qonlinetranslator.h#L502). The result is much cleaner but adding new translator is not an easy maneuver.

# Build

Build require `qt6` and `qt6-webengine` and a modern C++ compiler (Need c++17).

## Linux

### openSUSE leap 15.4

Stable distros ships older gcc by default. The older gcc has a series of build problems with qt6.

For openSUSE leap 15.4, gcc11-c++ from the main repo is needed:

```shell
sudo zypper in gcc11-c++
```
```
sudo zypper in qt6-gui-devel qt6-base-devel qt6-webengine  qt6-webenginewidgets-devel
```

Then build with cmake:

```shell
# Not needed if your default gcc is new enough
export CXX=/usr/bin/g++-11

cmake -S . -B build \
      --install-prefix=/usr/local \
      -G Ninja \
      -DCMAKE_BUILD_TYPE=Release

cmake --build build --parallel 4

# Optional step:
# Install the binary to `/usr/local/bin/kopperdict`
# Install prefix was set above

cmake --install build

```

## Windows

As of Qt6.4, MSVC2019(? MSVC2022 also works ?) and MSVC qt libs are needed (webengine on Windows has hard requirement on MSVC ). In Qt's MaintenanceTool.exe, qt webengine and webchannel have to be selected.

QtCreator can detect almost everything. Vistual Studio and Clion seems need `${Qt_install_dir}\6.4.0\msvc2019_64\bin` to be in PATH.

Use `windeployqt` on the `.exe` to copy DLLs automatically.

## macOS

Similar to linux, homebrewed qt works out of box and can be used to build an `.app` bundle. However, bundling dependencies into the `.app` is  magic that I don't know/care.

TODO: cpack for win&mac?

# Custom dict urls

Edit `~/.kopperdict/urls` file, add urls like this, the word will be appended to the end of url

```
Google https://www.google.com/search?q=
Merriam-Webster https://www.merriam-webster.com/dictionary/
Wiktionary https://en.wiktionary.org/wiki/
Oxford https://www.lexico.com/definition/
Longman https://www.ldoceonline.com/dictionary/
Cambridge https://dictionary.cambridge.org/dictionary/english/
```

# Design. To my future self (and potential contributors)

Clean Architecture, Decoupling functionalities, S.O.L.I.D principles....

Yes, yes and yes.

However, this is a simple app, the data are stored in responsible UI components. The kpDict.cpp is
a [God object](https://en.wikipedia.org/wiki/God_object).

The code is shorter :)
