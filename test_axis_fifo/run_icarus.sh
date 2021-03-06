#!/bin/bash

if [ -d ".sim_build" ]; then
	rm -rf .sim_build
fi
mkdir .sim_build

cargo build --release

cp ../target/release/libtest_axis_fifo.so ../target/release/libtest_axis_fifo.vpi
iverilog -o .sim_build/sim.vvp -s axis_fifo -g2012 hdl/dpram.v hdl/fifo_fwft.v hdl/axis_fifo.v
vvp -M ../target/release -m libtest_axis_fifo .sim_build/sim.vvp
