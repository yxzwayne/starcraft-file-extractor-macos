# Starcraft File Extractor for MacOS

This is a simple tool to extract files from the Starcraft Remastered and Starcraft 2 game files on MacOS. It is based on the CascLib library and is a simple command line tool.

## Cloning the Repository

To clone the repository along with its submodule [`CascLib`](https://github.com/yxzwayne/CascLib), use the following command:

```sh
git clone --recurse-submodules https://github.com/yxzwayne/starcraft-file-extractor-macos.git
```

## Build Instructions

Because this uses CascLib as submodule, we build it first:

`cd` into the submodule:
```sh
cd src/CascLib
```

build it:
```sh
cmake -L CMakeLists.txt
make
```

go back to the project root:
```sh
# this is just one way to do it
cd ../../..
```

then, proceed with building our program:
```sh
mkdir build
cd build
cmake ..
make
```

## Usage

```sh
./extract_audio
```

## License

TBD (but will be maximally open anyway)