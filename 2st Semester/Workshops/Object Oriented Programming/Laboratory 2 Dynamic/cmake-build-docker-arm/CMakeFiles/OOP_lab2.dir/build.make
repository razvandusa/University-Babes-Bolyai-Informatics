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
CMAKE_SOURCE_DIR = "/tmp/OOP_lab2 Dinamic"

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = "/tmp/OOP_lab2 Dinamic/cmake-build-docker-arm"

# Include any dependencies generated for this target.
include CMakeFiles/OOP_lab2.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/OOP_lab2.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/OOP_lab2.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/OOP_lab2.dir/flags.make

CMakeFiles/OOP_lab2.dir/main.c.o: CMakeFiles/OOP_lab2.dir/flags.make
CMakeFiles/OOP_lab2.dir/main.c.o: /tmp/OOP_lab2\ Dinamic/main.c
CMakeFiles/OOP_lab2.dir/main.c.o: CMakeFiles/OOP_lab2.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/tmp/OOP_lab2 Dinamic/cmake-build-docker-arm/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/OOP_lab2.dir/main.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/OOP_lab2.dir/main.c.o -MF CMakeFiles/OOP_lab2.dir/main.c.o.d -o CMakeFiles/OOP_lab2.dir/main.c.o -c "/tmp/OOP_lab2 Dinamic/main.c"

CMakeFiles/OOP_lab2.dir/main.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/OOP_lab2.dir/main.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E "/tmp/OOP_lab2 Dinamic/main.c" > CMakeFiles/OOP_lab2.dir/main.c.i

CMakeFiles/OOP_lab2.dir/main.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/OOP_lab2.dir/main.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S "/tmp/OOP_lab2 Dinamic/main.c" -o CMakeFiles/OOP_lab2.dir/main.c.s

CMakeFiles/OOP_lab2.dir/Domain/domain.c.o: CMakeFiles/OOP_lab2.dir/flags.make
CMakeFiles/OOP_lab2.dir/Domain/domain.c.o: /tmp/OOP_lab2\ Dinamic/Domain/domain.c
CMakeFiles/OOP_lab2.dir/Domain/domain.c.o: CMakeFiles/OOP_lab2.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/tmp/OOP_lab2 Dinamic/cmake-build-docker-arm/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_2) "Building C object CMakeFiles/OOP_lab2.dir/Domain/domain.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/OOP_lab2.dir/Domain/domain.c.o -MF CMakeFiles/OOP_lab2.dir/Domain/domain.c.o.d -o CMakeFiles/OOP_lab2.dir/Domain/domain.c.o -c "/tmp/OOP_lab2 Dinamic/Domain/domain.c"

CMakeFiles/OOP_lab2.dir/Domain/domain.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/OOP_lab2.dir/Domain/domain.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E "/tmp/OOP_lab2 Dinamic/Domain/domain.c" > CMakeFiles/OOP_lab2.dir/Domain/domain.c.i

CMakeFiles/OOP_lab2.dir/Domain/domain.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/OOP_lab2.dir/Domain/domain.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S "/tmp/OOP_lab2 Dinamic/Domain/domain.c" -o CMakeFiles/OOP_lab2.dir/Domain/domain.c.s

CMakeFiles/OOP_lab2.dir/Repository/repository.c.o: CMakeFiles/OOP_lab2.dir/flags.make
CMakeFiles/OOP_lab2.dir/Repository/repository.c.o: /tmp/OOP_lab2\ Dinamic/Repository/repository.c
CMakeFiles/OOP_lab2.dir/Repository/repository.c.o: CMakeFiles/OOP_lab2.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/tmp/OOP_lab2 Dinamic/cmake-build-docker-arm/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_3) "Building C object CMakeFiles/OOP_lab2.dir/Repository/repository.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/OOP_lab2.dir/Repository/repository.c.o -MF CMakeFiles/OOP_lab2.dir/Repository/repository.c.o.d -o CMakeFiles/OOP_lab2.dir/Repository/repository.c.o -c "/tmp/OOP_lab2 Dinamic/Repository/repository.c"

CMakeFiles/OOP_lab2.dir/Repository/repository.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/OOP_lab2.dir/Repository/repository.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E "/tmp/OOP_lab2 Dinamic/Repository/repository.c" > CMakeFiles/OOP_lab2.dir/Repository/repository.c.i

CMakeFiles/OOP_lab2.dir/Repository/repository.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/OOP_lab2.dir/Repository/repository.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S "/tmp/OOP_lab2 Dinamic/Repository/repository.c" -o CMakeFiles/OOP_lab2.dir/Repository/repository.c.s

CMakeFiles/OOP_lab2.dir/Tests/repository_tests.c.o: CMakeFiles/OOP_lab2.dir/flags.make
CMakeFiles/OOP_lab2.dir/Tests/repository_tests.c.o: /tmp/OOP_lab2\ Dinamic/Tests/repository_tests.c
CMakeFiles/OOP_lab2.dir/Tests/repository_tests.c.o: CMakeFiles/OOP_lab2.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/tmp/OOP_lab2 Dinamic/cmake-build-docker-arm/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_4) "Building C object CMakeFiles/OOP_lab2.dir/Tests/repository_tests.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/OOP_lab2.dir/Tests/repository_tests.c.o -MF CMakeFiles/OOP_lab2.dir/Tests/repository_tests.c.o.d -o CMakeFiles/OOP_lab2.dir/Tests/repository_tests.c.o -c "/tmp/OOP_lab2 Dinamic/Tests/repository_tests.c"

CMakeFiles/OOP_lab2.dir/Tests/repository_tests.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/OOP_lab2.dir/Tests/repository_tests.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E "/tmp/OOP_lab2 Dinamic/Tests/repository_tests.c" > CMakeFiles/OOP_lab2.dir/Tests/repository_tests.c.i

CMakeFiles/OOP_lab2.dir/Tests/repository_tests.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/OOP_lab2.dir/Tests/repository_tests.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S "/tmp/OOP_lab2 Dinamic/Tests/repository_tests.c" -o CMakeFiles/OOP_lab2.dir/Tests/repository_tests.c.s

CMakeFiles/OOP_lab2.dir/Tests/service_tests.c.o: CMakeFiles/OOP_lab2.dir/flags.make
CMakeFiles/OOP_lab2.dir/Tests/service_tests.c.o: /tmp/OOP_lab2\ Dinamic/Tests/service_tests.c
CMakeFiles/OOP_lab2.dir/Tests/service_tests.c.o: CMakeFiles/OOP_lab2.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/tmp/OOP_lab2 Dinamic/cmake-build-docker-arm/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_5) "Building C object CMakeFiles/OOP_lab2.dir/Tests/service_tests.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/OOP_lab2.dir/Tests/service_tests.c.o -MF CMakeFiles/OOP_lab2.dir/Tests/service_tests.c.o.d -o CMakeFiles/OOP_lab2.dir/Tests/service_tests.c.o -c "/tmp/OOP_lab2 Dinamic/Tests/service_tests.c"

CMakeFiles/OOP_lab2.dir/Tests/service_tests.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/OOP_lab2.dir/Tests/service_tests.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E "/tmp/OOP_lab2 Dinamic/Tests/service_tests.c" > CMakeFiles/OOP_lab2.dir/Tests/service_tests.c.i

CMakeFiles/OOP_lab2.dir/Tests/service_tests.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/OOP_lab2.dir/Tests/service_tests.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S "/tmp/OOP_lab2 Dinamic/Tests/service_tests.c" -o CMakeFiles/OOP_lab2.dir/Tests/service_tests.c.s

CMakeFiles/OOP_lab2.dir/UI/ui.c.o: CMakeFiles/OOP_lab2.dir/flags.make
CMakeFiles/OOP_lab2.dir/UI/ui.c.o: /tmp/OOP_lab2\ Dinamic/UI/ui.c
CMakeFiles/OOP_lab2.dir/UI/ui.c.o: CMakeFiles/OOP_lab2.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/tmp/OOP_lab2 Dinamic/cmake-build-docker-arm/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_6) "Building C object CMakeFiles/OOP_lab2.dir/UI/ui.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/OOP_lab2.dir/UI/ui.c.o -MF CMakeFiles/OOP_lab2.dir/UI/ui.c.o.d -o CMakeFiles/OOP_lab2.dir/UI/ui.c.o -c "/tmp/OOP_lab2 Dinamic/UI/ui.c"

CMakeFiles/OOP_lab2.dir/UI/ui.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/OOP_lab2.dir/UI/ui.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E "/tmp/OOP_lab2 Dinamic/UI/ui.c" > CMakeFiles/OOP_lab2.dir/UI/ui.c.i

CMakeFiles/OOP_lab2.dir/UI/ui.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/OOP_lab2.dir/UI/ui.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S "/tmp/OOP_lab2 Dinamic/UI/ui.c" -o CMakeFiles/OOP_lab2.dir/UI/ui.c.s

CMakeFiles/OOP_lab2.dir/Service/service.c.o: CMakeFiles/OOP_lab2.dir/flags.make
CMakeFiles/OOP_lab2.dir/Service/service.c.o: /tmp/OOP_lab2\ Dinamic/Service/service.c
CMakeFiles/OOP_lab2.dir/Service/service.c.o: CMakeFiles/OOP_lab2.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/tmp/OOP_lab2 Dinamic/cmake-build-docker-arm/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_7) "Building C object CMakeFiles/OOP_lab2.dir/Service/service.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/OOP_lab2.dir/Service/service.c.o -MF CMakeFiles/OOP_lab2.dir/Service/service.c.o.d -o CMakeFiles/OOP_lab2.dir/Service/service.c.o -c "/tmp/OOP_lab2 Dinamic/Service/service.c"

CMakeFiles/OOP_lab2.dir/Service/service.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/OOP_lab2.dir/Service/service.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E "/tmp/OOP_lab2 Dinamic/Service/service.c" > CMakeFiles/OOP_lab2.dir/Service/service.c.i

CMakeFiles/OOP_lab2.dir/Service/service.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/OOP_lab2.dir/Service/service.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S "/tmp/OOP_lab2 Dinamic/Service/service.c" -o CMakeFiles/OOP_lab2.dir/Service/service.c.s

CMakeFiles/OOP_lab2.dir/Tests/domain_tests.c.o: CMakeFiles/OOP_lab2.dir/flags.make
CMakeFiles/OOP_lab2.dir/Tests/domain_tests.c.o: /tmp/OOP_lab2\ Dinamic/Tests/domain_tests.c
CMakeFiles/OOP_lab2.dir/Tests/domain_tests.c.o: CMakeFiles/OOP_lab2.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/tmp/OOP_lab2 Dinamic/cmake-build-docker-arm/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_8) "Building C object CMakeFiles/OOP_lab2.dir/Tests/domain_tests.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/OOP_lab2.dir/Tests/domain_tests.c.o -MF CMakeFiles/OOP_lab2.dir/Tests/domain_tests.c.o.d -o CMakeFiles/OOP_lab2.dir/Tests/domain_tests.c.o -c "/tmp/OOP_lab2 Dinamic/Tests/domain_tests.c"

CMakeFiles/OOP_lab2.dir/Tests/domain_tests.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/OOP_lab2.dir/Tests/domain_tests.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E "/tmp/OOP_lab2 Dinamic/Tests/domain_tests.c" > CMakeFiles/OOP_lab2.dir/Tests/domain_tests.c.i

CMakeFiles/OOP_lab2.dir/Tests/domain_tests.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/OOP_lab2.dir/Tests/domain_tests.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S "/tmp/OOP_lab2 Dinamic/Tests/domain_tests.c" -o CMakeFiles/OOP_lab2.dir/Tests/domain_tests.c.s

# Object files for target OOP_lab2
OOP_lab2_OBJECTS = \
"CMakeFiles/OOP_lab2.dir/main.c.o" \
"CMakeFiles/OOP_lab2.dir/Domain/domain.c.o" \
"CMakeFiles/OOP_lab2.dir/Repository/repository.c.o" \
"CMakeFiles/OOP_lab2.dir/Tests/repository_tests.c.o" \
"CMakeFiles/OOP_lab2.dir/Tests/service_tests.c.o" \
"CMakeFiles/OOP_lab2.dir/UI/ui.c.o" \
"CMakeFiles/OOP_lab2.dir/Service/service.c.o" \
"CMakeFiles/OOP_lab2.dir/Tests/domain_tests.c.o"

# External object files for target OOP_lab2
OOP_lab2_EXTERNAL_OBJECTS =

OOP_lab2: CMakeFiles/OOP_lab2.dir/main.c.o
OOP_lab2: CMakeFiles/OOP_lab2.dir/Domain/domain.c.o
OOP_lab2: CMakeFiles/OOP_lab2.dir/Repository/repository.c.o
OOP_lab2: CMakeFiles/OOP_lab2.dir/Tests/repository_tests.c.o
OOP_lab2: CMakeFiles/OOP_lab2.dir/Tests/service_tests.c.o
OOP_lab2: CMakeFiles/OOP_lab2.dir/UI/ui.c.o
OOP_lab2: CMakeFiles/OOP_lab2.dir/Service/service.c.o
OOP_lab2: CMakeFiles/OOP_lab2.dir/Tests/domain_tests.c.o
OOP_lab2: CMakeFiles/OOP_lab2.dir/build.make
OOP_lab2: CMakeFiles/OOP_lab2.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir="/tmp/OOP_lab2 Dinamic/cmake-build-docker-arm/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_9) "Linking C executable OOP_lab2"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/OOP_lab2.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/OOP_lab2.dir/build: OOP_lab2
.PHONY : CMakeFiles/OOP_lab2.dir/build

CMakeFiles/OOP_lab2.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/OOP_lab2.dir/cmake_clean.cmake
.PHONY : CMakeFiles/OOP_lab2.dir/clean

CMakeFiles/OOP_lab2.dir/depend:
	cd "/tmp/OOP_lab2 Dinamic/cmake-build-docker-arm" && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" "/tmp/OOP_lab2 Dinamic" "/tmp/OOP_lab2 Dinamic" "/tmp/OOP_lab2 Dinamic/cmake-build-docker-arm" "/tmp/OOP_lab2 Dinamic/cmake-build-docker-arm" "/tmp/OOP_lab2 Dinamic/cmake-build-docker-arm/CMakeFiles/OOP_lab2.dir/DependInfo.cmake" --color=$(COLOR)
.PHONY : CMakeFiles/OOP_lab2.dir/depend

