# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles\\QtProject_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\QtProject_autogen.dir\\ParseCache.txt"
  "QtProject_autogen"
  )
endif()
