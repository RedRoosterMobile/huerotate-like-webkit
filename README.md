# huerotate-like-webkit
comandline implementation of the css-filter 'hue-rotate' and/or svg feColorMatrix 'hueRotate'

I had serious trouble to replicate the css filter 'hue-rotate', as seen in modern browsers, on the server.
I tried using image magick(different algorithm), reimplementing it in ruby(super slow), jruby (still super slow) and ended up with this 23kb command line tool, which fast as lightnin', even for massive images.

## Usage:
```
bin/huerotate [angle_deg] [in_image] [out_image]
```

## Dependencies:

freeimage

## Install:
```
git clone https://github.com/RedRoosterMobile/huerotate-like-webkit
cd huerotate-like-webkit/
sudo apt-get install build-essential
sudo apt-get-install libfreeimage-dev # to used a previously build executabel do: sudo apt-get install libfreeimage3
make
bin/huerotate 
```

