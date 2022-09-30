# KopperDict

A online dictionary result aggregator.

# Build

Build require `qt6` and `qt6-webengine` and a modern C++ compiler.

## openSUSE leap 15.4

Stable distros like Leap ship gcc-7 by default, and there are a series of build problems with qt6.

```shell
sudo zypper in gcc10-c++
```

```
sudo zypper in qt6-gui-devel qt6-base-devel qt6-webengine  qt6-webenginewidgets-devel
```

Then build with cmake:
```shell
export CC=/usr/bin/gcc-10
export CXX=/usr/bin/g++-10

mkdir build && cd ./build
cmake ../
cmake --build .
```

# Custom dict urls

Edit `~/.kopperdict` file, add urls like this

```
Google https://www.google.com/search?q=
Merriam-Webster https://www.merriam-webster.com/dictionary/
Wiktionary https://en.wiktionary.org/wiki/
Oxford https://www.lexico.com/definition/
Longman https://www.ldoceonline.com/dictionary/
Cambridge https://dictionary.cambridge.org/dictionary/english/
```