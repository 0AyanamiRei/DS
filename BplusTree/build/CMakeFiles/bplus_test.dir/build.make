# CMAKE generated file: DO NOT EDIT!
# Generated by "MinGW Makefiles" Generator, CMake Version 3.29

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

SHELL = cmd.exe

# The CMake executable.
CMAKE_COMMAND = D:\CodeApp\VSCODE\CandC++4VS\cmake-3.29.2-windows-x86_64\bin\cmake.exe

# The command to remove a file.
RM = D:\CodeApp\VSCODE\CandC++4VS\cmake-3.29.2-windows-x86_64\bin\cmake.exe -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = D:\Project\bustub_dbms\cpp_test\DS\BplusTree

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = D:\Project\bustub_dbms\cpp_test\DS\BplusTree\build

# Include any dependencies generated for this target.
include CMakeFiles/bplus_test.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/bplus_test.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/bplus_test.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/bplus_test.dir/flags.make

CMakeFiles/bplus_test.dir/bplus_test.cpp.obj: CMakeFiles/bplus_test.dir/flags.make
CMakeFiles/bplus_test.dir/bplus_test.cpp.obj: D:/Project/bustub_dbms/cpp_test/DS/BplusTree/bplus_test.cpp
CMakeFiles/bplus_test.dir/bplus_test.cpp.obj: CMakeFiles/bplus_test.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=D:\Project\bustub_dbms\cpp_test\DS\BplusTree\build\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/bplus_test.dir/bplus_test.cpp.obj"
	D:\CodeApp\MinGW\MINGW\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/bplus_test.dir/bplus_test.cpp.obj -MF CMakeFiles\bplus_test.dir\bplus_test.cpp.obj.d -o CMakeFiles\bplus_test.dir\bplus_test.cpp.obj -c D:\Project\bustub_dbms\cpp_test\DS\BplusTree\bplus_test.cpp

CMakeFiles/bplus_test.dir/bplus_test.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/bplus_test.dir/bplus_test.cpp.i"
	D:\CodeApp\MinGW\MINGW\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E D:\Project\bustub_dbms\cpp_test\DS\BplusTree\bplus_test.cpp > CMakeFiles\bplus_test.dir\bplus_test.cpp.i

CMakeFiles/bplus_test.dir/bplus_test.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/bplus_test.dir/bplus_test.cpp.s"
	D:\CodeApp\MinGW\MINGW\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S D:\Project\bustub_dbms\cpp_test\DS\BplusTree\bplus_test.cpp -o CMakeFiles\bplus_test.dir\bplus_test.cpp.s

# Object files for target bplus_test
bplus_test_OBJECTS = \
"CMakeFiles/bplus_test.dir/bplus_test.cpp.obj"

# External object files for target bplus_test
bplus_test_EXTERNAL_OBJECTS =

bplus_test.exe: CMakeFiles/bplus_test.dir/bplus_test.cpp.obj
bplus_test.exe: CMakeFiles/bplus_test.dir/build.make
bplus_test.exe: CMakeFiles/bplus_test.dir/linkLibs.rsp
bplus_test.exe: CMakeFiles/bplus_test.dir/objects1.rsp
bplus_test.exe: CMakeFiles/bplus_test.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir=D:\Project\bustub_dbms\cpp_test\DS\BplusTree\build\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable bplus_test.exe"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\bplus_test.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/bplus_test.dir/build: bplus_test.exe
.PHONY : CMakeFiles/bplus_test.dir/build

CMakeFiles/bplus_test.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles\bplus_test.dir\cmake_clean.cmake
.PHONY : CMakeFiles/bplus_test.dir/clean

CMakeFiles/bplus_test.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" D:\Project\bustub_dbms\cpp_test\DS\BplusTree D:\Project\bustub_dbms\cpp_test\DS\BplusTree D:\Project\bustub_dbms\cpp_test\DS\BplusTree\build D:\Project\bustub_dbms\cpp_test\DS\BplusTree\build D:\Project\bustub_dbms\cpp_test\DS\BplusTree\build\CMakeFiles\bplus_test.dir\DependInfo.cmake "--color=$(COLOR)"
.PHONY : CMakeFiles/bplus_test.dir/depend

