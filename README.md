# huerotate-like-webkit
comandline implementation of the css-filter 'hue-rotate' and/or svg feColorMatrix 'hueRotate'

I had serious trouble to replicate the css filter 'hue-rotate', as seen in modern browsers, on the server.
I tried using image magick(different algorithm), reimplementing it in ruby(super slow), jruby (stil super slow) and ended up with this 23kb command line tool.

Usage:
bin/huerotate [angle_deg] [in_image] [out_image]

Dependencies:
freeimage
