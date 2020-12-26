#!/bin/bash

# NOTE: Assuming Ubuntu 20.04

# Prerequisites
apt-get update
apt-get -y install \
  binutils=2.34-6ubuntu1 \
  gcc=4:9.3.0-1ubuntu2 \
  make=4.2.1-1.2

# Build SDK
pushd libPS4
make
popd

# Clear path from .bashrc if it's there
sed -i "s/^\s*export PS4SDK=.*//gm" ~/.bashrc

# Add to paths
echo "export PS4SDK=$(pwd)/PS4SDK" | tee -a ~/.bashrc
export PS4SDK=$(pwd)/PS4SDK
