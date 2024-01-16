Tyler Sulsenti

3rd Party library used - cURLpp - https://github.com/jpbarrette/curlpp/tree/master
Source will be included in zip.

I installed using clion + vcpkg

macos:
brew install curlpp
cmake file: find_package(unofficial-curlpp CONFIG REQUIRED)
target_link_libraries(HLSParser PRIVATE unofficial::curlpp::curlpp)


Instructions for running the app:

There are no command line options. Perhaps in the future, if given more time, some options could have been included for various things.

The easiest way to run the program would be to import it into clion in macOS & install cURLpp using vcpkg in clion.

From the command line, ensnure cmake is installed. If not, install it with brew install cmake.


cmake -DCMAKE_BUILD_TYPE=Debug -DCMAKE_MAKE_PROGRAM=/Applications/CLion.app/Contents/bin/ninja/mac/aarch64/ninja -DCMAKE_TOOLCHAIN_FILE=/Users/SULST002/.vcpkg-clion/vcpkg/scripts/buildsystems/vcpkg.cmake -G Ninja -S /Users/SULST002/CLionProjects/HLSParser -B /Users/SULST002/CLionProjects/HLSParser/cmake-build-debug

However, these paths should be changed to your machine's. If i were to do this again, id use g++ and makefiles.

