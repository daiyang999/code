# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.22

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
CMAKE_SOURCE_DIR = /home/daiyang/sylarhttp

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/daiyang/sylarhttp/build

# Include any dependencies generated for this target.
include CMakeFiles/sylar1.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/sylar1.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/sylar1.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/sylar1.dir/flags.make

CMakeFiles/sylar1.dir/sylar1.cpp.o: CMakeFiles/sylar1.dir/flags.make
CMakeFiles/sylar1.dir/sylar1.cpp.o: ../sylar1.cpp
CMakeFiles/sylar1.dir/sylar1.cpp.o: CMakeFiles/sylar1.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/daiyang/sylarhttp/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/sylar1.dir/sylar1.cpp.o"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/sylar1.dir/sylar1.cpp.o -MF CMakeFiles/sylar1.dir/sylar1.cpp.o.d -o CMakeFiles/sylar1.dir/sylar1.cpp.o -c /home/daiyang/sylarhttp/sylar1.cpp

CMakeFiles/sylar1.dir/sylar1.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/sylar1.dir/sylar1.cpp.i"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/daiyang/sylarhttp/sylar1.cpp > CMakeFiles/sylar1.dir/sylar1.cpp.i

CMakeFiles/sylar1.dir/sylar1.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/sylar1.dir/sylar1.cpp.s"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/daiyang/sylarhttp/sylar1.cpp -o CMakeFiles/sylar1.dir/sylar1.cpp.s

# Object files for target sylar1
sylar1_OBJECTS = \
"CMakeFiles/sylar1.dir/sylar1.cpp.o"

# External object files for target sylar1
sylar1_EXTERNAL_OBJECTS =

libsylar1.a: CMakeFiles/sylar1.dir/sylar1.cpp.o
libsylar1.a: CMakeFiles/sylar1.dir/build.make
libsylar1.a: CMakeFiles/sylar1.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/daiyang/sylarhttp/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX static library libsylar1.a"
	$(CMAKE_COMMAND) -P CMakeFiles/sylar1.dir/cmake_clean_target.cmake
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/sylar1.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/sylar1.dir/build: libsylar1.a
.PHONY : CMakeFiles/sylar1.dir/build

CMakeFiles/sylar1.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/sylar1.dir/cmake_clean.cmake
.PHONY : CMakeFiles/sylar1.dir/clean

CMakeFiles/sylar1.dir/depend:
	cd /home/daiyang/sylarhttp/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/daiyang/sylarhttp /home/daiyang/sylarhttp /home/daiyang/sylarhttp/build /home/daiyang/sylarhttp/build /home/daiyang/sylarhttp/build/CMakeFiles/sylar1.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/sylar1.dir/depend
