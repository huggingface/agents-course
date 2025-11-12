# CMakeLists.txt - ESP32-S3 Alexa Wake Word Project
cmake_minimum_required(VERSION 3.16)

# Set the components to include
set(EXTRA_COMPONENT_DIRS components)

include($ENV{IDF_PATH}/tools/cmake/project.cmake)
project(alexa_wakeword)
