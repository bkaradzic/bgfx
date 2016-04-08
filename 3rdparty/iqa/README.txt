Doxygen documentation can be found at: http://tdistler.com/iqa

BUILD:

  All build artifacts end up in build/<configuration>, where <configuration> is
  'debug' or 'release'.

  Windows:
    - Open iqa.sln, select 'Debug' or 'Release', and build. The output is a 
      static library 'iqa.lib'.
    - To run the tests under the debugger, first right-click the 'test' project,
      select Properties -> Configuration Properties -> Debugging and set
      'Working Directory' to '$(OutDir)'. Then start the application.

  Linux:
    - Change directories into the root of the IQA branch you want to build.
    - Type `make` for a debug build, or `make RELEASE=1` for a release build.
      The output is a static library 'libiqa.a'.
    - Type `make test` (or `make test RELEASE=1`) to build the unit tests.
    - Type `make clean` (or `make clean RELEASE=1`) to delete all build
      artifacts.
    - To run the tests, `cd` to the build/<configuration> directory and type
      `./test`.


USE:

  - Include 'iqa.h' in your source file.
  - Call iqa_* methods.
  - Link against the IQA library.


HELP & SUPPORT:

  Further help can be found at: https://sourceforge.net/projects/iqa/support

