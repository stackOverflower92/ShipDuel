#!/bin/bash

#Make
cd Game/src;
make

#Docs
cd ..
doxygen Doxyfile

#Launch
cd src
./ShipDuel P1 P2 0