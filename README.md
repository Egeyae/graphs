# GRAPHS
#### _[@Egeyae](https://github.com/Egeyae)_

Small C library to work with Graphs. Purpose is to learn more about C, CMake and Graphs.

For the moment lib installation works on UNIX only:
```shell
cd build
cmake ..
sudo make install
```

To access the lib later using CMakeLists.txt for example:

```CMake
# Your stuff...
find_library(GRAPHS_LIB NAMES graphs PATHS /usr/local/lib)

include_directories(/usr/local/include)

target_link_libraries(YOUR_PROJECT PRIVATE ${GRAPHS_LIB})
# Your stuff...
```
