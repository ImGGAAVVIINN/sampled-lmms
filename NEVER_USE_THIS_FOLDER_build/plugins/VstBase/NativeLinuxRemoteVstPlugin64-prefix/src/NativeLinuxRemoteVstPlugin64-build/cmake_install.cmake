# Install script for directory: /home/ascend/git/sampled-lmms/plugins/VstBase/RemoteVstPlugin

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "/usr/local")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "Debug")
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

# Install shared libraries without execute permission?
if(NOT DEFINED CMAKE_INSTALL_SO_NO_EXE)
  set(CMAKE_INSTALL_SO_NO_EXE "1")
endif()

# Is this installation the result of a crosscompile?
if(NOT DEFINED CMAKE_CROSSCOMPILING)
  set(CMAKE_CROSSCOMPILING "FALSE")
endif()

# Set default install directory permissions.
if(NOT DEFINED CMAKE_OBJDUMP)
  set(CMAKE_OBJDUMP "/usr/bin/objdump")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/lmms/NativeLinuxRemoteVstPlugin64" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/lmms/NativeLinuxRemoteVstPlugin64")
    file(RPATH_CHECK
         FILE "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/lmms/NativeLinuxRemoteVstPlugin64"
         RPATH "")
  endif()
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/lmms" TYPE EXECUTABLE FILES "/home/ascend/git/sampled-lmms/build/plugins/NativeLinuxRemoteVstPlugin64")
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/lmms/NativeLinuxRemoteVstPlugin64" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/lmms/NativeLinuxRemoteVstPlugin64")
    if(CMAKE_INSTALL_DO_STRIP)
      execute_process(COMMAND "/usr/bin/strip" "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/lmms/NativeLinuxRemoteVstPlugin64")
    endif()
  endif()
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  set("DEPLOY_FILES" "/home/ascend/git/sampled-lmms/build/plugins/NativeLinuxRemoteVstPlugin64")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  
		INCLUDE("/home/ascend/git/sampled-lmms/cmake/modules/InstallDependencies.cmake")

		INSTALL_DEPENDENCIES(
			FILES "${DEPLOY_FILES}"
			DESTINATION "lib/lmms/32"
			LIB_DIRS "/usr/lib/gcc/x86_64-linux-gnu/11;/usr/lib/x86_64-linux-gnu;/usr/lib;/lib/x86_64-linux-gnu;/lib;/usr/lib/gcc/x86_64-linux-gnu/11/bin;/usr/lib/gcc/x86_64-linux-gnu/11/lib;/usr/lib/gcc/x86_64-linux-gnu/11/../bin;/usr/lib/x86_64-linux-gnu/bin;/usr/lib/x86_64-linux-gnu/lib;/usr/lib/x86_64-linux-gnu/../bin;/usr/lib/bin;/usr/lib/lib;/usr/lib/../bin;/lib/x86_64-linux-gnu/bin;/lib/x86_64-linux-gnu/lib;/lib/x86_64-linux-gnu/../bin;/lib/bin;/lib/lib;/lib/../bin"
			SEARCH_PATHS ""
			INCLUDE_SYSTEM;IGNORE_LIBS_FILE;/home/ascend/git/sampled-lmms/build/plugins/VstBase/NativeLinuxRemoteVstPlugin64-prefix/src/NativeLinuxRemoteVstPlugin64-build/excludelist
		)
	
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for each subdirectory.
  include("/home/ascend/git/sampled-lmms/build/plugins/VstBase/NativeLinuxRemoteVstPlugin64-prefix/src/NativeLinuxRemoteVstPlugin64-build/common/cmake_install.cmake")

endif()

if(CMAKE_INSTALL_COMPONENT)
  set(CMAKE_INSTALL_MANIFEST "install_manifest_${CMAKE_INSTALL_COMPONENT}.txt")
else()
  set(CMAKE_INSTALL_MANIFEST "install_manifest.txt")
endif()

string(REPLACE ";" "\n" CMAKE_INSTALL_MANIFEST_CONTENT
       "${CMAKE_INSTALL_MANIFEST_FILES}")
file(WRITE "/home/ascend/git/sampled-lmms/build/plugins/VstBase/NativeLinuxRemoteVstPlugin64-prefix/src/NativeLinuxRemoteVstPlugin64-build/${CMAKE_INSTALL_MANIFEST}"
     "${CMAKE_INSTALL_MANIFEST_CONTENT}")
