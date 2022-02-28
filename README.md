# aiousb-alpha is deprecated. Please see https://github.com/accesio/aiousb-linux
# aiousb

aiousb is the Linux implementation of the [ACCES I/O USB API](https://accesio.com/MANUALS/USB%20Software%20Reference%20Manual.html)
as a linux kernel module and library.

## Install needed packages

```bash
apt install git cmake build-essential libudev-dev
  ```

## Obtaining the source

```bash
git clone https://github.com/accesio/aiousb-alpha aiousb
```

## Build and install

```bash
mkdir build
cd build
cmake ..
make
sudo make install
```


# Using the library
To use the library include aiousb.h in your program. The first call into the library must be `AiousbInit()`. All of the functions are documented in the [ACCES I/O USB API](https://accesio.com/MANUALS/USB%20Software%20Reference%20Manual.html)


The source code in the samples directory is intended as a guide. The source code in the test directory is not intended for general use.

