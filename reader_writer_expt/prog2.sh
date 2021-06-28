#!/usr/bin/env bash

cc prog2_init.c -o prog2_init -pthread
cc prog2_read.c -o prog2_read -pthread
cc prog2_write.c -o prog2_write -pthread
cc prog2_dest.c -o prog2_dest -pthread
./prog2_init
