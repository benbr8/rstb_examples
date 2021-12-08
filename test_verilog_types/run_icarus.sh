#!/bin/bash

if [ -d ".sim_build" ]; then
	rm -rf .sim_build
fi
mkdir .sim_build
cp ../target/release/libtest_verilog_types.so ../target/release/libtest_verilog_types.vpi
iverilog -o .sim_build/sim.vvp -s dut -g2012 hdl/dut.sv
vvp -M ../target/release -m libtest_verilog_types .sim_build/sim.vvp
