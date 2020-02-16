# Prerequisites
apt-get update
apt-get -y upgrade
apt-get -y install make clang gcc llvm binutils

# Clone Repo
git clone https://github.com/Scene-Collective/ps4-payload-sdk ~/PS4SDK

# Build SDK
pushd ~/PS4SDK/libPS4
make
popd

# Add to paths
echo "export PS4SDK=~/PS4SDK" | tee -a ~/.bashrc
source ~/.bashrc
