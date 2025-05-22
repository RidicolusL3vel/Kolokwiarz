# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles\\Testownik_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\Testownik_autogen.dir\\ParseCache.txt"
  "Testownik_autogen"
  )
endif()
