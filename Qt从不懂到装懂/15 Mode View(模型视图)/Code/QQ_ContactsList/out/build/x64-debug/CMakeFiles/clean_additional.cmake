# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles\\QQ_ContactsList_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\QQ_ContactsList_autogen.dir\\ParseCache.txt"
  "QQ_ContactsList_autogen"
  )
endif()
