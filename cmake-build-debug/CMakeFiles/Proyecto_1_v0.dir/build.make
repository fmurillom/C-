# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.9

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
CMAKE_COMMAND = /opt/clion-2017.3.3/bin/cmake/bin/cmake

# The command to remove a file.
RM = /opt/clion-2017.3.3/bin/cmake/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/loop/CLionProjects/Proyecto_1_v0

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/loop/CLionProjects/Proyecto_1_v0/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/Proyecto_1_v0.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/Proyecto_1_v0.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/Proyecto_1_v0.dir/flags.make

CMakeFiles/Proyecto_1_v0.dir/source/memBlock.cpp.o: CMakeFiles/Proyecto_1_v0.dir/flags.make
CMakeFiles/Proyecto_1_v0.dir/source/memBlock.cpp.o: ../source/memBlock.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/loop/CLionProjects/Proyecto_1_v0/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/Proyecto_1_v0.dir/source/memBlock.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/Proyecto_1_v0.dir/source/memBlock.cpp.o -c /home/loop/CLionProjects/Proyecto_1_v0/source/memBlock.cpp

CMakeFiles/Proyecto_1_v0.dir/source/memBlock.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Proyecto_1_v0.dir/source/memBlock.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/loop/CLionProjects/Proyecto_1_v0/source/memBlock.cpp > CMakeFiles/Proyecto_1_v0.dir/source/memBlock.cpp.i

CMakeFiles/Proyecto_1_v0.dir/source/memBlock.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Proyecto_1_v0.dir/source/memBlock.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/loop/CLionProjects/Proyecto_1_v0/source/memBlock.cpp -o CMakeFiles/Proyecto_1_v0.dir/source/memBlock.cpp.s

CMakeFiles/Proyecto_1_v0.dir/source/memBlock.cpp.o.requires:

.PHONY : CMakeFiles/Proyecto_1_v0.dir/source/memBlock.cpp.o.requires

CMakeFiles/Proyecto_1_v0.dir/source/memBlock.cpp.o.provides: CMakeFiles/Proyecto_1_v0.dir/source/memBlock.cpp.o.requires
	$(MAKE) -f CMakeFiles/Proyecto_1_v0.dir/build.make CMakeFiles/Proyecto_1_v0.dir/source/memBlock.cpp.o.provides.build
.PHONY : CMakeFiles/Proyecto_1_v0.dir/source/memBlock.cpp.o.provides

CMakeFiles/Proyecto_1_v0.dir/source/memBlock.cpp.o.provides.build: CMakeFiles/Proyecto_1_v0.dir/source/memBlock.cpp.o


CMakeFiles/Proyecto_1_v0.dir/sintaxys/mainS.cpp.o: CMakeFiles/Proyecto_1_v0.dir/flags.make
CMakeFiles/Proyecto_1_v0.dir/sintaxys/mainS.cpp.o: ../sintaxys/mainS.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/loop/CLionProjects/Proyecto_1_v0/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/Proyecto_1_v0.dir/sintaxys/mainS.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/Proyecto_1_v0.dir/sintaxys/mainS.cpp.o -c /home/loop/CLionProjects/Proyecto_1_v0/sintaxys/mainS.cpp

CMakeFiles/Proyecto_1_v0.dir/sintaxys/mainS.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Proyecto_1_v0.dir/sintaxys/mainS.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/loop/CLionProjects/Proyecto_1_v0/sintaxys/mainS.cpp > CMakeFiles/Proyecto_1_v0.dir/sintaxys/mainS.cpp.i

CMakeFiles/Proyecto_1_v0.dir/sintaxys/mainS.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Proyecto_1_v0.dir/sintaxys/mainS.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/loop/CLionProjects/Proyecto_1_v0/sintaxys/mainS.cpp -o CMakeFiles/Proyecto_1_v0.dir/sintaxys/mainS.cpp.s

CMakeFiles/Proyecto_1_v0.dir/sintaxys/mainS.cpp.o.requires:

.PHONY : CMakeFiles/Proyecto_1_v0.dir/sintaxys/mainS.cpp.o.requires

CMakeFiles/Proyecto_1_v0.dir/sintaxys/mainS.cpp.o.provides: CMakeFiles/Proyecto_1_v0.dir/sintaxys/mainS.cpp.o.requires
	$(MAKE) -f CMakeFiles/Proyecto_1_v0.dir/build.make CMakeFiles/Proyecto_1_v0.dir/sintaxys/mainS.cpp.o.provides.build
.PHONY : CMakeFiles/Proyecto_1_v0.dir/sintaxys/mainS.cpp.o.provides

CMakeFiles/Proyecto_1_v0.dir/sintaxys/mainS.cpp.o.provides.build: CMakeFiles/Proyecto_1_v0.dir/sintaxys/mainS.cpp.o


CMakeFiles/Proyecto_1_v0.dir/source/Scoope.cpp.o: CMakeFiles/Proyecto_1_v0.dir/flags.make
CMakeFiles/Proyecto_1_v0.dir/source/Scoope.cpp.o: ../source/Scoope.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/loop/CLionProjects/Proyecto_1_v0/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/Proyecto_1_v0.dir/source/Scoope.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/Proyecto_1_v0.dir/source/Scoope.cpp.o -c /home/loop/CLionProjects/Proyecto_1_v0/source/Scoope.cpp

CMakeFiles/Proyecto_1_v0.dir/source/Scoope.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Proyecto_1_v0.dir/source/Scoope.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/loop/CLionProjects/Proyecto_1_v0/source/Scoope.cpp > CMakeFiles/Proyecto_1_v0.dir/source/Scoope.cpp.i

CMakeFiles/Proyecto_1_v0.dir/source/Scoope.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Proyecto_1_v0.dir/source/Scoope.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/loop/CLionProjects/Proyecto_1_v0/source/Scoope.cpp -o CMakeFiles/Proyecto_1_v0.dir/source/Scoope.cpp.s

CMakeFiles/Proyecto_1_v0.dir/source/Scoope.cpp.o.requires:

.PHONY : CMakeFiles/Proyecto_1_v0.dir/source/Scoope.cpp.o.requires

CMakeFiles/Proyecto_1_v0.dir/source/Scoope.cpp.o.provides: CMakeFiles/Proyecto_1_v0.dir/source/Scoope.cpp.o.requires
	$(MAKE) -f CMakeFiles/Proyecto_1_v0.dir/build.make CMakeFiles/Proyecto_1_v0.dir/source/Scoope.cpp.o.provides.build
.PHONY : CMakeFiles/Proyecto_1_v0.dir/source/Scoope.cpp.o.provides

CMakeFiles/Proyecto_1_v0.dir/source/Scoope.cpp.o.provides.build: CMakeFiles/Proyecto_1_v0.dir/source/Scoope.cpp.o


CMakeFiles/Proyecto_1_v0.dir/main.cpp.o: CMakeFiles/Proyecto_1_v0.dir/flags.make
CMakeFiles/Proyecto_1_v0.dir/main.cpp.o: ../main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/loop/CLionProjects/Proyecto_1_v0/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/Proyecto_1_v0.dir/main.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/Proyecto_1_v0.dir/main.cpp.o -c /home/loop/CLionProjects/Proyecto_1_v0/main.cpp

CMakeFiles/Proyecto_1_v0.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Proyecto_1_v0.dir/main.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/loop/CLionProjects/Proyecto_1_v0/main.cpp > CMakeFiles/Proyecto_1_v0.dir/main.cpp.i

CMakeFiles/Proyecto_1_v0.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Proyecto_1_v0.dir/main.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/loop/CLionProjects/Proyecto_1_v0/main.cpp -o CMakeFiles/Proyecto_1_v0.dir/main.cpp.s

CMakeFiles/Proyecto_1_v0.dir/main.cpp.o.requires:

.PHONY : CMakeFiles/Proyecto_1_v0.dir/main.cpp.o.requires

CMakeFiles/Proyecto_1_v0.dir/main.cpp.o.provides: CMakeFiles/Proyecto_1_v0.dir/main.cpp.o.requires
	$(MAKE) -f CMakeFiles/Proyecto_1_v0.dir/build.make CMakeFiles/Proyecto_1_v0.dir/main.cpp.o.provides.build
.PHONY : CMakeFiles/Proyecto_1_v0.dir/main.cpp.o.provides

CMakeFiles/Proyecto_1_v0.dir/main.cpp.o.provides.build: CMakeFiles/Proyecto_1_v0.dir/main.cpp.o


# Object files for target Proyecto_1_v0
Proyecto_1_v0_OBJECTS = \
"CMakeFiles/Proyecto_1_v0.dir/source/memBlock.cpp.o" \
"CMakeFiles/Proyecto_1_v0.dir/sintaxys/mainS.cpp.o" \
"CMakeFiles/Proyecto_1_v0.dir/source/Scoope.cpp.o" \
"CMakeFiles/Proyecto_1_v0.dir/main.cpp.o"

# External object files for target Proyecto_1_v0
Proyecto_1_v0_EXTERNAL_OBJECTS =

Proyecto_1_v0: CMakeFiles/Proyecto_1_v0.dir/source/memBlock.cpp.o
Proyecto_1_v0: CMakeFiles/Proyecto_1_v0.dir/sintaxys/mainS.cpp.o
Proyecto_1_v0: CMakeFiles/Proyecto_1_v0.dir/source/Scoope.cpp.o
Proyecto_1_v0: CMakeFiles/Proyecto_1_v0.dir/main.cpp.o
Proyecto_1_v0: CMakeFiles/Proyecto_1_v0.dir/build.make
Proyecto_1_v0: CMakeFiles/Proyecto_1_v0.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/loop/CLionProjects/Proyecto_1_v0/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Linking CXX executable Proyecto_1_v0"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/Proyecto_1_v0.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/Proyecto_1_v0.dir/build: Proyecto_1_v0

.PHONY : CMakeFiles/Proyecto_1_v0.dir/build

CMakeFiles/Proyecto_1_v0.dir/requires: CMakeFiles/Proyecto_1_v0.dir/source/memBlock.cpp.o.requires
CMakeFiles/Proyecto_1_v0.dir/requires: CMakeFiles/Proyecto_1_v0.dir/sintaxys/mainS.cpp.o.requires
CMakeFiles/Proyecto_1_v0.dir/requires: CMakeFiles/Proyecto_1_v0.dir/source/Scoope.cpp.o.requires
CMakeFiles/Proyecto_1_v0.dir/requires: CMakeFiles/Proyecto_1_v0.dir/main.cpp.o.requires

.PHONY : CMakeFiles/Proyecto_1_v0.dir/requires

CMakeFiles/Proyecto_1_v0.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/Proyecto_1_v0.dir/cmake_clean.cmake
.PHONY : CMakeFiles/Proyecto_1_v0.dir/clean

CMakeFiles/Proyecto_1_v0.dir/depend:
	cd /home/loop/CLionProjects/Proyecto_1_v0/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/loop/CLionProjects/Proyecto_1_v0 /home/loop/CLionProjects/Proyecto_1_v0 /home/loop/CLionProjects/Proyecto_1_v0/cmake-build-debug /home/loop/CLionProjects/Proyecto_1_v0/cmake-build-debug /home/loop/CLionProjects/Proyecto_1_v0/cmake-build-debug/CMakeFiles/Proyecto_1_v0.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/Proyecto_1_v0.dir/depend
