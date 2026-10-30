# Copyright (c) 2025 saker <sakertooth@gmail.com>
#
# Redistribution and use is allowed according to the terms of the New BSD license.
# For details see the accompanying COPYING-CMAKE-SCRIPTS file.

include(ImportedTargetHelpers)

find_package_config_mode_with_fallback(SoundTouch SoundTouch::soundtouch
	LIBRARY_NAMES "SoundTouch" "soundtouch" "libsoundtouch" "libsoundtouch-2"
	INCLUDE_NAMES "soundtouch/SoundTouch.h"
	PKG_CONFIG soundtouch
	PREFIX SoundTouch
)

determine_version_from_source(SoundTouch_VERSION SoundTouch::soundtouch [[
	#include <iostream>
	#include <string_view>
	#include "soundtouch/SoundTouch.h"

	auto main() -> int
	{
		// Version string has the format "name-version copyright"
		const auto version = std::string_view{SoundTouch::getVersionString()};
		const auto begin = version.find('-') + 1;
		const auto end = version.find(' ', begin);
		std::cout << version.substr(begin, end - begin);
	}
]])

include(FindPackageHandleStandardArgs)

find_package_handle_standard_args(SoundTouch
	REQUIRED_VARS SoundTouch_LIBRARY SoundTouch_INCLUDE_DIRS
	VERSION_VAR SoundTouch_VERSION
)