# Copyright (c) 2024 Stefan Giggenbach (https://github.com/mastergiggi)
# SPDX-License-Identifier: Apache-2.0
#
# CMake entry point defined in zephyr/module.yml

zephyr_include_directories(include)

add_subdirectory(lib)
