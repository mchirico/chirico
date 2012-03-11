#!/bin/bash
cd ~/
mkdir -p node
cd node
wget http://nodejs.org/dist/node-v0.4.12.tar.gz
tar -xzf node-v0.4.12.tar.gz
cd node-v0.4.12  
./configure
make
sudo make install
