#//////////////////////////////////////////////////////////////
#//   ____                                                   //
#//  | __ )  ___ _ __  ___ _   _ _ __   ___ _ __ _ __   ___  //
#//  |  _ \ / _ \ '_ \/ __| | | | '_ \ / _ \ '__| '_ \ / __| //
#//  | |_) |  __/ | | \__ \ |_| | |_) |  __/ |  | |_) | (__  //
#//  |____/ \___|_| |_|___/\__,_| .__/ \___|_|  | .__/ \___| //
#//                             |_|             |_|          //
#//////////////////////////////////////////////////////////////
#//                                                          //
#//  Script, 2022                                            //
#//  Created: 19, April, 2022                                //
#//  Modified: 04, July, 2022                                //
#//  file: -                                                 //
#//  -                                                       //
#//  Source:                                                 //
#//  OS: ALL                                                 //
#//  CPU: ALL                                                //
#//                                                          //
#//////////////////////////////////////////////////////////////

PROJECT_NAME = "experimentation"

PARALLEL := 1

GENERATOR := Ninja

CTEST_TIMEOUT := 1500
CTEST_OPTIONS := --output-on-failure --verbose

# LANG := en
# LANG=$(LANG)

DOCKCROSS_IMAGE := android-arm android-arm64 android-x86 android-x86_64 \
	linux-x86 linux-x64 linux-x64-clang \
	linux-arm64 linux-arm64-musl linux-arm64-full \
	linux-armv5 linux-armv5-musl linux-armv5-uclibc \
	linux-m68k-uclibc linux-s390x linux-x64-tinycc \
	linux-armv6 linux-armv6-lts linux-armv6-musl linux-arm64-lts linux-mipsel-lts \
	linux-armv7l-musl linux-armv7 linux-armv7a linux-armv7-lts linux-armv7a-lts linux-x86_64-full linux-mips linux-mips-lts linux-ppc64le \
	linux-riscv64 linux-riscv32 linux-xtensa-uclibc web-wasi \
	windows-static-x86 windows-static-x64 windows-static-x64-posix windows-armv7 windows-shared-x86 windows-shared-x64 windows-shared-x64-posix windows-arm64 \
	manylinux_2_28-x64 manylinux2014-x64 manylinux2014-x86 manylinux2014-aarch64 web-wasm

.PHONY: build
build: base

.PHONY: $(DOCKCROSS_IMAGE)
$(DOCKCROSS_IMAGE):
	docker run --rm dockcross/$@ > ./dockcross-$@
	chmod +x ./dockcross-$@
	./dockcross-$@ cmake -B build/$@ -S . -G $(GENERATOR)
	./dockcross-$@ ninja -C build/$@

.PHONY: docker
docker: $(DOCKCROSS_IMAGE)

.PHONY: all
all: release debug minsizerel coverage relwithdebinfo minsizerel relwithdebinfo release-clang \
	debug-clang base base-clang sanitize sanitize-clang gprof $(DOCKCROSS_IMAGE) docker valgrind gdb

.PHONY: base
base:
	cmake --preset=$@ -G $(GENERATOR)
	cmake --build build/$@
	ctest $(CTEST_OPTIONS) --timeout $(CTEST_TIMEOUT) --parallel $(PARALLEL) --test-dir build/$@

.PHONY: base-clang
base-clang:
	cmake --preset=$@ -G $(GENERATOR)
	cmake --build build/$@
	ctest $(CTEST_OPTIONS) --timeout $(CTEST_TIMEOUT) --parallel $(PARALLEL) --test-dir build/$@

.PHONY: release
release:
	cmake -B build/$@ -S . -G $(GENERATOR) --preset=base -DCMAKE_BUILD_TYPE=Release
	cmake --build build/$@
	ctest $(CTEST_OPTIONS) --timeout $(CTEST_TIMEOUT) --parallel $(PARALLEL) --test-dir build/$@

.PHONY: release-clang
release-clang:
	cmake -B build/$@ -S . -G $(GENERATOR) --preset=base -DCMAKE_BUILD_TYPE=Release \
	-DCMAKE_C_COMPILER=clang -DCMAKE_CXX_COMPILER=clang++
	cmake --build build/$@
	ctest $(CTEST_OPTIONS) --timeout $(CTEST_TIMEOUT) --parallel $(PARALLEL) --test-dir build/$@

.PHONY: debug
debug:
	cmake -B build/$@ -S . -G $(GENERATOR) --preset=dev -DCMAKE_BUILD_TYPE=Debug
	cmake --build build/$@
	ctest $(CTEST_OPTIONS) --timeout $(CTEST_TIMEOUT) --parallel $(PARALLEL) --test-dir build/$@

.PHONY: debug-clang
debug-clang:
	cmake -B build/$@ -S . -G $(GENERATOR) --preset=dev -DCMAKE_BUILD_TYPE=Debug \
	-DCMAKE_C_COMPILER=clang -DCMAKE_CXX_COMPILER=clang++
	cmake --build build/$@
	ctest $(CTEST_OPTIONS) --timeout $(CTEST_TIMEOUT) --parallel $(PARALLEL) --test-dir build/$@

.PHONY: coverage
coverage:
	cmake -B build/$@ -S . -G $(GENERATOR) --preset=dev-coverage -DCMAKE_BUILD_TYPE=Coverage
	cmake --build build/$@
	ctest $(CTEST_OPTIONS) --timeout $(CTEST_TIMEOUT) --parallel $(PARALLEL) --test-dir build/$@
	cmake --build build/$@ --target coverage

.PHONY: sanitize
sanitize:
	cmake -B build/$@ -S . -G $(GENERATOR) --preset=ci-sanitize
	cmake --build build/$@
	ctest $(CTEST_OPTIONS) --timeout $(CTEST_TIMEOUT) --parallel $(PARALLEL) --test-dir build/$@

sanitize-clang:
	cmake -B build/$@ -S . -G $(GENERATOR) --preset=ci-sanitize \
	-DCMAKE_C_COMPILER=clang -DCMAKE_CXX_COMPILER=clang++
	cmake --build build/$@
	ctest $(CTEST_OPTIONS) --timeout $(CTEST_TIMEOUT) --parallel $(PARALLEL) --test-dir build/$@

.PHONY: minsizerel
minsizerel:
	cmake -B build/$@ -S . -G $(GENERATOR) --preset=dev -DCMAKE_BUILD_TYPE=MinSizeRel
	cmake --build build/$@
	ctest $(CTEST_OPTIONS) --timeout $(CTEST_TIMEOUT) --parallel $(PARALLEL) --test-dir build/$@

.PHONY: relwithdebinfo
relwithdebinfo:
	cmake -B build/$@ -S . -G $(GENERATOR) --preset=dev -DCMAKE_BUILD_TYPE=RelWithDebInfo
	cmake --build build/$@
	ctest $(CTEST_OPTIONS) --timeout $(CTEST_TIMEOUT) --parallel $(PARALLEL) --test-dir build/$@

.PHONY: gprof
gprof:
	cmake --preset=$@ -G $(GENERATOR)
	cmake --build build/$@
	@echo "Run executable and after gprof <exe> gmon.out | less"

.PHONY: graph
graph:
	cmake -B build/$@ -S . -G $(GENERATOR) --graphviz=build/$@/graph.dot
	cmake --build build/base
	dot -Tpng -o build/$@/graph.png build/$@/graph.dot

.PHONY: valgrind
valgrind:
	cmake -B build/$@ -S . -G $(GENERATOR) --preset=dev -DCMAKE_BUILD_TYPE=Debug
	cmake --build build/$@
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --verbose --log-file=build/$@/valgrind.log build/$@/bin/$(PROJECT_NAME)

.PHONY: gdb
gdb:
	cmake -B build/$@ -S . -G $(GENERATOR) --preset=dev -DCMAKE_BUILD_TYPE=Debug
	cmake --build build/$@
	gdb build/$@/bin/$(PROJECT_NAME)

.PHONY: lint
lint:
	cmake -D FORMAT_COMMAND=clang-format -P cmake/lint.cmake
	cmake -P cmake/spell.cmake

.PHONY: format
format:
	time find . -regex '.*\.\(cpp\|cxx\|hpp\|hxx\|c\|h\|cu\|cuh\|cuhpp\|tpp\)' -not -path '*/build/*' | parallel clang-format -style=file -i {} \;

.PHONY: cloc
cloc:
	cloc --fullpath --not-match-d="(build|.git)" --not-match-f="(.git)" .

.PHONY: update
update:
	git pull --recurse-submodules --all --progress

.PHONY: clean
clean:
	rm -rf build/*
