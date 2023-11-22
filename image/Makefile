all: build

clean: 
	rm -rf build
	mkdir build

build: clean
	(cd build; cmake -DCMAKE_INSTALL_PREFIX:PATH=usr/ ..; make)
