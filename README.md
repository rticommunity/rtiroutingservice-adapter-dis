# Distributed Interactive Simulation (DIS) Adapter

This is an RTI Routing Service adapter that facilitates Distributed
Interactive Simulation (DIS)-DDS traffic.

## Cloning Repository

To clone the repository you will need to run git clone as follows to download
both the repository and its submodule dependencies:

```sh
git clone --recurse-submodule https://github.com/rticommunity/rtiroutingservice-adapter-dis.git
```

If you forget to clone the repository with ``--recurse-submodule``, simply run
the following command to pull all the dependencies:

```sh
git submodule update --init --recursive
```

## Building the Adapter

The `src` directory contains the adapter application which parses DIS traffic
and converts it to DDS traffic (and vice versa). You can modify the application
as needed. To build the adapter, use CMake to create the shared object file
which will be used by RTI Routing Service:

```sh
mkdir build
cd build
cmake ..
cmake --build .
```

This will generate a `libDisAdapter.so` file that you will need to add to your
library path, using the appropriate variable for your operating system (i.e.,
`LD_SHARED_LIBRARY` on Linux, `DYLD_LIBRARY_PATH` on macOS, and `Path` on
Windows), so that RTI Routing Service can find it.

## Configuring the adapter

The adapter is configured in `DisRouterConfig.xml`. There is also a backwards
compatible `DisRouterConfig601.xml` file to use with Connext 6.0.1. The first
section allows you to configure which DDS domains you will communicate on,
and which ports/addresses to use for DIS. The rest of the file contains routes
for each DIS PDU to an appropriate DDS Topic, which may be commented out. The
other XML files contain type definitions for various DIS PDUs (currently all
DIS v5 and most v6). To support additional/custom PDU types, define the type in
XML and include it in this config file. You would also need to add the new PDU
to `DisParser.cxx` and rebuild the adapter.

## Running the adapter

To run the adapter, first add the build directory to your library path:

```sh
# Linux
export LD_LIBRARY_PATH=/path/to/build:$LD_LIBRARY_PATH
# macOS
export DYLD_LIBRARY_PATH=/path/to/build:$DYLD_LIBRARY_PATH
# Windows
set "Path=C:\path\to\build;%Path%"
```

And then, from the `config` directory, run RTI Routing Service as follows:

```sh
cd config
/path/to/installation/rtiroutingservice -cfgFile DisRouterConfig.xml -cfgName RoutingService
```

> If you want to enable compatibility with RTI Connext 6.0.1, use the
> `DisRouterConfig601.xml` configuration file:
>
> ```sh
> cd config
> /path/to/installation/rtiroutingservice -cfgFile DisRouterConfig.xml -cfgName RoutingService
> ```
