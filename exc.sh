#!/bin/sh
echo ` gcc $1 -o gl -lGL -lGLU -lglut -o output.x -lm`
echo `./output.x`


