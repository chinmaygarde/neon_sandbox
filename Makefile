main:
	mkdir -p build
	cmake -G Ninja -B build -DCMAKE_BUILD_TYPE=Release
	ninja -C build
	ctest -C build

clean:
	rm -rf build

sync:
	git submodule update --init --recursive
