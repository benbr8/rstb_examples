#!/bin/bash

cargo build --release
vlog -O4 hdl/mem.v hdl/fifo_fwft.v hdl/axis_fifo.v
vsim -do ../.questa/questa_gui.do -pli ../target/release/libtest_axis_fifo.so axis_fifo