# Operating System Abstraction Layer

## Introduction

The main goal of this project is to use the pimpl-idiom to hide implementation
details in the header file located declartions. The disclosure of these details
is one of the biggest drawbacks of C++ and can heavily impact the architecture
and layering of the software system in a negative way.

Beside some other techniques like using forward declarations and references or
using interfaces by declaring pure virtual base classes, the pimpl-idiom is a
straight forward solution, which has it's roots in opaque pointers already used
in object oriented programming with the language C.

The pimpl implementation I use is heavily inspired by Herb Sutter's blog:

https://herbsutter.com/gotw/_100/
\
https://herbsutter.com/gotw/_101/

I want to implement an operating system abstraction layer using this idiom and
port it for various embedded (real-time) operating systems like FreeRTOS, MS
Azure RTOS and the Zephyr project's RTOS kernel.

## Implementation and usage

I have already implemented a first prototype using the C++17 thread support
library in another project. In this project I started using the Zephyr
project's example application and modified it to provide the usage of a OSAL
library.

### Prerequisites

Make sure to install the Zephyr SDK according to the documentation:
https://docs.zephyrproject.org/latest/develop/getting_started/index.html#install-the-zephyr-sdk

### Setup Python virtual environment and install west

```shell
cd ~
mkdir zephyr-workspace
python -m venv zephyr-workspace/.venv
source zephyr-workspace/.venv/bin/activate
pip install west
```

### Clone repository and initialize Zephyr workspace

```shell
cd ~/zephyr-workspace
git clone git@github.com:mastergiggi/application.git
west init -l --mf application/west.yml application/
west update
west zephyr-export
```

### Install Python packages

```shell
pip install -r zephyr/scripts/requirements.txt
```

### Build the OSAL example application using the command

```shell
cd application/
west build -p auto -b $BOARD osal-example/
```

where `$BOARD` is the target board (e.g. `native_sim` or `nucleo_f303re`).
