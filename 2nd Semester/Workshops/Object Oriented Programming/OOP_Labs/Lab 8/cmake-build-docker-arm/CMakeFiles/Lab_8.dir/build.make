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
CMAKE_SOURCE_DIR = "/tmp/Lab 8"

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = "/tmp/Lab 8/cmake-build-docker-arm"

# Include any dependencies generated for this target.
include CMakeFiles/Lab_8.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/Lab_8.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/Lab_8.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/Lab_8.dir/flags.make

CMakeFiles/Lab_8.dir/main.cpp.o: CMakeFiles/Lab_8.dir/flags.make
CMakeFiles/Lab_8.dir/main.cpp.o: /tmp/Lab\ 8/main.cpp
CMakeFiles/Lab_8.dir/main.cpp.o: CMakeFiles/Lab_8.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/tmp/Lab 8/cmake-build-docker-arm/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/Lab_8.dir/main.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/Lab_8.dir/main.cpp.o -MF CMakeFiles/Lab_8.dir/main.cpp.o.d -o CMakeFiles/Lab_8.dir/main.cpp.o -c "/tmp/Lab 8/main.cpp"

CMakeFiles/Lab_8.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Lab_8.dir/main.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "/tmp/Lab 8/main.cpp" > CMakeFiles/Lab_8.dir/main.cpp.i

CMakeFiles/Lab_8.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Lab_8.dir/main.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "/tmp/Lab 8/main.cpp" -o CMakeFiles/Lab_8.dir/main.cpp.s

CMakeFiles/Lab_8.dir/src/domain.cpp.o: CMakeFiles/Lab_8.dir/flags.make
CMakeFiles/Lab_8.dir/src/domain.cpp.o: /tmp/Lab\ 8/src/domain.cpp
CMakeFiles/Lab_8.dir/src/domain.cpp.o: CMakeFiles/Lab_8.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/tmp/Lab 8/cmake-build-docker-arm/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/Lab_8.dir/src/domain.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/Lab_8.dir/src/domain.cpp.o -MF CMakeFiles/Lab_8.dir/src/domain.cpp.o.d -o CMakeFiles/Lab_8.dir/src/domain.cpp.o -c "/tmp/Lab 8/src/domain.cpp"

CMakeFiles/Lab_8.dir/src/domain.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Lab_8.dir/src/domain.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "/tmp/Lab 8/src/domain.cpp" > CMakeFiles/Lab_8.dir/src/domain.cpp.i

CMakeFiles/Lab_8.dir/src/domain.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Lab_8.dir/src/domain.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "/tmp/Lab 8/src/domain.cpp" -o CMakeFiles/Lab_8.dir/src/domain.cpp.s

CMakeFiles/Lab_8.dir/src/repository.cpp.o: CMakeFiles/Lab_8.dir/flags.make
CMakeFiles/Lab_8.dir/src/repository.cpp.o: /tmp/Lab\ 8/src/repository.cpp
CMakeFiles/Lab_8.dir/src/repository.cpp.o: CMakeFiles/Lab_8.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/tmp/Lab 8/cmake-build-docker-arm/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/Lab_8.dir/src/repository.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/Lab_8.dir/src/repository.cpp.o -MF CMakeFiles/Lab_8.dir/src/repository.cpp.o.d -o CMakeFiles/Lab_8.dir/src/repository.cpp.o -c "/tmp/Lab 8/src/repository.cpp"

CMakeFiles/Lab_8.dir/src/repository.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Lab_8.dir/src/repository.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "/tmp/Lab 8/src/repository.cpp" > CMakeFiles/Lab_8.dir/src/repository.cpp.i

CMakeFiles/Lab_8.dir/src/repository.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Lab_8.dir/src/repository.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "/tmp/Lab 8/src/repository.cpp" -o CMakeFiles/Lab_8.dir/src/repository.cpp.s

CMakeFiles/Lab_8.dir/src/service.cpp.o: CMakeFiles/Lab_8.dir/flags.make
CMakeFiles/Lab_8.dir/src/service.cpp.o: /tmp/Lab\ 8/src/service.cpp
CMakeFiles/Lab_8.dir/src/service.cpp.o: CMakeFiles/Lab_8.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/tmp/Lab 8/cmake-build-docker-arm/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/Lab_8.dir/src/service.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/Lab_8.dir/src/service.cpp.o -MF CMakeFiles/Lab_8.dir/src/service.cpp.o.d -o CMakeFiles/Lab_8.dir/src/service.cpp.o -c "/tmp/Lab 8/src/service.cpp"

CMakeFiles/Lab_8.dir/src/service.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Lab_8.dir/src/service.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "/tmp/Lab 8/src/service.cpp" > CMakeFiles/Lab_8.dir/src/service.cpp.i

CMakeFiles/Lab_8.dir/src/service.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Lab_8.dir/src/service.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "/tmp/Lab 8/src/service.cpp" -o CMakeFiles/Lab_8.dir/src/service.cpp.s

CMakeFiles/Lab_8.dir/src/ui.cpp.o: CMakeFiles/Lab_8.dir/flags.make
CMakeFiles/Lab_8.dir/src/ui.cpp.o: /tmp/Lab\ 8/src/ui.cpp
CMakeFiles/Lab_8.dir/src/ui.cpp.o: CMakeFiles/Lab_8.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/tmp/Lab 8/cmake-build-docker-arm/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object CMakeFiles/Lab_8.dir/src/ui.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/Lab_8.dir/src/ui.cpp.o -MF CMakeFiles/Lab_8.dir/src/ui.cpp.o.d -o CMakeFiles/Lab_8.dir/src/ui.cpp.o -c "/tmp/Lab 8/src/ui.cpp"

CMakeFiles/Lab_8.dir/src/ui.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Lab_8.dir/src/ui.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "/tmp/Lab 8/src/ui.cpp" > CMakeFiles/Lab_8.dir/src/ui.cpp.i

CMakeFiles/Lab_8.dir/src/ui.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Lab_8.dir/src/ui.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "/tmp/Lab 8/src/ui.cpp" -o CMakeFiles/Lab_8.dir/src/ui.cpp.s

CMakeFiles/Lab_8.dir/tests/tests_domain.cpp.o: CMakeFiles/Lab_8.dir/flags.make
CMakeFiles/Lab_8.dir/tests/tests_domain.cpp.o: /tmp/Lab\ 8/tests/tests_domain.cpp
CMakeFiles/Lab_8.dir/tests/tests_domain.cpp.o: CMakeFiles/Lab_8.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/tmp/Lab 8/cmake-build-docker-arm/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_6) "Building CXX object CMakeFiles/Lab_8.dir/tests/tests_domain.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/Lab_8.dir/tests/tests_domain.cpp.o -MF CMakeFiles/Lab_8.dir/tests/tests_domain.cpp.o.d -o CMakeFiles/Lab_8.dir/tests/tests_domain.cpp.o -c "/tmp/Lab 8/tests/tests_domain.cpp"

CMakeFiles/Lab_8.dir/tests/tests_domain.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Lab_8.dir/tests/tests_domain.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "/tmp/Lab 8/tests/tests_domain.cpp" > CMakeFiles/Lab_8.dir/tests/tests_domain.cpp.i

CMakeFiles/Lab_8.dir/tests/tests_domain.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Lab_8.dir/tests/tests_domain.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "/tmp/Lab 8/tests/tests_domain.cpp" -o CMakeFiles/Lab_8.dir/tests/tests_domain.cpp.s

CMakeFiles/Lab_8.dir/tests/tests_repository.cpp.o: CMakeFiles/Lab_8.dir/flags.make
CMakeFiles/Lab_8.dir/tests/tests_repository.cpp.o: /tmp/Lab\ 8/tests/tests_repository.cpp
CMakeFiles/Lab_8.dir/tests/tests_repository.cpp.o: CMakeFiles/Lab_8.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/tmp/Lab 8/cmake-build-docker-arm/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_7) "Building CXX object CMakeFiles/Lab_8.dir/tests/tests_repository.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/Lab_8.dir/tests/tests_repository.cpp.o -MF CMakeFiles/Lab_8.dir/tests/tests_repository.cpp.o.d -o CMakeFiles/Lab_8.dir/tests/tests_repository.cpp.o -c "/tmp/Lab 8/tests/tests_repository.cpp"

CMakeFiles/Lab_8.dir/tests/tests_repository.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Lab_8.dir/tests/tests_repository.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "/tmp/Lab 8/tests/tests_repository.cpp" > CMakeFiles/Lab_8.dir/tests/tests_repository.cpp.i

CMakeFiles/Lab_8.dir/tests/tests_repository.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Lab_8.dir/tests/tests_repository.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "/tmp/Lab 8/tests/tests_repository.cpp" -o CMakeFiles/Lab_8.dir/tests/tests_repository.cpp.s

CMakeFiles/Lab_8.dir/src/validator.cpp.o: CMakeFiles/Lab_8.dir/flags.make
CMakeFiles/Lab_8.dir/src/validator.cpp.o: /tmp/Lab\ 8/src/validator.cpp
CMakeFiles/Lab_8.dir/src/validator.cpp.o: CMakeFiles/Lab_8.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/tmp/Lab 8/cmake-build-docker-arm/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_8) "Building CXX object CMakeFiles/Lab_8.dir/src/validator.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/Lab_8.dir/src/validator.cpp.o -MF CMakeFiles/Lab_8.dir/src/validator.cpp.o.d -o CMakeFiles/Lab_8.dir/src/validator.cpp.o -c "/tmp/Lab 8/src/validator.cpp"

CMakeFiles/Lab_8.dir/src/validator.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Lab_8.dir/src/validator.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "/tmp/Lab 8/src/validator.cpp" > CMakeFiles/Lab_8.dir/src/validator.cpp.i

CMakeFiles/Lab_8.dir/src/validator.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Lab_8.dir/src/validator.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "/tmp/Lab 8/src/validator.cpp" -o CMakeFiles/Lab_8.dir/src/validator.cpp.s

CMakeFiles/Lab_8.dir/tests/tests_validator.cpp.o: CMakeFiles/Lab_8.dir/flags.make
CMakeFiles/Lab_8.dir/tests/tests_validator.cpp.o: /tmp/Lab\ 8/tests/tests_validator.cpp
CMakeFiles/Lab_8.dir/tests/tests_validator.cpp.o: CMakeFiles/Lab_8.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/tmp/Lab 8/cmake-build-docker-arm/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_9) "Building CXX object CMakeFiles/Lab_8.dir/tests/tests_validator.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/Lab_8.dir/tests/tests_validator.cpp.o -MF CMakeFiles/Lab_8.dir/tests/tests_validator.cpp.o.d -o CMakeFiles/Lab_8.dir/tests/tests_validator.cpp.o -c "/tmp/Lab 8/tests/tests_validator.cpp"

CMakeFiles/Lab_8.dir/tests/tests_validator.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Lab_8.dir/tests/tests_validator.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "/tmp/Lab 8/tests/tests_validator.cpp" > CMakeFiles/Lab_8.dir/tests/tests_validator.cpp.i

CMakeFiles/Lab_8.dir/tests/tests_validator.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Lab_8.dir/tests/tests_validator.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "/tmp/Lab 8/tests/tests_validator.cpp" -o CMakeFiles/Lab_8.dir/tests/tests_validator.cpp.s

CMakeFiles/Lab_8.dir/tests/tests_service.cpp.o: CMakeFiles/Lab_8.dir/flags.make
CMakeFiles/Lab_8.dir/tests/tests_service.cpp.o: /tmp/Lab\ 8/tests/tests_service.cpp
CMakeFiles/Lab_8.dir/tests/tests_service.cpp.o: CMakeFiles/Lab_8.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/tmp/Lab 8/cmake-build-docker-arm/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_10) "Building CXX object CMakeFiles/Lab_8.dir/tests/tests_service.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/Lab_8.dir/tests/tests_service.cpp.o -MF CMakeFiles/Lab_8.dir/tests/tests_service.cpp.o.d -o CMakeFiles/Lab_8.dir/tests/tests_service.cpp.o -c "/tmp/Lab 8/tests/tests_service.cpp"

CMakeFiles/Lab_8.dir/tests/tests_service.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Lab_8.dir/tests/tests_service.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "/tmp/Lab 8/tests/tests_service.cpp" > CMakeFiles/Lab_8.dir/tests/tests_service.cpp.i

CMakeFiles/Lab_8.dir/tests/tests_service.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Lab_8.dir/tests/tests_service.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "/tmp/Lab 8/tests/tests_service.cpp" -o CMakeFiles/Lab_8.dir/tests/tests_service.cpp.s

CMakeFiles/Lab_8.dir/tests/tests_exceptions.cpp.o: CMakeFiles/Lab_8.dir/flags.make
CMakeFiles/Lab_8.dir/tests/tests_exceptions.cpp.o: /tmp/Lab\ 8/tests/tests_exceptions.cpp
CMakeFiles/Lab_8.dir/tests/tests_exceptions.cpp.o: CMakeFiles/Lab_8.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/tmp/Lab 8/cmake-build-docker-arm/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_11) "Building CXX object CMakeFiles/Lab_8.dir/tests/tests_exceptions.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/Lab_8.dir/tests/tests_exceptions.cpp.o -MF CMakeFiles/Lab_8.dir/tests/tests_exceptions.cpp.o.d -o CMakeFiles/Lab_8.dir/tests/tests_exceptions.cpp.o -c "/tmp/Lab 8/tests/tests_exceptions.cpp"

CMakeFiles/Lab_8.dir/tests/tests_exceptions.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Lab_8.dir/tests/tests_exceptions.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "/tmp/Lab 8/tests/tests_exceptions.cpp" > CMakeFiles/Lab_8.dir/tests/tests_exceptions.cpp.i

CMakeFiles/Lab_8.dir/tests/tests_exceptions.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Lab_8.dir/tests/tests_exceptions.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "/tmp/Lab 8/tests/tests_exceptions.cpp" -o CMakeFiles/Lab_8.dir/tests/tests_exceptions.cpp.s

CMakeFiles/Lab_8.dir/src/contract.cpp.o: CMakeFiles/Lab_8.dir/flags.make
CMakeFiles/Lab_8.dir/src/contract.cpp.o: /tmp/Lab\ 8/src/contract.cpp
CMakeFiles/Lab_8.dir/src/contract.cpp.o: CMakeFiles/Lab_8.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/tmp/Lab 8/cmake-build-docker-arm/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_12) "Building CXX object CMakeFiles/Lab_8.dir/src/contract.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/Lab_8.dir/src/contract.cpp.o -MF CMakeFiles/Lab_8.dir/src/contract.cpp.o.d -o CMakeFiles/Lab_8.dir/src/contract.cpp.o -c "/tmp/Lab 8/src/contract.cpp"

CMakeFiles/Lab_8.dir/src/contract.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Lab_8.dir/src/contract.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "/tmp/Lab 8/src/contract.cpp" > CMakeFiles/Lab_8.dir/src/contract.cpp.i

CMakeFiles/Lab_8.dir/src/contract.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Lab_8.dir/src/contract.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "/tmp/Lab 8/src/contract.cpp" -o CMakeFiles/Lab_8.dir/src/contract.cpp.s

CMakeFiles/Lab_8.dir/tests/tests_contract.cpp.o: CMakeFiles/Lab_8.dir/flags.make
CMakeFiles/Lab_8.dir/tests/tests_contract.cpp.o: /tmp/Lab\ 8/tests/tests_contract.cpp
CMakeFiles/Lab_8.dir/tests/tests_contract.cpp.o: CMakeFiles/Lab_8.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/tmp/Lab 8/cmake-build-docker-arm/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_13) "Building CXX object CMakeFiles/Lab_8.dir/tests/tests_contract.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/Lab_8.dir/tests/tests_contract.cpp.o -MF CMakeFiles/Lab_8.dir/tests/tests_contract.cpp.o.d -o CMakeFiles/Lab_8.dir/tests/tests_contract.cpp.o -c "/tmp/Lab 8/tests/tests_contract.cpp"

CMakeFiles/Lab_8.dir/tests/tests_contract.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Lab_8.dir/tests/tests_contract.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "/tmp/Lab 8/tests/tests_contract.cpp" > CMakeFiles/Lab_8.dir/tests/tests_contract.cpp.i

CMakeFiles/Lab_8.dir/tests/tests_contract.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Lab_8.dir/tests/tests_contract.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "/tmp/Lab 8/tests/tests_contract.cpp" -o CMakeFiles/Lab_8.dir/tests/tests_contract.cpp.s

CMakeFiles/Lab_8.dir/src/undo.cpp.o: CMakeFiles/Lab_8.dir/flags.make
CMakeFiles/Lab_8.dir/src/undo.cpp.o: /tmp/Lab\ 8/src/undo.cpp
CMakeFiles/Lab_8.dir/src/undo.cpp.o: CMakeFiles/Lab_8.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/tmp/Lab 8/cmake-build-docker-arm/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_14) "Building CXX object CMakeFiles/Lab_8.dir/src/undo.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/Lab_8.dir/src/undo.cpp.o -MF CMakeFiles/Lab_8.dir/src/undo.cpp.o.d -o CMakeFiles/Lab_8.dir/src/undo.cpp.o -c "/tmp/Lab 8/src/undo.cpp"

CMakeFiles/Lab_8.dir/src/undo.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Lab_8.dir/src/undo.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "/tmp/Lab 8/src/undo.cpp" > CMakeFiles/Lab_8.dir/src/undo.cpp.i

CMakeFiles/Lab_8.dir/src/undo.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Lab_8.dir/src/undo.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "/tmp/Lab 8/src/undo.cpp" -o CMakeFiles/Lab_8.dir/src/undo.cpp.s

CMakeFiles/Lab_8.dir/tests/tests_undo.cpp.o: CMakeFiles/Lab_8.dir/flags.make
CMakeFiles/Lab_8.dir/tests/tests_undo.cpp.o: /tmp/Lab\ 8/tests/tests_undo.cpp
CMakeFiles/Lab_8.dir/tests/tests_undo.cpp.o: CMakeFiles/Lab_8.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/tmp/Lab 8/cmake-build-docker-arm/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_15) "Building CXX object CMakeFiles/Lab_8.dir/tests/tests_undo.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/Lab_8.dir/tests/tests_undo.cpp.o -MF CMakeFiles/Lab_8.dir/tests/tests_undo.cpp.o.d -o CMakeFiles/Lab_8.dir/tests/tests_undo.cpp.o -c "/tmp/Lab 8/tests/tests_undo.cpp"

CMakeFiles/Lab_8.dir/tests/tests_undo.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Lab_8.dir/tests/tests_undo.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "/tmp/Lab 8/tests/tests_undo.cpp" > CMakeFiles/Lab_8.dir/tests/tests_undo.cpp.i

CMakeFiles/Lab_8.dir/tests/tests_undo.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Lab_8.dir/tests/tests_undo.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "/tmp/Lab 8/tests/tests_undo.cpp" -o CMakeFiles/Lab_8.dir/tests/tests_undo.cpp.s

# Object files for target Lab_8
Lab_8_OBJECTS = \
"CMakeFiles/Lab_8.dir/main.cpp.o" \
"CMakeFiles/Lab_8.dir/src/domain.cpp.o" \
"CMakeFiles/Lab_8.dir/src/repository.cpp.o" \
"CMakeFiles/Lab_8.dir/src/service.cpp.o" \
"CMakeFiles/Lab_8.dir/src/ui.cpp.o" \
"CMakeFiles/Lab_8.dir/tests/tests_domain.cpp.o" \
"CMakeFiles/Lab_8.dir/tests/tests_repository.cpp.o" \
"CMakeFiles/Lab_8.dir/src/validator.cpp.o" \
"CMakeFiles/Lab_8.dir/tests/tests_validator.cpp.o" \
"CMakeFiles/Lab_8.dir/tests/tests_service.cpp.o" \
"CMakeFiles/Lab_8.dir/tests/tests_exceptions.cpp.o" \
"CMakeFiles/Lab_8.dir/src/contract.cpp.o" \
"CMakeFiles/Lab_8.dir/tests/tests_contract.cpp.o" \
"CMakeFiles/Lab_8.dir/src/undo.cpp.o" \
"CMakeFiles/Lab_8.dir/tests/tests_undo.cpp.o"

# External object files for target Lab_8
Lab_8_EXTERNAL_OBJECTS =

Lab_8: CMakeFiles/Lab_8.dir/main.cpp.o
Lab_8: CMakeFiles/Lab_8.dir/src/domain.cpp.o
Lab_8: CMakeFiles/Lab_8.dir/src/repository.cpp.o
Lab_8: CMakeFiles/Lab_8.dir/src/service.cpp.o
Lab_8: CMakeFiles/Lab_8.dir/src/ui.cpp.o
Lab_8: CMakeFiles/Lab_8.dir/tests/tests_domain.cpp.o
Lab_8: CMakeFiles/Lab_8.dir/tests/tests_repository.cpp.o
Lab_8: CMakeFiles/Lab_8.dir/src/validator.cpp.o
Lab_8: CMakeFiles/Lab_8.dir/tests/tests_validator.cpp.o
Lab_8: CMakeFiles/Lab_8.dir/tests/tests_service.cpp.o
Lab_8: CMakeFiles/Lab_8.dir/tests/tests_exceptions.cpp.o
Lab_8: CMakeFiles/Lab_8.dir/src/contract.cpp.o
Lab_8: CMakeFiles/Lab_8.dir/tests/tests_contract.cpp.o
Lab_8: CMakeFiles/Lab_8.dir/src/undo.cpp.o
Lab_8: CMakeFiles/Lab_8.dir/tests/tests_undo.cpp.o
Lab_8: CMakeFiles/Lab_8.dir/build.make
Lab_8: CMakeFiles/Lab_8.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir="/tmp/Lab 8/cmake-build-docker-arm/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_16) "Linking CXX executable Lab_8"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/Lab_8.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/Lab_8.dir/build: Lab_8
.PHONY : CMakeFiles/Lab_8.dir/build

CMakeFiles/Lab_8.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/Lab_8.dir/cmake_clean.cmake
.PHONY : CMakeFiles/Lab_8.dir/clean

CMakeFiles/Lab_8.dir/depend:
	cd "/tmp/Lab 8/cmake-build-docker-arm" && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" "/tmp/Lab 8" "/tmp/Lab 8" "/tmp/Lab 8/cmake-build-docker-arm" "/tmp/Lab 8/cmake-build-docker-arm" "/tmp/Lab 8/cmake-build-docker-arm/CMakeFiles/Lab_8.dir/DependInfo.cmake" --color=$(COLOR)
.PHONY : CMakeFiles/Lab_8.dir/depend

