# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.14

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


# Remove some rules from gmake that .SUFFIXES does not remove.
SUFFIXES =

.SUFFIXES: .hpux_make_needs_suffix_list


# Suppress display of executed commands.
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
RM = /usr/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/Evan/Desktop/test/CPP_rtype_2019/server

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/Evan/Desktop/test/CPP_rtype_2019/server

# Include any dependencies generated for this target.
include CMakeFiles/r-type_server.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/r-type_server.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/r-type_server.dir/flags.make

CMakeFiles/r-type_server.dir/src/main.cpp.o: CMakeFiles/r-type_server.dir/flags.make
CMakeFiles/r-type_server.dir/src/main.cpp.o: src/main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/Evan/Desktop/test/CPP_rtype_2019/server/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/r-type_server.dir/src/main.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/r-type_server.dir/src/main.cpp.o -c /home/Evan/Desktop/test/CPP_rtype_2019/server/src/main.cpp

CMakeFiles/r-type_server.dir/src/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/r-type_server.dir/src/main.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/Evan/Desktop/test/CPP_rtype_2019/server/src/main.cpp > CMakeFiles/r-type_server.dir/src/main.cpp.i

CMakeFiles/r-type_server.dir/src/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/r-type_server.dir/src/main.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/Evan/Desktop/test/CPP_rtype_2019/server/src/main.cpp -o CMakeFiles/r-type_server.dir/src/main.cpp.s

# Object files for target r-type_server
r__type_server_OBJECTS = \
"CMakeFiles/r-type_server.dir/src/main.cpp.o"

# External object files for target r-type_server
r__type_server_EXTERNAL_OBJECTS =

r-type_server: CMakeFiles/r-type_server.dir/src/main.cpp.o
r-type_server: CMakeFiles/r-type_server.dir/build.make
r-type_server: CMakeFiles/r-type_server.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/Evan/Desktop/test/CPP_rtype_2019/server/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable r-type_server"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/r-type_server.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/r-type_server.dir/build: r-type_server

.PHONY : CMakeFiles/r-type_server.dir/build

CMakeFiles/r-type_server.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/r-type_server.dir/cmake_clean.cmake
.PHONY : CMakeFiles/r-type_server.dir/clean

CMakeFiles/r-type_server.dir/depend:
	cd /home/Evan/Desktop/test/CPP_rtype_2019/server && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/Evan/Desktop/test/CPP_rtype_2019/server /home/Evan/Desktop/test/CPP_rtype_2019/server /home/Evan/Desktop/test/CPP_rtype_2019/server /home/Evan/Desktop/test/CPP_rtype_2019/server /home/Evan/Desktop/test/CPP_rtype_2019/server/CMakeFiles/r-type_server.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/r-type_server.dir/depend

