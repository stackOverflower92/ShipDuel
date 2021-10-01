#!/bin/bash

#Make
cd Launcher/src
make 

#Docs
cd ..
doxygen Doxyfile

#Launch
cd src
./ShipDuelLauncher