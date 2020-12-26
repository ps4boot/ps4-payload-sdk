#!/bin/bash

# Prerequisites
apt-get update
apt-get -y upgrade
apt-get -y install make gcc binutils

# Delete directory if it exists and make empty directory
rm -rf ~/PS4SDK || true
mkdir -p ~/PS4SDK

# Build SDK
pushd libPS4
make
popd

# Move compiled SDK
mv libPS4 ~/PS4SDK/libPS4

# Clear path from .bashrc if it's there
sed -i "s/^\s*export PS4SDK=.*//gm" ~/.bashrc

# Add to paths
echo "export PS4SDK=~/PS4SDK" | tee -a ~/.bashrc
export PS4SDK=~/PS4SDK
