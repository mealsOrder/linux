# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.25

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:

#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:

# Disable VCS-based implicit rules.
% : %,v

# Disable VCS-based implicit rules.
% : RCS/%

# Disable VCS-based implicit rules.
% : RCS/%,v

# Disable VCS-based implicit rules.
% : SCCS/s.%

# Disable VCS-based implicit rules.
% : s.%

.SUFFIXES: .hpux_make_needs_suffix_list

# Command-line flag to silence nested $(MAKE).
$(VERBOSE)MAKESILENT = -s

#Suppress display of executed commands.
$(VERBOSE).SILENT:

# A target that is always out of date.
cmake_force:
.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/jyj/workspace/rtp/RTSP_TUTORIAL

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/jyj/workspace/rtp/RTSP_TUTORIAL/build

# Include any dependencies generated for this target.
include CMakeFiles/rtsp_client.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/rtsp_client.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/rtsp_client.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/rtsp_client.dir/flags.make

CMakeFiles/rtsp_client.dir/example/example_client.cpp.o: CMakeFiles/rtsp_client.dir/flags.make
CMakeFiles/rtsp_client.dir/example/example_client.cpp.o: /home/jyj/workspace/rtp/RTSP_TUTORIAL/example/example_client.cpp
CMakeFiles/rtsp_client.dir/example/example_client.cpp.o: CMakeFiles/rtsp_client.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/jyj/workspace/rtp/RTSP_TUTORIAL/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/rtsp_client.dir/example/example_client.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/rtsp_client.dir/example/example_client.cpp.o -MF CMakeFiles/rtsp_client.dir/example/example_client.cpp.o.d -o CMakeFiles/rtsp_client.dir/example/example_client.cpp.o -c /home/jyj/workspace/rtp/RTSP_TUTORIAL/example/example_client.cpp

CMakeFiles/rtsp_client.dir/example/example_client.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/rtsp_client.dir/example/example_client.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/jyj/workspace/rtp/RTSP_TUTORIAL/example/example_client.cpp > CMakeFiles/rtsp_client.dir/example/example_client.cpp.i

CMakeFiles/rtsp_client.dir/example/example_client.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/rtsp_client.dir/example/example_client.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/jyj/workspace/rtp/RTSP_TUTORIAL/example/example_client.cpp -o CMakeFiles/rtsp_client.dir/example/example_client.cpp.s

# Object files for target rtsp_client
rtsp_client_OBJECTS = \
"CMakeFiles/rtsp_client.dir/example/example_client.cpp.o"

# External object files for target rtsp_client
rtsp_client_EXTERNAL_OBJECTS =

rtsp_client: CMakeFiles/rtsp_client.dir/example/example_client.cpp.o
rtsp_client: CMakeFiles/rtsp_client.dir/build.make
rtsp_client: /usr/local/lib/libopencv_gapi.so.4.10.0
rtsp_client: /usr/local/lib/libopencv_highgui.so.4.10.0
rtsp_client: /usr/local/lib/libopencv_ml.so.4.10.0
rtsp_client: /usr/local/lib/libopencv_objdetect.so.4.10.0
rtsp_client: /usr/local/lib/libopencv_photo.so.4.10.0
rtsp_client: /usr/local/lib/libopencv_stitching.so.4.10.0
rtsp_client: /usr/local/lib/libopencv_video.so.4.10.0
rtsp_client: /usr/local/lib/libopencv_videoio.so.4.10.0
rtsp_client: /usr/local/lib/libopencv_imgcodecs.so.4.10.0
rtsp_client: /usr/local/lib/libopencv_dnn.so.4.10.0
rtsp_client: /usr/local/lib/libopencv_calib3d.so.4.10.0
rtsp_client: /usr/local/lib/libopencv_features2d.so.4.10.0
rtsp_client: /usr/local/lib/libopencv_flann.so.4.10.0
rtsp_client: /usr/local/lib/libopencv_imgproc.so.4.10.0
rtsp_client: /usr/local/lib/libopencv_core.so.4.10.0
rtsp_client: CMakeFiles/rtsp_client.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/jyj/workspace/rtp/RTSP_TUTORIAL/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable rtsp_client"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/rtsp_client.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/rtsp_client.dir/build: rtsp_client
.PHONY : CMakeFiles/rtsp_client.dir/build

CMakeFiles/rtsp_client.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/rtsp_client.dir/cmake_clean.cmake
.PHONY : CMakeFiles/rtsp_client.dir/clean

CMakeFiles/rtsp_client.dir/depend:
	cd /home/jyj/workspace/rtp/RTSP_TUTORIAL/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/jyj/workspace/rtp/RTSP_TUTORIAL /home/jyj/workspace/rtp/RTSP_TUTORIAL /home/jyj/workspace/rtp/RTSP_TUTORIAL/build /home/jyj/workspace/rtp/RTSP_TUTORIAL/build /home/jyj/workspace/rtp/RTSP_TUTORIAL/build/CMakeFiles/rtsp_client.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/rtsp_client.dir/depend

