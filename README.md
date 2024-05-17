# Starcraft File Extractor for MacOS

This is a simple tool to extract files from the Starcraft Remastered and Starcraft 2 game files on MacOS. 
* based on the CascLib library and is a simple command line tool. 
* written such that criteria for selecting the files are flexible so you can make changes based on your use case.
* I simply filtered for audio file formats.

It's actually my first ever cpp program! I made this becasue I wanted clean voice tracks for both English and German so that I can possibly make a "1h of terran base ambience with occasional xxxx notification" type of video. well, that still hasn't gone well since this program has problems. I will write about it below.

## Cloning the Repository

To clone the repository along with its submodule [`CascLib`](https://github.com/yxzwayne/CascLib), use the following command:

```sh
git clone --recurse-submodules https://github.com/yxzwayne/starcraft-file-extractor-macos.git
```

or if you already cloned, use 

```sh
git submodule update --init --recursive
```

## Build Instructions

Because this uses CascLib as submodule, we build it first (if you have already cloned it):

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

Once you compile, run the binary. For example:

```sh
./extract_audio
```

So far, the program asks you for 
* the path to your game data file (which should be fairly straightforward to find on macos if you peep your Applications folder)
* the output path

Notably, the program will create the output directory if it doesn't exist yet (although I don't remember if I wrote it to be recursive... can I even do that anyway??)

It will then create a log at your home directory; oops bug but it should be a simple path fix so you can do it yourself :3

## License

TBD (but will be maximally open anyway)
