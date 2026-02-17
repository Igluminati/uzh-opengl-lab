#!/bin/bash
cd ..
git clone https://github.com/microsoft/vcpkg.git
cd vcpkg


./bootstrap-vcpkg.sh
./vcpkg update
./vcpkg install glfw3 glew glm