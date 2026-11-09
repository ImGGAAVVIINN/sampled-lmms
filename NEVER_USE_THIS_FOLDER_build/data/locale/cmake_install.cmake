# Install script for directory: /home/ascend/git/sampled-lmms/data/locale

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
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/lmms/locale" TYPE FILE FILES
    "/home/ascend/git/sampled-lmms/data/locale/ar.qm"
    "/home/ascend/git/sampled-lmms/data/locale/bs.qm"
    "/home/ascend/git/sampled-lmms/data/locale/ca.qm"
    "/home/ascend/git/sampled-lmms/data/locale/cs.qm"
    "/home/ascend/git/sampled-lmms/data/locale/de.qm"
    "/home/ascend/git/sampled-lmms/data/locale/el.qm"
    "/home/ascend/git/sampled-lmms/data/locale/en.qm"
    "/home/ascend/git/sampled-lmms/data/locale/eo.qm"
    "/home/ascend/git/sampled-lmms/data/locale/es.qm"
    "/home/ascend/git/sampled-lmms/data/locale/eu.qm"
    "/home/ascend/git/sampled-lmms/data/locale/fa.qm"
    "/home/ascend/git/sampled-lmms/data/locale/fi.qm"
    "/home/ascend/git/sampled-lmms/data/locale/fr.qm"
    "/home/ascend/git/sampled-lmms/data/locale/gl.qm"
    "/home/ascend/git/sampled-lmms/data/locale/he.qm"
    "/home/ascend/git/sampled-lmms/data/locale/hi.qm"
    "/home/ascend/git/sampled-lmms/data/locale/hu_HU.qm"
    "/home/ascend/git/sampled-lmms/data/locale/id.qm"
    "/home/ascend/git/sampled-lmms/data/locale/it.qm"
    "/home/ascend/git/sampled-lmms/data/locale/ja.qm"
    "/home/ascend/git/sampled-lmms/data/locale/ka.qm"
    "/home/ascend/git/sampled-lmms/data/locale/ko.qm"
    "/home/ascend/git/sampled-lmms/data/locale/lo.qm"
    "/home/ascend/git/sampled-lmms/data/locale/ms_MY.qm"
    "/home/ascend/git/sampled-lmms/data/locale/nb.qm"
    "/home/ascend/git/sampled-lmms/data/locale/nl.qm"
    "/home/ascend/git/sampled-lmms/data/locale/oc.qm"
    "/home/ascend/git/sampled-lmms/data/locale/pl.qm"
    "/home/ascend/git/sampled-lmms/data/locale/pt.qm"
    "/home/ascend/git/sampled-lmms/data/locale/ro.qm"
    "/home/ascend/git/sampled-lmms/data/locale/ru.qm"
    "/home/ascend/git/sampled-lmms/data/locale/sl.qm"
    "/home/ascend/git/sampled-lmms/data/locale/sr.qm"
    "/home/ascend/git/sampled-lmms/data/locale/sv.qm"
    "/home/ascend/git/sampled-lmms/data/locale/tl.qm"
    "/home/ascend/git/sampled-lmms/data/locale/tr.qm"
    "/home/ascend/git/sampled-lmms/data/locale/uk.qm"
    "/home/ascend/git/sampled-lmms/data/locale/zh_CN.qm"
    "/home/ascend/git/sampled-lmms/data/locale/zh_TW.qm"
    )
endif()

