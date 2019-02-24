# Install script for directory: /Users/Cyro/CSCI4611/repo-chakx011/dev/SoupCan

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "/Users/Cyro/CSCI4611/repo-chakx011/")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "Release")
  endif()
  message(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
endif()

# Set the component getting installed.
if(NOT CMAKE_INSTALL_COMPONENT)
  if(COMPONENT)
    message(STATUS "Install component: \"${COMPONENT}\"")
    set(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  else()
    set(CMAKE_INSTALL_COMPONENT)
  endif()
endif()

# Is this installation the result of a crosscompile?
if(NOT DEFINED CMAKE_CROSSCOMPILING)
  set(CMAKE_CROSSCOMPILING "FALSE")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  if("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Dd][Ee][Bb][Uu][Gg])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/bin" TYPE EXECUTABLE FILES "/Users/Cyro/CSCI4611/repo-chakx011/dev/SoupCan/build/Debug/example")
    if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/example" AND
       NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/example")
      execute_process(COMMAND /usr/bin/install_name_tool
        -delete_rpath "/Users/Cyro/CSCI4611/repo-chakx011/lib"
        "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/example")
      execute_process(COMMAND /usr/bin/install_name_tool
        -add_rpath "/Users/Cyro/CSCI4611/repo-chakx011//lib"
        "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/example")
      execute_process(COMMAND /usr/bin/install_name_tool
        -add_rpath "/Users/Cyro/CSCI4611/repo-chakx011/lib"
        "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/example")
      if(CMAKE_INSTALL_DO_STRIP)
        execute_process(COMMAND "/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/strip" "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/example")
      endif()
    endif()
  elseif("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Rr][Ee][Ll][Ee][Aa][Ss][Ee])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/bin" TYPE EXECUTABLE FILES "/Users/Cyro/CSCI4611/repo-chakx011/dev/SoupCan/build/Release/example")
    if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/example" AND
       NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/example")
      execute_process(COMMAND /usr/bin/install_name_tool
        -delete_rpath "/Users/Cyro/CSCI4611/repo-chakx011/lib"
        "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/example")
      execute_process(COMMAND /usr/bin/install_name_tool
        -add_rpath "/Users/Cyro/CSCI4611/repo-chakx011//lib"
        "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/example")
      execute_process(COMMAND /usr/bin/install_name_tool
        -add_rpath "/Users/Cyro/CSCI4611/repo-chakx011/lib"
        "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/example")
      if(CMAKE_INSTALL_DO_STRIP)
        execute_process(COMMAND "/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/strip" "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/example")
      endif()
    endif()
  elseif("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Mm][Ii][Nn][Ss][Ii][Zz][Ee][Rr][Ee][Ll])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/bin" TYPE EXECUTABLE FILES "/Users/Cyro/CSCI4611/repo-chakx011/dev/SoupCan/build/MinSizeRel/example")
    if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/example" AND
       NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/example")
      execute_process(COMMAND /usr/bin/install_name_tool
        -delete_rpath "/Users/Cyro/CSCI4611/repo-chakx011/lib"
        "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/example")
      execute_process(COMMAND /usr/bin/install_name_tool
        -add_rpath "/Users/Cyro/CSCI4611/repo-chakx011//lib"
        "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/example")
      execute_process(COMMAND /usr/bin/install_name_tool
        -add_rpath "/Users/Cyro/CSCI4611/repo-chakx011/lib"
        "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/example")
      if(CMAKE_INSTALL_DO_STRIP)
        execute_process(COMMAND "/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/strip" "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/example")
      endif()
    endif()
  elseif("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Rr][Ee][Ll][Ww][Ii][Tt][Hh][Dd][Ee][Bb][Ii][Nn][Ff][Oo])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/bin" TYPE EXECUTABLE FILES "/Users/Cyro/CSCI4611/repo-chakx011/dev/SoupCan/build/RelWithDebInfo/example")
    if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/example" AND
       NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/example")
      execute_process(COMMAND /usr/bin/install_name_tool
        -delete_rpath "/Users/Cyro/CSCI4611/repo-chakx011/lib"
        "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/example")
      execute_process(COMMAND /usr/bin/install_name_tool
        -add_rpath "/Users/Cyro/CSCI4611/repo-chakx011//lib"
        "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/example")
      execute_process(COMMAND /usr/bin/install_name_tool
        -add_rpath "/Users/Cyro/CSCI4611/repo-chakx011/lib"
        "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/example")
      if(CMAKE_INSTALL_DO_STRIP)
        execute_process(COMMAND "/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/strip" "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/example")
      endif()
    endif()
  endif()
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  list(APPEND CMAKE_ABSOLUTE_DESTINATION_FILES
   "/Users/Cyro/CSCI4611/repo-chakx011//share/example/data/")
  if(CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(WARNING "ABSOLUTE path INSTALL DESTINATION : ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  if(CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(FATAL_ERROR "ABSOLUTE path INSTALL DESTINATION forbidden (by caller): ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
file(INSTALL DESTINATION "/Users/Cyro/CSCI4611/repo-chakx011//share/example/data" TYPE DIRECTORY FILES "/Users/Cyro/CSCI4611/repo-chakx011/dev/SoupCan/data/")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  list(APPEND CMAKE_ABSOLUTE_DESTINATION_FILES
   "/Users/Cyro/CSCI4611/repo-chakx011//share/example/shaders/")
  if(CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(WARNING "ABSOLUTE path INSTALL DESTINATION : ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  if(CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(FATAL_ERROR "ABSOLUTE path INSTALL DESTINATION forbidden (by caller): ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
file(INSTALL DESTINATION "/Users/Cyro/CSCI4611/repo-chakx011//share/example/shaders" TYPE DIRECTORY FILES "/Users/Cyro/CSCI4611/repo-chakx011/dev/SoupCan/shaders/")
endif()

if(CMAKE_INSTALL_COMPONENT)
  set(CMAKE_INSTALL_MANIFEST "install_manifest_${CMAKE_INSTALL_COMPONENT}.txt")
else()
  set(CMAKE_INSTALL_MANIFEST "install_manifest.txt")
endif()

string(REPLACE ";" "\n" CMAKE_INSTALL_MANIFEST_CONTENT
       "${CMAKE_INSTALL_MANIFEST_FILES}")
file(WRITE "/Users/Cyro/CSCI4611/repo-chakx011/dev/SoupCan/build/${CMAKE_INSTALL_MANIFEST}"
     "${CMAKE_INSTALL_MANIFEST_CONTENT}")
