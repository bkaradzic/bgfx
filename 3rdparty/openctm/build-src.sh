#!/bin/bash

# Name of the distribution
distname=OpenCTM-1.0.3

# Clean the source directories
echo Cleaning up...
make -f Makefile.linux clean

# Build all the necessary files
echo Building documentation...
make -f Makefile.linux documentation

# Set up a temporary directory
tmproot=/tmp/openctm-$USER-$$
mkdir $tmproot
tmpdir=$tmproot/$distname
mkdir $tmpdir

# Copy files
echo Copying files to $tmpdir...
cp Makefile* *.txt $tmpdir/
mkdir $tmpdir/lib
cp lib/*.c lib/*.h lib/*.rc lib/*.def lib/Makefile* $tmpdir/lib/
mkdir $tmpdir/lib/liblzma
cp lib/liblzma/* $tmpdir/lib/liblzma/
mkdir $tmpdir/tools
cp tools/*.cpp tools/*.mm tools/*.h tools/*.vert tools/*.frag tools/*.rc tools/Makefile* $tmpdir/tools/
mkdir $tmpdir/tools/icons
cp tools/icons/* $tmpdir/tools/icons/
mkdir $tmpdir/tools/jpeg
cp tools/jpeg/* $tmpdir/tools/jpeg/
mkdir $tmpdir/tools/rply
cp tools/rply/* $tmpdir/tools/rply/
mkdir $tmpdir/tools/glew
cp tools/glew/* $tmpdir/tools/glew/
mkdir $tmpdir/tools/glew/GL
cp tools/glew/GL/* $tmpdir/tools/glew/GL/
mkdir $tmpdir/tools/tinyxml
cp tools/tinyxml/* $tmpdir/tools/tinyxml/
mkdir $tmpdir/tools/zlib
cp tools/zlib/* $tmpdir/tools/zlib/
mkdir $tmpdir/tools/pnglite
cp tools/pnglite/* $tmpdir/tools/pnglite/

mkdir $tmpdir/doc
cp doc/DevelopersManual.pdf $tmpdir/doc/
cp doc/FormatSpecification.pdf $tmpdir/doc/
cp doc/ctmconv.1 $tmpdir/doc/
cp doc/ctmviewer.1 $tmpdir/doc/
mkdir $tmpdir/doc/APIReference
cp doc/APIReference/* $tmpdir/doc/APIReference/

mkdir $tmpdir/plugins
mkdir $tmpdir/plugins/blender
cp plugins/blender/* $tmpdir/plugins/blender/
mkdir $tmpdir/plugins/maya
cp plugins/maya/* $tmpdir/plugins/maya/

mkdir $tmpdir/bindings
mkdir $tmpdir/bindings/delphi
cp bindings/delphi/* $tmpdir/bindings/delphi/
mkdir $tmpdir/bindings/python
cp bindings/python/* $tmpdir/bindings/python/

# Create archives
olddir=`pwd`
cd $tmproot
tar -cvf $distname-src.tar $distname
bzip2 -9 $distname-src.tar
zip -9r $distname-src.zip $distname
cd $olddir
cp $tmproot/*.bz2 $tmproot/*.zip ./

# Remove temporary directory
rm -rf $tmproot

