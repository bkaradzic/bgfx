#!/bin/bash

pushd "$(dirname "$0")"

URL_ZIP="https://github.com/wolfpld/tracy/archive/refs/heads/master.zip"

mkdir -p "_tmp"
rm -rf public

wget -O "_tmp/tracy.zip" "$URL_ZIP"
cd _tmp
unzip tracy.zip

mv tracy-master/public ../.
mv tracy-master/LICENSE ../.
cd ..
rm -rf _tmp

# We need access to a private field in the VkCtx class...
sed -i 's/private:/public:/' public/tracy/TracyVulkan.hpp

popd
