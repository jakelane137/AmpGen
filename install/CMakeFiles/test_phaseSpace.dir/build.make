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
CMAKE_SOURCE_DIR = /home/jlane/Documents/ampGen

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/jlane/Documents/ampGen/install

# Include any dependencies generated for this target.
include CMakeFiles/test_phaseSpace.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/test_phaseSpace.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/test_phaseSpace.dir/flags.make

CMakeFiles/test_phaseSpace.dir/test/test_phaseSpace.cpp.o: CMakeFiles/test_phaseSpace.dir/flags.make
CMakeFiles/test_phaseSpace.dir/test/test_phaseSpace.cpp.o: ../test/test_phaseSpace.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/jlane/Documents/ampGen/install/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/test_phaseSpace.dir/test/test_phaseSpace.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/test_phaseSpace.dir/test/test_phaseSpace.cpp.o -c /home/jlane/Documents/ampGen/test/test_phaseSpace.cpp

CMakeFiles/test_phaseSpace.dir/test/test_phaseSpace.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/test_phaseSpace.dir/test/test_phaseSpace.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/jlane/Documents/ampGen/test/test_phaseSpace.cpp > CMakeFiles/test_phaseSpace.dir/test/test_phaseSpace.cpp.i

CMakeFiles/test_phaseSpace.dir/test/test_phaseSpace.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/test_phaseSpace.dir/test/test_phaseSpace.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/jlane/Documents/ampGen/test/test_phaseSpace.cpp -o CMakeFiles/test_phaseSpace.dir/test/test_phaseSpace.cpp.s

# Object files for target test_phaseSpace
test_phaseSpace_OBJECTS = \
"CMakeFiles/test_phaseSpace.dir/test/test_phaseSpace.cpp.o"

# External object files for target test_phaseSpace
test_phaseSpace_EXTERNAL_OBJECTS =

bin/test/test_phaseSpace: CMakeFiles/test_phaseSpace.dir/test/test_phaseSpace.cpp.o
bin/test/test_phaseSpace: CMakeFiles/test_phaseSpace.dir/build.make
bin/test/test_phaseSpace: /usr/lib64/libboost_unit_test_framework.so
bin/test/test_phaseSpace: lib/libAmpGen.so
bin/test/test_phaseSpace: /usr/lib64/root/libCore.so
bin/test/test_phaseSpace: /usr/lib64/root/libImt.so
bin/test/test_phaseSpace: /usr/lib64/root/libRIO.so
bin/test/test_phaseSpace: /usr/lib64/root/libNet.so
bin/test/test_phaseSpace: /usr/lib64/root/libHist.so
bin/test/test_phaseSpace: /usr/lib64/root/libGraf.so
bin/test/test_phaseSpace: /usr/lib64/root/libGraf3d.so
bin/test/test_phaseSpace: /usr/lib64/root/libGpad.so
bin/test/test_phaseSpace: /usr/lib64/root/libROOTDataFrame.so
bin/test/test_phaseSpace: /usr/lib64/root/libROOTVecOps.so
bin/test/test_phaseSpace: /usr/lib64/root/libTree.so
bin/test/test_phaseSpace: /usr/lib64/root/libTreePlayer.so
bin/test/test_phaseSpace: /usr/lib64/root/libRint.so
bin/test/test_phaseSpace: /usr/lib64/root/libPostscript.so
bin/test/test_phaseSpace: /usr/lib64/root/libMatrix.so
bin/test/test_phaseSpace: /usr/lib64/root/libPhysics.so
bin/test/test_phaseSpace: /usr/lib64/root/libMathCore.so
bin/test/test_phaseSpace: /usr/lib64/root/libThread.so
bin/test/test_phaseSpace: /usr/lib64/root/libMultiProc.so
bin/test/test_phaseSpace: /usr/lib64/root/libMathMore.so
bin/test/test_phaseSpace: /usr/lib64/root/libMinuit2.so.6.16.00
bin/test/test_phaseSpace: /usr/lib64/root/libHist.so.6.16.00
bin/test/test_phaseSpace: /usr/lib64/root/libMatrix.so.6.16.00
bin/test/test_phaseSpace: /usr/lib64/root/libMathCore.so.6.16.00
bin/test/test_phaseSpace: /usr/lib64/root/libImt.so.6.16.00
bin/test/test_phaseSpace: /usr/lib64/libtbb.so
bin/test/test_phaseSpace: /usr/lib64/root/libRIO.so.6.16.00
bin/test/test_phaseSpace: /usr/lib64/root/libThread.so.6.16.00
bin/test/test_phaseSpace: /usr/lib64/root/libCore.so.6.16.00
bin/test/test_phaseSpace: /usr/lib/gcc/x86_64-redhat-linux/9/libgomp.so
bin/test/test_phaseSpace: /usr/lib64/libpthread.so
bin/test/test_phaseSpace: CMakeFiles/test_phaseSpace.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/jlane/Documents/ampGen/install/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable bin/test/test_phaseSpace"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/test_phaseSpace.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/test_phaseSpace.dir/build: bin/test/test_phaseSpace

.PHONY : CMakeFiles/test_phaseSpace.dir/build

CMakeFiles/test_phaseSpace.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/test_phaseSpace.dir/cmake_clean.cmake
.PHONY : CMakeFiles/test_phaseSpace.dir/clean

CMakeFiles/test_phaseSpace.dir/depend:
	cd /home/jlane/Documents/ampGen/install && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/jlane/Documents/ampGen /home/jlane/Documents/ampGen /home/jlane/Documents/ampGen/install /home/jlane/Documents/ampGen/install /home/jlane/Documents/ampGen/install/CMakeFiles/test_phaseSpace.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/test_phaseSpace.dir/depend

