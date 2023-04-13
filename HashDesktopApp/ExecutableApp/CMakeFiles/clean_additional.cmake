# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles\\HashGUIApp_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\HashGUIApp_autogen.dir\\ParseCache.txt"
  "HashGUIApp_autogen"
  )
endif()
