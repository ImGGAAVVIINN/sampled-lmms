# Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
# file Copyright.txt or https://cmake.org/licensing for details.

cmake_minimum_required(VERSION 3.5)

file(MAKE_DIRECTORY
  "/home/ascend/git/sampled-lmms/plugins/VstBase/RemoteVstPlugin"
  "/home/ascend/git/sampled-lmms/build/plugins/VstBase/NativeLinuxRemoteVstPlugin64-prefix/src/NativeLinuxRemoteVstPlugin64-build"
  "/home/ascend/git/sampled-lmms/build/plugins/VstBase/NativeLinuxRemoteVstPlugin64-prefix"
  "/home/ascend/git/sampled-lmms/build/plugins/VstBase/NativeLinuxRemoteVstPlugin64-prefix/tmp"
  "/home/ascend/git/sampled-lmms/build/plugins/VstBase/NativeLinuxRemoteVstPlugin64-prefix/src/NativeLinuxRemoteVstPlugin64-stamp"
  "/home/ascend/git/sampled-lmms/build/plugins/VstBase/NativeLinuxRemoteVstPlugin64-prefix/src"
  "/home/ascend/git/sampled-lmms/build/plugins/VstBase/NativeLinuxRemoteVstPlugin64-prefix/src/NativeLinuxRemoteVstPlugin64-stamp"
)

set(configSubDirs )
foreach(subDir IN LISTS configSubDirs)
    file(MAKE_DIRECTORY "/home/ascend/git/sampled-lmms/build/plugins/VstBase/NativeLinuxRemoteVstPlugin64-prefix/src/NativeLinuxRemoteVstPlugin64-stamp/${subDir}")
endforeach()
if(cfgdir)
  file(MAKE_DIRECTORY "/home/ascend/git/sampled-lmms/build/plugins/VstBase/NativeLinuxRemoteVstPlugin64-prefix/src/NativeLinuxRemoteVstPlugin64-stamp${cfgdir}") # cfgdir has leading slash
endif()
