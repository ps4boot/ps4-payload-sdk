# Prerequisites
apt-get update
apt-get -y upgrade
apt-get -y install make clang gcc llvm binutils

# Clone Repo
git clone https://github.com/Scene-Collective/ps4-payload-sdk ~/PS4-SDK

# Build SDK
pushd ~/PS4-SDK/libPS4
make
popd

# Add to paths
echo "export PS4SDK=~/PS4-SDK" | tee -a ~/.bash.rc
source ~/.bashrc
