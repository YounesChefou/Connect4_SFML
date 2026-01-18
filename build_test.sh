cmake -B CMakebuild/
cmake --build CMakebuild/
cd CMakebuild/test
ctest
cd ../..