#!/usr/bin/python3
import sys

filein = open(sys.argv[1],'rb')
fileout = open(sys.argv[2],'wb')

blocksize=9
s=filein.read(blocksize)
if not s:
 quit
while True:
 fileout.write(s)
 s=filein.read(blocksize)
 if not s:
  break

fileout.close()
filein.close()
