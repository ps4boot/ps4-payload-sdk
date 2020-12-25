#!/bin/bash

# Prerequisites
apt-get update
apt-get -y upgrade
apt-get -y install make gcc binutils

# Delete directory if it exists
rm -rf ~/PS4SDK || true

# Clone Repo
git clone https://github.com/Scene-Collective/ps4-payload-sdk ~/PS4SDK

# Build SDK
pushd ~/PS4SDK/libPS4
make
popd

# Clear path from .bashrc if it's there
sed -i "s/^\s*export PS4SDK=.*//gm" ~/.bashrc

# Add to paths
echo "export PS4SDK=~/PS4SDK" | tee -a ~/.bashrc
export PS4SDK=~/PS4SDK
