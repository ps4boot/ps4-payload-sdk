#!/bin/bash

# NOTE: Assuming Ubuntu 20.04

# Install prerequisites if root
if [ "$EUID" -ne 0 ]; then
  echo "Not root, skipping update and install"
else
  apt-get update
  apt-get -y install \
    binutils=2.34-6ubuntu1 \
    gcc=4:9.3.0-1ubuntu2 \
    make=4.2.1-1.2
fi

# Delete directory if it exists and make empty directory
rm -rf ~/PS4SDK || true
mkdir -p ~/PS4SK

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
