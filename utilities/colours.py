#!/usr/bin/python
import sys
import getopt
import os
import subprocess

infile = open('../files/colours.csv', "r")
target = open('../files/colour.h', 'w')
target = open('../files/colour.cpp', 'w')

counter = 0
target.write("#ifndef SDLENGINE_H\n#define SDLENGINE_H\n")
for line in infile:
    stemp = line.rstrip('\n');
    stemp = stemp.rstrip('\r');
    colour = stemp.split(",")[0];
    rgbcode = stemp.split(",")[1].split("-");
    colour = colour.replace(" ","_");
    red = rgbcode[0];
    green = rgbcode[1];
    blue = rgbcode[2];
    target.write("\n")
    target.write("\tcustomcolour " + colour + "; \n\t"+colour+".red = " + red + ";\n\t"+colour+".green = " + green + ";\n\t"+colour+".blue = " +blue +";\n")
    counter = counter + 1;
target.write("#endif\n")

infile.close()
target.close()
print counter