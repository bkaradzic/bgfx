#! /bin/sh
git rm -rf bin
git rm -rf docs
git rm -rf m4
git rm -rf src/egl
git rm -rf src/glsl/glcpp/tests
git rm -rf src/loader
git rm -rf src/mapi
git rm -rf src/mesa/drivers
git rm -rf src/mesa/main/tests
git rm -rf src/mesa/state_tracker
git rm -rf src/gallium
git rm -rf src/glx
git rm -rf src/gtest
git rm -rf $(git status --porcelain | awk '/^DU/ {print $NF}')
