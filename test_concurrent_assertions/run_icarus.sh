#!/bin/bash

if [ -d ".sim_build" ]; then
	rm -rf .sim_build
fi
mkdir .sim_build

cargo build --release

cp ../target/release/libtest_concurrent_assertions.so ../target/release/libtest_concurrent_assertions.vpi
iverilog -o .sim_build/sim.vvp -s dut -g2012 hdl/dut.sv
vvp -M ../target/release -m libtest_concurrent_assertions .sim_build/sim.vvp
