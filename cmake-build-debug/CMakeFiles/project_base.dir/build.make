# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.17

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
CMAKE_COMMAND = /snap/clion/138/bin/cmake/linux/bin/cmake

# The command to remove a file.
RM = /snap/clion/138/bin/cmake/linux/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/dzondzi/Desktop/grafa/rgproject

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/dzondzi/Desktop/grafa/rgproject/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/project_base.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/project_base.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/project_base.dir/flags.make

CMakeFiles/project_base.dir/src/Game.cpp.o: CMakeFiles/project_base.dir/flags.make
CMakeFiles/project_base.dir/src/Game.cpp.o: ../src/Game.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/dzondzi/Desktop/grafa/rgproject/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/project_base.dir/src/Game.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/project_base.dir/src/Game.cpp.o -c /home/dzondzi/Desktop/grafa/rgproject/src/Game.cpp

CMakeFiles/project_base.dir/src/Game.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/project_base.dir/src/Game.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/dzondzi/Desktop/grafa/rgproject/src/Game.cpp > CMakeFiles/project_base.dir/src/Game.cpp.i

CMakeFiles/project_base.dir/src/Game.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/project_base.dir/src/Game.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/dzondzi/Desktop/grafa/rgproject/src/Game.cpp -o CMakeFiles/project_base.dir/src/Game.cpp.s

CMakeFiles/project_base.dir/src/LoadTextures.cpp.o: CMakeFiles/project_base.dir/flags.make
CMakeFiles/project_base.dir/src/LoadTextures.cpp.o: ../src/LoadTextures.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/dzondzi/Desktop/grafa/rgproject/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/project_base.dir/src/LoadTextures.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/project_base.dir/src/LoadTextures.cpp.o -c /home/dzondzi/Desktop/grafa/rgproject/src/LoadTextures.cpp

CMakeFiles/project_base.dir/src/LoadTextures.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/project_base.dir/src/LoadTextures.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/dzondzi/Desktop/grafa/rgproject/src/LoadTextures.cpp > CMakeFiles/project_base.dir/src/LoadTextures.cpp.i

CMakeFiles/project_base.dir/src/LoadTextures.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/project_base.dir/src/LoadTextures.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/dzondzi/Desktop/grafa/rgproject/src/LoadTextures.cpp -o CMakeFiles/project_base.dir/src/LoadTextures.cpp.s

CMakeFiles/project_base.dir/src/MatrixChanges1.cpp.o: CMakeFiles/project_base.dir/flags.make
CMakeFiles/project_base.dir/src/MatrixChanges1.cpp.o: ../src/MatrixChanges1.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/dzondzi/Desktop/grafa/rgproject/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/project_base.dir/src/MatrixChanges1.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/project_base.dir/src/MatrixChanges1.cpp.o -c /home/dzondzi/Desktop/grafa/rgproject/src/MatrixChanges1.cpp

CMakeFiles/project_base.dir/src/MatrixChanges1.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/project_base.dir/src/MatrixChanges1.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/dzondzi/Desktop/grafa/rgproject/src/MatrixChanges1.cpp > CMakeFiles/project_base.dir/src/MatrixChanges1.cpp.i

CMakeFiles/project_base.dir/src/MatrixChanges1.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/project_base.dir/src/MatrixChanges1.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/dzondzi/Desktop/grafa/rgproject/src/MatrixChanges1.cpp -o CMakeFiles/project_base.dir/src/MatrixChanges1.cpp.s

CMakeFiles/project_base.dir/src/RenderCube.cpp.o: CMakeFiles/project_base.dir/flags.make
CMakeFiles/project_base.dir/src/RenderCube.cpp.o: ../src/RenderCube.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/dzondzi/Desktop/grafa/rgproject/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/project_base.dir/src/RenderCube.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/project_base.dir/src/RenderCube.cpp.o -c /home/dzondzi/Desktop/grafa/rgproject/src/RenderCube.cpp

CMakeFiles/project_base.dir/src/RenderCube.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/project_base.dir/src/RenderCube.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/dzondzi/Desktop/grafa/rgproject/src/RenderCube.cpp > CMakeFiles/project_base.dir/src/RenderCube.cpp.i

CMakeFiles/project_base.dir/src/RenderCube.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/project_base.dir/src/RenderCube.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/dzondzi/Desktop/grafa/rgproject/src/RenderCube.cpp -o CMakeFiles/project_base.dir/src/RenderCube.cpp.s

CMakeFiles/project_base.dir/src/StartingCallbackInit.cpp.o: CMakeFiles/project_base.dir/flags.make
CMakeFiles/project_base.dir/src/StartingCallbackInit.cpp.o: ../src/StartingCallbackInit.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/dzondzi/Desktop/grafa/rgproject/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object CMakeFiles/project_base.dir/src/StartingCallbackInit.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/project_base.dir/src/StartingCallbackInit.cpp.o -c /home/dzondzi/Desktop/grafa/rgproject/src/StartingCallbackInit.cpp

CMakeFiles/project_base.dir/src/StartingCallbackInit.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/project_base.dir/src/StartingCallbackInit.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/dzondzi/Desktop/grafa/rgproject/src/StartingCallbackInit.cpp > CMakeFiles/project_base.dir/src/StartingCallbackInit.cpp.i

CMakeFiles/project_base.dir/src/StartingCallbackInit.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/project_base.dir/src/StartingCallbackInit.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/dzondzi/Desktop/grafa/rgproject/src/StartingCallbackInit.cpp -o CMakeFiles/project_base.dir/src/StartingCallbackInit.cpp.s

CMakeFiles/project_base.dir/src/StartingGlfwInit.cpp.o: CMakeFiles/project_base.dir/flags.make
CMakeFiles/project_base.dir/src/StartingGlfwInit.cpp.o: ../src/StartingGlfwInit.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/dzondzi/Desktop/grafa/rgproject/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building CXX object CMakeFiles/project_base.dir/src/StartingGlfwInit.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/project_base.dir/src/StartingGlfwInit.cpp.o -c /home/dzondzi/Desktop/grafa/rgproject/src/StartingGlfwInit.cpp

CMakeFiles/project_base.dir/src/StartingGlfwInit.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/project_base.dir/src/StartingGlfwInit.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/dzondzi/Desktop/grafa/rgproject/src/StartingGlfwInit.cpp > CMakeFiles/project_base.dir/src/StartingGlfwInit.cpp.i

CMakeFiles/project_base.dir/src/StartingGlfwInit.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/project_base.dir/src/StartingGlfwInit.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/dzondzi/Desktop/grafa/rgproject/src/StartingGlfwInit.cpp -o CMakeFiles/project_base.dir/src/StartingGlfwInit.cpp.s

CMakeFiles/project_base.dir/src/main.cpp.o: CMakeFiles/project_base.dir/flags.make
CMakeFiles/project_base.dir/src/main.cpp.o: ../src/main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/dzondzi/Desktop/grafa/rgproject/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Building CXX object CMakeFiles/project_base.dir/src/main.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/project_base.dir/src/main.cpp.o -c /home/dzondzi/Desktop/grafa/rgproject/src/main.cpp

CMakeFiles/project_base.dir/src/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/project_base.dir/src/main.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/dzondzi/Desktop/grafa/rgproject/src/main.cpp > CMakeFiles/project_base.dir/src/main.cpp.i

CMakeFiles/project_base.dir/src/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/project_base.dir/src/main.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/dzondzi/Desktop/grafa/rgproject/src/main.cpp -o CMakeFiles/project_base.dir/src/main.cpp.s

# Object files for target project_base
project_base_OBJECTS = \
"CMakeFiles/project_base.dir/src/Game.cpp.o" \
"CMakeFiles/project_base.dir/src/LoadTextures.cpp.o" \
"CMakeFiles/project_base.dir/src/MatrixChanges1.cpp.o" \
"CMakeFiles/project_base.dir/src/RenderCube.cpp.o" \
"CMakeFiles/project_base.dir/src/StartingCallbackInit.cpp.o" \
"CMakeFiles/project_base.dir/src/StartingGlfwInit.cpp.o" \
"CMakeFiles/project_base.dir/src/main.cpp.o"

# External object files for target project_base
project_base_EXTERNAL_OBJECTS =

../project_base: CMakeFiles/project_base.dir/src/Game.cpp.o
../project_base: CMakeFiles/project_base.dir/src/LoadTextures.cpp.o
../project_base: CMakeFiles/project_base.dir/src/MatrixChanges1.cpp.o
../project_base: CMakeFiles/project_base.dir/src/RenderCube.cpp.o
../project_base: CMakeFiles/project_base.dir/src/StartingCallbackInit.cpp.o
../project_base: CMakeFiles/project_base.dir/src/StartingGlfwInit.cpp.o
../project_base: CMakeFiles/project_base.dir/src/main.cpp.o
../project_base: CMakeFiles/project_base.dir/build.make
../project_base: /usr/lib/x86_64-linux-gnu/libglfw.so.3.3
../project_base: libs/glad/libglad.a
../project_base: libSTB_IMAGE.a
../project_base: libs/imgui/libimgui.a
../project_base: /usr/lib/x86_64-linux-gnu/libGLX.so
../project_base: /usr/lib/x86_64-linux-gnu/libOpenGL.so
../project_base: libs/glad/libglad.a
../project_base: CMakeFiles/project_base.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/dzondzi/Desktop/grafa/rgproject/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_8) "Linking CXX executable ../project_base"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/project_base.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/project_base.dir/build: ../project_base

.PHONY : CMakeFiles/project_base.dir/build

CMakeFiles/project_base.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/project_base.dir/cmake_clean.cmake
.PHONY : CMakeFiles/project_base.dir/clean

CMakeFiles/project_base.dir/depend:
	cd /home/dzondzi/Desktop/grafa/rgproject/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/dzondzi/Desktop/grafa/rgproject /home/dzondzi/Desktop/grafa/rgproject /home/dzondzi/Desktop/grafa/rgproject/cmake-build-debug /home/dzondzi/Desktop/grafa/rgproject/cmake-build-debug /home/dzondzi/Desktop/grafa/rgproject/cmake-build-debug/CMakeFiles/project_base.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/project_base.dir/depend

