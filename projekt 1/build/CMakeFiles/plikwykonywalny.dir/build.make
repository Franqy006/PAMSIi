# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.10

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
CMAKE_SOURCE_DIR = /home/a17sude/Desktop/PAMSI/proejkt

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/a17sude/Desktop/PAMSI/proejkt/build

# Include any dependencies generated for this target.
include CMakeFiles/plikwykonywalny.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/plikwykonywalny.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/plikwykonywalny.dir/flags.make

CMakeFiles/plikwykonywalny.dir/src/kupa.cpp.o: CMakeFiles/plikwykonywalny.dir/flags.make
CMakeFiles/plikwykonywalny.dir/src/kupa.cpp.o: ../src/kupa.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/a17sude/Desktop/PAMSI/proejkt/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/plikwykonywalny.dir/src/kupa.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/plikwykonywalny.dir/src/kupa.cpp.o -c /home/a17sude/Desktop/PAMSI/proejkt/src/kupa.cpp

CMakeFiles/plikwykonywalny.dir/src/kupa.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/plikwykonywalny.dir/src/kupa.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/a17sude/Desktop/PAMSI/proejkt/src/kupa.cpp > CMakeFiles/plikwykonywalny.dir/src/kupa.cpp.i

CMakeFiles/plikwykonywalny.dir/src/kupa.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/plikwykonywalny.dir/src/kupa.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/a17sude/Desktop/PAMSI/proejkt/src/kupa.cpp -o CMakeFiles/plikwykonywalny.dir/src/kupa.cpp.s

CMakeFiles/plikwykonywalny.dir/src/kupa.cpp.o.requires:

.PHONY : CMakeFiles/plikwykonywalny.dir/src/kupa.cpp.o.requires

CMakeFiles/plikwykonywalny.dir/src/kupa.cpp.o.provides: CMakeFiles/plikwykonywalny.dir/src/kupa.cpp.o.requires
	$(MAKE) -f CMakeFiles/plikwykonywalny.dir/build.make CMakeFiles/plikwykonywalny.dir/src/kupa.cpp.o.provides.build
.PHONY : CMakeFiles/plikwykonywalny.dir/src/kupa.cpp.o.provides

CMakeFiles/plikwykonywalny.dir/src/kupa.cpp.o.provides.build: CMakeFiles/plikwykonywalny.dir/src/kupa.cpp.o


CMakeFiles/plikwykonywalny.dir/src/main.cpp.o: CMakeFiles/plikwykonywalny.dir/flags.make
CMakeFiles/plikwykonywalny.dir/src/main.cpp.o: ../src/main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/a17sude/Desktop/PAMSI/proejkt/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/plikwykonywalny.dir/src/main.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/plikwykonywalny.dir/src/main.cpp.o -c /home/a17sude/Desktop/PAMSI/proejkt/src/main.cpp

CMakeFiles/plikwykonywalny.dir/src/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/plikwykonywalny.dir/src/main.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/a17sude/Desktop/PAMSI/proejkt/src/main.cpp > CMakeFiles/plikwykonywalny.dir/src/main.cpp.i

CMakeFiles/plikwykonywalny.dir/src/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/plikwykonywalny.dir/src/main.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/a17sude/Desktop/PAMSI/proejkt/src/main.cpp -o CMakeFiles/plikwykonywalny.dir/src/main.cpp.s

CMakeFiles/plikwykonywalny.dir/src/main.cpp.o.requires:

.PHONY : CMakeFiles/plikwykonywalny.dir/src/main.cpp.o.requires

CMakeFiles/plikwykonywalny.dir/src/main.cpp.o.provides: CMakeFiles/plikwykonywalny.dir/src/main.cpp.o.requires
	$(MAKE) -f CMakeFiles/plikwykonywalny.dir/build.make CMakeFiles/plikwykonywalny.dir/src/main.cpp.o.provides.build
.PHONY : CMakeFiles/plikwykonywalny.dir/src/main.cpp.o.provides

CMakeFiles/plikwykonywalny.dir/src/main.cpp.o.provides.build: CMakeFiles/plikwykonywalny.dir/src/main.cpp.o


# Object files for target plikwykonywalny
plikwykonywalny_OBJECTS = \
"CMakeFiles/plikwykonywalny.dir/src/kupa.cpp.o" \
"CMakeFiles/plikwykonywalny.dir/src/main.cpp.o"

# External object files for target plikwykonywalny
plikwykonywalny_EXTERNAL_OBJECTS =

plikwykonywalny: CMakeFiles/plikwykonywalny.dir/src/kupa.cpp.o
plikwykonywalny: CMakeFiles/plikwykonywalny.dir/src/main.cpp.o
plikwykonywalny: CMakeFiles/plikwykonywalny.dir/build.make
plikwykonywalny: CMakeFiles/plikwykonywalny.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/a17sude/Desktop/PAMSI/proejkt/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking CXX executable plikwykonywalny"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/plikwykonywalny.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/plikwykonywalny.dir/build: plikwykonywalny

.PHONY : CMakeFiles/plikwykonywalny.dir/build

CMakeFiles/plikwykonywalny.dir/requires: CMakeFiles/plikwykonywalny.dir/src/kupa.cpp.o.requires
CMakeFiles/plikwykonywalny.dir/requires: CMakeFiles/plikwykonywalny.dir/src/main.cpp.o.requires

.PHONY : CMakeFiles/plikwykonywalny.dir/requires

CMakeFiles/plikwykonywalny.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/plikwykonywalny.dir/cmake_clean.cmake
.PHONY : CMakeFiles/plikwykonywalny.dir/clean

CMakeFiles/plikwykonywalny.dir/depend:
	cd /home/a17sude/Desktop/PAMSI/proejkt/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/a17sude/Desktop/PAMSI/proejkt /home/a17sude/Desktop/PAMSI/proejkt /home/a17sude/Desktop/PAMSI/proejkt/build /home/a17sude/Desktop/PAMSI/proejkt/build /home/a17sude/Desktop/PAMSI/proejkt/build/CMakeFiles/plikwykonywalny.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/plikwykonywalny.dir/depend

