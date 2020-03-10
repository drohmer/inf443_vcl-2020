#!/bin/bash
 
rm -f out.mp4
cd sph
convert '*.png[640x]' resized_%03d.jpg
cd ..
ffmpeg -i sph/resized_%3d.jpg -c:v libx264 -r 30 -pix_fmt yuv420p out.mp4
