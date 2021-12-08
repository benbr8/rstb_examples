#!/bin/bash
cargo build --release
if [ -d ".sim_build" ]; then
	rm -rf .sim_build
fi
mkdir .sim_build
cp ../target/release/libtest_dff.so ../target/release/libtest_dff.vpi
iverilog -o .sim_build/sim.vvp -s dff -g2012 hdl/dff.v
vvp -M ../target/release -m libtest_dff .sim_build/sim.vvp
