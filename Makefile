# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.14

# Default target executed when no arguments are given to make.
default_target: all

.PHONY : default_target

# Allow only one "make -f Makefile2" at a time, but pass parallelism.
.NOTPARALLEL:


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
CMAKE_COMMAND = /usr/bin/cmake.exe

# The command to remove a file.
RM = /usr/bin/cmake.exe -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /cygdrive/d/linuxDrive/wav_to_mp3

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /cygdrive/d/linuxDrive/wav_to_mp3

#=============================================================================
# Targets provided globally by CMake.

# Special rule for the target rebuild_cache
rebuild_cache:
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --cyan "Running CMake to regenerate build system..."
	/usr/bin/cmake.exe -S$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR)
.PHONY : rebuild_cache

# Special rule for the target rebuild_cache
rebuild_cache/fast: rebuild_cache

.PHONY : rebuild_cache/fast

# Special rule for the target edit_cache
edit_cache:
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --cyan "Running CMake cache editor..."
	/usr/bin/ccmake.exe -S$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR)
.PHONY : edit_cache

# Special rule for the target edit_cache
edit_cache/fast: edit_cache

.PHONY : edit_cache/fast

# The main all target
all: cmake_check_build_system
	$(CMAKE_COMMAND) -E cmake_progress_start /cygdrive/d/linuxDrive/wav_to_mp3/CMakeFiles /cygdrive/d/linuxDrive/wav_to_mp3/CMakeFiles/progress.marks
	$(MAKE) -f CMakeFiles/Makefile2 all
	$(CMAKE_COMMAND) -E cmake_progress_start /cygdrive/d/linuxDrive/wav_to_mp3/CMakeFiles 0
.PHONY : all

# The main clean target
clean:
	$(MAKE) -f CMakeFiles/Makefile2 clean
.PHONY : clean

# The main clean target
clean/fast: clean

.PHONY : clean/fast

# Prepare targets for installation.
preinstall: all
	$(MAKE) -f CMakeFiles/Makefile2 preinstall
.PHONY : preinstall

# Prepare targets for installation.
preinstall/fast:
	$(MAKE) -f CMakeFiles/Makefile2 preinstall
.PHONY : preinstall/fast

# clear depends
depend:
	$(CMAKE_COMMAND) -S$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR) --check-build-system CMakeFiles/Makefile.cmake 1
.PHONY : depend

#=============================================================================
# Target rules for targets named wav_to_mp3

# Build rule for target.
wav_to_mp3: cmake_check_build_system
	$(MAKE) -f CMakeFiles/Makefile2 wav_to_mp3
.PHONY : wav_to_mp3

# fast build rule for target.
wav_to_mp3/fast:
	$(MAKE) -f CMakeFiles/wav_to_mp3.dir/build.make CMakeFiles/wav_to_mp3.dir/build
.PHONY : wav_to_mp3/fast

main.o: main.cpp.o

.PHONY : main.o

# target to build an object file
main.cpp.o:
	$(MAKE) -f CMakeFiles/wav_to_mp3.dir/build.make CMakeFiles/wav_to_mp3.dir/main.cpp.o
.PHONY : main.cpp.o

main.i: main.cpp.i

.PHONY : main.i

# target to preprocess a source file
main.cpp.i:
	$(MAKE) -f CMakeFiles/wav_to_mp3.dir/build.make CMakeFiles/wav_to_mp3.dir/main.cpp.i
.PHONY : main.cpp.i

main.s: main.cpp.s

.PHONY : main.s

# target to generate assembly for a file
main.cpp.s:
	$(MAKE) -f CMakeFiles/wav_to_mp3.dir/build.make CMakeFiles/wav_to_mp3.dir/main.cpp.s
.PHONY : main.cpp.s

wavFileHandler.o: wavFileHandler.cpp.o

.PHONY : wavFileHandler.o

# target to build an object file
wavFileHandler.cpp.o:
	$(MAKE) -f CMakeFiles/wav_to_mp3.dir/build.make CMakeFiles/wav_to_mp3.dir/wavFileHandler.cpp.o
.PHONY : wavFileHandler.cpp.o

wavFileHandler.i: wavFileHandler.cpp.i

.PHONY : wavFileHandler.i

# target to preprocess a source file
wavFileHandler.cpp.i:
	$(MAKE) -f CMakeFiles/wav_to_mp3.dir/build.make CMakeFiles/wav_to_mp3.dir/wavFileHandler.cpp.i
.PHONY : wavFileHandler.cpp.i

wavFileHandler.s: wavFileHandler.cpp.s

.PHONY : wavFileHandler.s

# target to generate assembly for a file
wavFileHandler.cpp.s:
	$(MAKE) -f CMakeFiles/wav_to_mp3.dir/build.make CMakeFiles/wav_to_mp3.dir/wavFileHandler.cpp.s
.PHONY : wavFileHandler.cpp.s

wav_to_mp3.o: wav_to_mp3.cpp.o

.PHONY : wav_to_mp3.o

# target to build an object file
wav_to_mp3.cpp.o:
	$(MAKE) -f CMakeFiles/wav_to_mp3.dir/build.make CMakeFiles/wav_to_mp3.dir/wav_to_mp3.cpp.o
.PHONY : wav_to_mp3.cpp.o

wav_to_mp3.i: wav_to_mp3.cpp.i

.PHONY : wav_to_mp3.i

# target to preprocess a source file
wav_to_mp3.cpp.i:
	$(MAKE) -f CMakeFiles/wav_to_mp3.dir/build.make CMakeFiles/wav_to_mp3.dir/wav_to_mp3.cpp.i
.PHONY : wav_to_mp3.cpp.i

wav_to_mp3.s: wav_to_mp3.cpp.s

.PHONY : wav_to_mp3.s

# target to generate assembly for a file
wav_to_mp3.cpp.s:
	$(MAKE) -f CMakeFiles/wav_to_mp3.dir/build.make CMakeFiles/wav_to_mp3.dir/wav_to_mp3.cpp.s
.PHONY : wav_to_mp3.cpp.s

# Help Target
help:
	@echo "The following are some of the valid targets for this Makefile:"
	@echo "... all (the default if no target is provided)"
	@echo "... clean"
	@echo "... depend"
	@echo "... rebuild_cache"
	@echo "... wav_to_mp3"
	@echo "... edit_cache"
	@echo "... main.o"
	@echo "... main.i"
	@echo "... main.s"
	@echo "... wavFileHandler.o"
	@echo "... wavFileHandler.i"
	@echo "... wavFileHandler.s"
	@echo "... wav_to_mp3.o"
	@echo "... wav_to_mp3.i"
	@echo "... wav_to_mp3.s"
.PHONY : help



#=============================================================================
# Special targets to cleanup operation of make.

# Special rule to run CMake to check the build system integrity.
# No rule that depends on this can have commands that come from listfiles
# because they might be regenerated.
cmake_check_build_system:
	$(CMAKE_COMMAND) -S$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR) --check-build-system CMakeFiles/Makefile.cmake 0
.PHONY : cmake_check_build_system
