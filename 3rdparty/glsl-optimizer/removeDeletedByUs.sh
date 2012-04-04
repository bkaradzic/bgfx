#! /bin/sh
git rm -rf docs
git rm -rf src/mesa/drivers
git rm -rf src/gallium
git rm -rf $(git status --porcelain | awk '/^DU/ {print $NF}')
