#!/bin/bash

# Install prerequisites if root
if [ "$EUID" -ne 0 ]; then
  echo "Not root, skipping update and install"
else
  apt-get update
  apt-get -y install binutils gcc make
fi

# Delete directory if it exists and make empty directory
rm -rf /opt/ps4sdk || true
mkdir -p /opt/ps4sdk

# Build SDK
pushd libPS4
make
popd

# Copy compiled SDK
cp -r libPS4 /opt/ps4sdk

# Clear path from .bashrc if it's there
sed -i "s/^\s*export PS4SDK=.*//gm" ~/.bashrc

# Add to paths
echo "export PS4SDK=/opt/ps4sdk" | tee -a ~/.bashrc
export PS4SDK=/opt/ps4sdk
