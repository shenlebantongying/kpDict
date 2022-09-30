# KopperDict

A online dictionary result aggregator.

# Build

Build require `qt6` and `qt6-webengine` and a modern C++ compiler (Need c++17).

## openSUSE leap 15.4

Stable distros ships older gcc by default. The older gcc has a series of build problems with qt6.

For openSUSE leap 15.4, gcc10 from the main repo is needed:

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
