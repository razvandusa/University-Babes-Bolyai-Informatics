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
CMAKE_SOURCE_DIR = /tmp/lab2_4

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /tmp/lab2_4/cmake-build-docker-arm

# Include any dependencies generated for this target.
include CMakeFiles/lab2_4.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/lab2_4.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/lab2_4.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/lab2_4.dir/flags.make

CMakeFiles/lab2_4.dir/main.c.o: CMakeFiles/lab2_4.dir/flags.make
CMakeFiles/lab2_4.dir/main.c.o: /tmp/lab2_4/main.c
CMakeFiles/lab2_4.dir/main.c.o: CMakeFiles/lab2_4.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/tmp/lab2_4/cmake-build-docker-arm/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/lab2_4.dir/main.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/lab2_4.dir/main.c.o -MF CMakeFiles/lab2_4.dir/main.c.o.d -o CMakeFiles/lab2_4.dir/main.c.o -c /tmp/lab2_4/main.c

CMakeFiles/lab2_4.dir/main.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/lab2_4.dir/main.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /tmp/lab2_4/main.c > CMakeFiles/lab2_4.dir/main.c.i

CMakeFiles/lab2_4.dir/main.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/lab2_4.dir/main.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /tmp/lab2_4/main.c -o CMakeFiles/lab2_4.dir/main.c.s

CMakeFiles/lab2_4.dir/model/participant.c.o: CMakeFiles/lab2_4.dir/flags.make
CMakeFiles/lab2_4.dir/model/participant.c.o: /tmp/lab2_4/model/participant.c
CMakeFiles/lab2_4.dir/model/participant.c.o: CMakeFiles/lab2_4.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/tmp/lab2_4/cmake-build-docker-arm/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building C object CMakeFiles/lab2_4.dir/model/participant.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/lab2_4.dir/model/participant.c.o -MF CMakeFiles/lab2_4.dir/model/participant.c.o.d -o CMakeFiles/lab2_4.dir/model/participant.c.o -c /tmp/lab2_4/model/participant.c

CMakeFiles/lab2_4.dir/model/participant.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/lab2_4.dir/model/participant.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /tmp/lab2_4/model/participant.c > CMakeFiles/lab2_4.dir/model/participant.c.i

CMakeFiles/lab2_4.dir/model/participant.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/lab2_4.dir/model/participant.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /tmp/lab2_4/model/participant.c -o CMakeFiles/lab2_4.dir/model/participant.c.s

CMakeFiles/lab2_4.dir/ui/ui.c.o: CMakeFiles/lab2_4.dir/flags.make
CMakeFiles/lab2_4.dir/ui/ui.c.o: /tmp/lab2_4/ui/ui.c
CMakeFiles/lab2_4.dir/ui/ui.c.o: CMakeFiles/lab2_4.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/tmp/lab2_4/cmake-build-docker-arm/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building C object CMakeFiles/lab2_4.dir/ui/ui.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/lab2_4.dir/ui/ui.c.o -MF CMakeFiles/lab2_4.dir/ui/ui.c.o.d -o CMakeFiles/lab2_4.dir/ui/ui.c.o -c /tmp/lab2_4/ui/ui.c

CMakeFiles/lab2_4.dir/ui/ui.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/lab2_4.dir/ui/ui.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /tmp/lab2_4/ui/ui.c > CMakeFiles/lab2_4.dir/ui/ui.c.i

CMakeFiles/lab2_4.dir/ui/ui.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/lab2_4.dir/ui/ui.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /tmp/lab2_4/ui/ui.c -o CMakeFiles/lab2_4.dir/ui/ui.c.s

CMakeFiles/lab2_4.dir/service/service_participanti.c.o: CMakeFiles/lab2_4.dir/flags.make
CMakeFiles/lab2_4.dir/service/service_participanti.c.o: /tmp/lab2_4/service/service_participanti.c
CMakeFiles/lab2_4.dir/service/service_participanti.c.o: CMakeFiles/lab2_4.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/tmp/lab2_4/cmake-build-docker-arm/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building C object CMakeFiles/lab2_4.dir/service/service_participanti.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/lab2_4.dir/service/service_participanti.c.o -MF CMakeFiles/lab2_4.dir/service/service_participanti.c.o.d -o CMakeFiles/lab2_4.dir/service/service_participanti.c.o -c /tmp/lab2_4/service/service_participanti.c

CMakeFiles/lab2_4.dir/service/service_participanti.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/lab2_4.dir/service/service_participanti.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /tmp/lab2_4/service/service_participanti.c > CMakeFiles/lab2_4.dir/service/service_participanti.c.i

CMakeFiles/lab2_4.dir/service/service_participanti.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/lab2_4.dir/service/service_participanti.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /tmp/lab2_4/service/service_participanti.c -o CMakeFiles/lab2_4.dir/service/service_participanti.c.s

CMakeFiles/lab2_4.dir/repo/repo.c.o: CMakeFiles/lab2_4.dir/flags.make
CMakeFiles/lab2_4.dir/repo/repo.c.o: /tmp/lab2_4/repo/repo.c
CMakeFiles/lab2_4.dir/repo/repo.c.o: CMakeFiles/lab2_4.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/tmp/lab2_4/cmake-build-docker-arm/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building C object CMakeFiles/lab2_4.dir/repo/repo.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/lab2_4.dir/repo/repo.c.o -MF CMakeFiles/lab2_4.dir/repo/repo.c.o.d -o CMakeFiles/lab2_4.dir/repo/repo.c.o -c /tmp/lab2_4/repo/repo.c

CMakeFiles/lab2_4.dir/repo/repo.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/lab2_4.dir/repo/repo.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /tmp/lab2_4/repo/repo.c > CMakeFiles/lab2_4.dir/repo/repo.c.i

CMakeFiles/lab2_4.dir/repo/repo.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/lab2_4.dir/repo/repo.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /tmp/lab2_4/repo/repo.c -o CMakeFiles/lab2_4.dir/repo/repo.c.s

CMakeFiles/lab2_4.dir/util/util.c.o: CMakeFiles/lab2_4.dir/flags.make
CMakeFiles/lab2_4.dir/util/util.c.o: /tmp/lab2_4/util/util.c
CMakeFiles/lab2_4.dir/util/util.c.o: CMakeFiles/lab2_4.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/tmp/lab2_4/cmake-build-docker-arm/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building C object CMakeFiles/lab2_4.dir/util/util.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/lab2_4.dir/util/util.c.o -MF CMakeFiles/lab2_4.dir/util/util.c.o.d -o CMakeFiles/lab2_4.dir/util/util.c.o -c /tmp/lab2_4/util/util.c

CMakeFiles/lab2_4.dir/util/util.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/lab2_4.dir/util/util.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /tmp/lab2_4/util/util.c > CMakeFiles/lab2_4.dir/util/util.c.i

CMakeFiles/lab2_4.dir/util/util.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/lab2_4.dir/util/util.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /tmp/lab2_4/util/util.c -o CMakeFiles/lab2_4.dir/util/util.c.s

CMakeFiles/lab2_4.dir/teste/teste_repo.c.o: CMakeFiles/lab2_4.dir/flags.make
CMakeFiles/lab2_4.dir/teste/teste_repo.c.o: /tmp/lab2_4/teste/teste_repo.c
CMakeFiles/lab2_4.dir/teste/teste_repo.c.o: CMakeFiles/lab2_4.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/tmp/lab2_4/cmake-build-docker-arm/CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Building C object CMakeFiles/lab2_4.dir/teste/teste_repo.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/lab2_4.dir/teste/teste_repo.c.o -MF CMakeFiles/lab2_4.dir/teste/teste_repo.c.o.d -o CMakeFiles/lab2_4.dir/teste/teste_repo.c.o -c /tmp/lab2_4/teste/teste_repo.c

CMakeFiles/lab2_4.dir/teste/teste_repo.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/lab2_4.dir/teste/teste_repo.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /tmp/lab2_4/teste/teste_repo.c > CMakeFiles/lab2_4.dir/teste/teste_repo.c.i

CMakeFiles/lab2_4.dir/teste/teste_repo.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/lab2_4.dir/teste/teste_repo.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /tmp/lab2_4/teste/teste_repo.c -o CMakeFiles/lab2_4.dir/teste/teste_repo.c.s

CMakeFiles/lab2_4.dir/teste/teste_domain.c.o: CMakeFiles/lab2_4.dir/flags.make
CMakeFiles/lab2_4.dir/teste/teste_domain.c.o: /tmp/lab2_4/teste/teste_domain.c
CMakeFiles/lab2_4.dir/teste/teste_domain.c.o: CMakeFiles/lab2_4.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/tmp/lab2_4/cmake-build-docker-arm/CMakeFiles --progress-num=$(CMAKE_PROGRESS_8) "Building C object CMakeFiles/lab2_4.dir/teste/teste_domain.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/lab2_4.dir/teste/teste_domain.c.o -MF CMakeFiles/lab2_4.dir/teste/teste_domain.c.o.d -o CMakeFiles/lab2_4.dir/teste/teste_domain.c.o -c /tmp/lab2_4/teste/teste_domain.c

CMakeFiles/lab2_4.dir/teste/teste_domain.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/lab2_4.dir/teste/teste_domain.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /tmp/lab2_4/teste/teste_domain.c > CMakeFiles/lab2_4.dir/teste/teste_domain.c.i

CMakeFiles/lab2_4.dir/teste/teste_domain.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/lab2_4.dir/teste/teste_domain.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /tmp/lab2_4/teste/teste_domain.c -o CMakeFiles/lab2_4.dir/teste/teste_domain.c.s

CMakeFiles/lab2_4.dir/teste/teste_service.c.o: CMakeFiles/lab2_4.dir/flags.make
CMakeFiles/lab2_4.dir/teste/teste_service.c.o: /tmp/lab2_4/teste/teste_service.c
CMakeFiles/lab2_4.dir/teste/teste_service.c.o: CMakeFiles/lab2_4.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/tmp/lab2_4/cmake-build-docker-arm/CMakeFiles --progress-num=$(CMAKE_PROGRESS_9) "Building C object CMakeFiles/lab2_4.dir/teste/teste_service.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/lab2_4.dir/teste/teste_service.c.o -MF CMakeFiles/lab2_4.dir/teste/teste_service.c.o.d -o CMakeFiles/lab2_4.dir/teste/teste_service.c.o -c /tmp/lab2_4/teste/teste_service.c

CMakeFiles/lab2_4.dir/teste/teste_service.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/lab2_4.dir/teste/teste_service.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /tmp/lab2_4/teste/teste_service.c > CMakeFiles/lab2_4.dir/teste/teste_service.c.i

CMakeFiles/lab2_4.dir/teste/teste_service.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/lab2_4.dir/teste/teste_service.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /tmp/lab2_4/teste/teste_service.c -o CMakeFiles/lab2_4.dir/teste/teste_service.c.s

CMakeFiles/lab2_4.dir/model/validation.c.o: CMakeFiles/lab2_4.dir/flags.make
CMakeFiles/lab2_4.dir/model/validation.c.o: /tmp/lab2_4/model/validation.c
CMakeFiles/lab2_4.dir/model/validation.c.o: CMakeFiles/lab2_4.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/tmp/lab2_4/cmake-build-docker-arm/CMakeFiles --progress-num=$(CMAKE_PROGRESS_10) "Building C object CMakeFiles/lab2_4.dir/model/validation.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/lab2_4.dir/model/validation.c.o -MF CMakeFiles/lab2_4.dir/model/validation.c.o.d -o CMakeFiles/lab2_4.dir/model/validation.c.o -c /tmp/lab2_4/model/validation.c

CMakeFiles/lab2_4.dir/model/validation.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/lab2_4.dir/model/validation.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /tmp/lab2_4/model/validation.c > CMakeFiles/lab2_4.dir/model/validation.c.i

CMakeFiles/lab2_4.dir/model/validation.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/lab2_4.dir/model/validation.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /tmp/lab2_4/model/validation.c -o CMakeFiles/lab2_4.dir/model/validation.c.s

# Object files for target lab2_4
lab2_4_OBJECTS = \
"CMakeFiles/lab2_4.dir/main.c.o" \
"CMakeFiles/lab2_4.dir/model/participant.c.o" \
"CMakeFiles/lab2_4.dir/ui/ui.c.o" \
"CMakeFiles/lab2_4.dir/service/service_participanti.c.o" \
"CMakeFiles/lab2_4.dir/repo/repo.c.o" \
"CMakeFiles/lab2_4.dir/util/util.c.o" \
"CMakeFiles/lab2_4.dir/teste/teste_repo.c.o" \
"CMakeFiles/lab2_4.dir/teste/teste_domain.c.o" \
"CMakeFiles/lab2_4.dir/teste/teste_service.c.o" \
"CMakeFiles/lab2_4.dir/model/validation.c.o"

# External object files for target lab2_4
lab2_4_EXTERNAL_OBJECTS =

lab2_4: CMakeFiles/lab2_4.dir/main.c.o
lab2_4: CMakeFiles/lab2_4.dir/model/participant.c.o
lab2_4: CMakeFiles/lab2_4.dir/ui/ui.c.o
lab2_4: CMakeFiles/lab2_4.dir/service/service_participanti.c.o
lab2_4: CMakeFiles/lab2_4.dir/repo/repo.c.o
lab2_4: CMakeFiles/lab2_4.dir/util/util.c.o
lab2_4: CMakeFiles/lab2_4.dir/teste/teste_repo.c.o
lab2_4: CMakeFiles/lab2_4.dir/teste/teste_domain.c.o
lab2_4: CMakeFiles/lab2_4.dir/teste/teste_service.c.o
lab2_4: CMakeFiles/lab2_4.dir/model/validation.c.o
lab2_4: CMakeFiles/lab2_4.dir/build.make
lab2_4: CMakeFiles/lab2_4.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/tmp/lab2_4/cmake-build-docker-arm/CMakeFiles --progress-num=$(CMAKE_PROGRESS_11) "Linking C executable lab2_4"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/lab2_4.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/lab2_4.dir/build: lab2_4
.PHONY : CMakeFiles/lab2_4.dir/build

CMakeFiles/lab2_4.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/lab2_4.dir/cmake_clean.cmake
.PHONY : CMakeFiles/lab2_4.dir/clean

CMakeFiles/lab2_4.dir/depend:
	cd /tmp/lab2_4/cmake-build-docker-arm && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /tmp/lab2_4 /tmp/lab2_4 /tmp/lab2_4/cmake-build-docker-arm /tmp/lab2_4/cmake-build-docker-arm /tmp/lab2_4/cmake-build-docker-arm/CMakeFiles/lab2_4.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/lab2_4.dir/depend

