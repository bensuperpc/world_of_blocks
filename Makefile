#//////////////////////////////////////////////////////////////
#//   ____                                                   //
#//  | __ )  ___ _ __  ___ _   _ _ __   ___ _ __ _ __   ___  //
#//  |  _ \ / _ \ '_ \/ __| | | | '_ \ / _ \ '__| '_ \ / __| //
#//  | |_) |  __/ | | \__ \ |_| | |_) |  __/ |  | |_) | (__  //
#//  |____/ \___|_| |_|___/\__,_| .__/ \___|_|  | .__/ \___| //
#//                             |_|             |_|          //
#//////////////////////////////////////////////////////////////
#//                                                          //
#//  sandbox, 2023                               //
#//  Created: 04, June, 2021                                 //
#//  Modified: 18, November, 2023                            //
#//  file: -                                                 //
#//  -                                                       //
#//  Source:                                                 //
#//  OS: ALL                                                 //
#//  CPU: ALL                                                //
#//                                                          //
#//////////////////////////////////////////////////////////////

PROJECT_NAME := world_of_blocks

PARALLEL := 1

GENERATOR := Ninja
PROJECT_ROOT := .

CTEST_TIMEOUT := 1500
CTEST_OPTIONS := --output-on-failure --timeout $(CTEST_TIMEOUT) --parallel $(PARALLEL) --verbose

# LANG := en
# LANG=$(LANG)
# -Werror=float-equal

.PHONY: build
build: base

.PHONY: all
all: release debug minsizerel coverage relwithdebinfo minsizerel relwithdebinfo release-clang \
	debug-clang base base-clang sanitize sanitize-clang gprof $(DOCKCROSS_IMAGE) docker valgrind gdb

.PHONY: base
base:
	cmake -B build/$@ -S $(PROJECT_ROOT) -G $(GENERATOR) --preset=$@
	cmake --build build/$@
	ctest $(CTEST_OPTIONS) --test-dir build/$@

.PHONY: base-clang
base-clang:
	cmake -B build/$@ -S $(PROJECT_ROOT) -G $(GENERATOR) --preset=$@
	cmake --build build/$@
	ctest $(CTEST_OPTIONS) --test-dir build/$@

.PHONY: release
release:
	cmake -B build/$@ -S $(PROJECT_ROOT) -G $(GENERATOR) --preset=base -DCMAKE_BUILD_TYPE=Release
	cmake --build build/$@
	ctest $(CTEST_OPTIONS) --test-dir build/$@

.PHONY: release-clang
release-clang:
	cmake -B build/$@ -S $(PROJECT_ROOT) -G $(GENERATOR) --preset=base -DCMAKE_BUILD_TYPE=Release \
	-DCMAKE_C_COMPILER=clang -DCMAKE_CXX_COMPILER=clang++
	cmake --build build/$@
	ctest $(CTEST_OPTIONS) --test-dir build/$@

.PHONY: debug
debug:
	cmake -B build/$@ -S $(PROJECT_ROOT) -G $(GENERATOR) --preset=dev -DCMAKE_BUILD_TYPE=Debug
	cmake --build build/$@
	ctest $(CTEST_OPTIONS) --test-dir build/$@

.PHONY: debug-clang
debug-clang:
	cmake -B build/$@ -S $(PROJECT_ROOT) -G $(GENERATOR) --preset=dev -DCMAKE_BUILD_TYPE=Debug \
	-DCMAKE_C_COMPILER=clang -DCMAKE_CXX_COMPILER=clang++
	cmake --build build/$@
	ctest $(CTEST_OPTIONS) --test-dir build/$@

.PHONY: coverage
coverage:
	cmake -B build/$@ -S $(PROJECT_ROOT) -G $(GENERATOR) --preset=dev-coverage -DCMAKE_BUILD_TYPE=Coverage
	cmake --build build/$@
	ctest $(CTEST_OPTIONS) --test-dir build/$@
	cmake --build build/$@ --target $@

.PHONY: sanitize
sanitize:
	cmake -B build/$@ -S $(PROJECT_ROOT) -G $(GENERATOR) --preset=ci-sanitize
	cmake --build build/$@
	ctest $(CTEST_OPTIONS) --test-dir build/$@

sanitize-clang:
	cmake -B build/$@ -S $(PROJECT_ROOT) -G $(GENERATOR) --preset=ci-sanitize \
	-DCMAKE_C_COMPILER=clang -DCMAKE_CXX_COMPILER=clang++
	cmake --build build/$@
	ctest $(CTEST_OPTIONS) --test-dir build/$@

.PHONY: minsizerel
minsizerel:
	cmake -B build/$@ -S $(PROJECT_ROOT) -G $(GENERATOR) --preset=dev -DCMAKE_BUILD_TYPE=MinSizeRel
	cmake --build build/$@
	ctest $(CTEST_OPTIONS) --test-dir build/$@

.PHONY: relwithdebinfo
relwithdebinfo:
	cmake -B build/$@ -S $(PROJECT_ROOT) -G $(GENERATOR) --preset=dev -DCMAKE_BUILD_TYPE=RelWithDebInfo
	cmake --build build/$@
	ctest $(CTEST_OPTIONS) --test-dir build/$@

.PHONY: gprof
gprof:
	cmake --preset=$@ -G $(GENERATOR)
	cmake --build build/$@
	@echo "Run executable and after gprof <exe> gmon.out | less"

.PHONY: perf
perf:
	cmake --preset=base -G $(GENERATOR)
	cmake --build build/base
	perf record --all-user -e branch-misses ./build/base/bin/$(PROJECT_NAME)

.PHONY: graph
graph:
	cmake -B build/$@ -S $(PROJECT_ROOT) -G $(GENERATOR) --graphviz=build/$@/graph.dot
	cmake --build build/base
	dot -Tpng -o build/$@/graph.png build/$@/graph.dot

.PHONY: valgrind
valgrind:
	cmake -B build/$@ -S $(PROJECT_ROOT) -G $(GENERATOR) --preset=debugger
	cmake --build build/$@
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --verbose --log-file=build/$@/valgrind.log ./build/$@/bin/$(PROJECT_NAME)

.PHONY: gdb
gdb:
	cmake -B build/$@ -S $(PROJECT_ROOT) -G $(GENERATOR) --preset=debugger
	cmake --build build/$@
	gdb build/$@/bin/$(PROJECT_NAME)

.PHONY: lint
lint:
	cmake -D FORMAT_COMMAND=clang-format -P cmake/lint.cmake
	cmake -P cmake/spell.cmake

.PHONY: format
format:
	time find . -regex '.*\.\(cpp\|cxx\|hpp\|hxx\|c\|h\|cu\|cuh\|cuhpp\|tpp\)' -not -path '*/build/*' -not -path '.git/*' | parallel clang-format -style=file -i {} \;

.PHONY: cloc
cloc:
	cloc --fullpath --not-match-d="(build|.git)" --not-match-f="(.git)" .

.PHONY: update
update:
# 	git submodule update --recursive --remote --force --rebase
	git submodule update --init --recursive
	git pull --recurse-submodules --all --progress

.PHONY: clear
clear:
	rm -rf build/*
