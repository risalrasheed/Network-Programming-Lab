#!/usr/bin/env bash

cc prog1_init.c -o prog1_init -pthread
cc prog1_read.c -o prog1_read -pthread
cc prog1_write.c -o prog1_write -pthread
cc prog1_dest.c -o prog1_dest -pthread
./prog1_init
