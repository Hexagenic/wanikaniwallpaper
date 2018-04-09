wanikaniwallpaper
=================

[![Build Status](https://travis-ci.org/Hexagenic/wanikaniwallpaper.svg?branch=master)](https://travis-ci.org/Hexagenic/wanikaniwallpaper)

Create a wallpaper based on your WaniKani progress.

## Usage

```
$ ./wanikaniwallpaper --help
Command line options:
  -k [ --apikey ] arg                 API key
  -w [ --width ] arg (=1920)          Width of wallpaper
  -h [ --height ] arg (=1080)         Height of wallpaper
  -o [ --out ] arg (=out.png)         Output filename
  -f [ --font ] arg (=ipag.ttf)       Relative or absolute font filepath
  -i [ --heisig-index ] arg (=0)      Progress in Heisig's RTK (6th ed.)
  --margin-left arg (=0)              Space to leave blank to the left
  --margin-right arg (=0)             Space to leave blank to the right
  --margin-top arg (=0)               Space to leave blank to the top
  --margin-bottom arg (=0)            Space to leave blank to the bottom
  --color-background arg (=0x000000)  Color for background
  --color-unseen arg (=0x303030)      Color for unseen characters
  --color-heisig arg (=0xA0A0A0)      Color for Heisig characters
  --color-apprentice arg (=0xDD0093)  Color for apprentice characters
  --color-guru arg (=0x882D9E)        Color for guru characters
  --color-master arg (=0x294DDB)      Color for master characters
  --color-enlightened arg (=0x0093DD) Color for enlightened characters
  --color-burned arg (=0xFFFFFF)      Color for burned characters
  --color-error arg (=0xFF0000)       Color for error'ed characters
  --help                              Produce this help message

These options can also be saved in a config.ini file in this directory.
```

## Building

Building on Debian-based linux systems requires the following packages:

 * `libfreetype6-dev`
 * `libutfcpp-dev`
 * `libcurl3-dev`
 * `libjsoncpp-dev`
 * `libboost-program-options-dev`

Running requires a TTF font with Kanji available. The default is `ipag.ttf`
which is available [from this repository][ipag].

[ipag]: https://github.com/hyoshiok/ttf-ipafont
