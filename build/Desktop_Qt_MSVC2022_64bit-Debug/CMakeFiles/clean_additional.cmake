# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles\\GolybkovChat_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\GolybkovChat_autogen.dir\\ParseCache.txt"
  "GolybkovChat_autogen"
  )
endif()
