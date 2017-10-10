function generate()
{
    cmake -G "Unix Makefiles" -DASSIMP_NO_EXPORT=$TRAVIS_NO_EXPORT -DBUILD_SHARED_LIBS=$SHARED_BUILD -DASSIMP_COVERALLS=$ENABLE_COVERALLS
}

if [ $ANDROID ]; then
    ant -v -Dmy.dir=${TRAVIS_BUILD_DIR} -f ${TRAVIS_BUILD_DIR}/port/jassimp/build.xml ndk-jni
fi
if [ "$TRAVIS_OS_NAME" = "linux" ]; then
    generate \
    && make -j4 \
    && sudo make install \
    && sudo ldconfig \
    && (cd test/unit; ../../bin/unit) \
    #&& (cd test/regression; chmod 755 run.py; ./run.py ../../bin/assimp; \
	#   chmod 755 result_checker.py; ./result_checker.py)
fi
