# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Release")
  file(REMOVE_RECURSE
  "CMakeFiles\\GolybkovChat_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\GolybkovChat_autogen.dir\\ParseCache.txt"
  "CMakeFiles\\ws2_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\ws2_autogen.dir\\ParseCache.txt"
  "CMakeFiles\\wstd_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\wstd_autogen.dir\\ParseCache.txt"
  "GolybkovChat_autogen"
  "ws2_autogen"
  "wstd_autogen"
  )
endif()
