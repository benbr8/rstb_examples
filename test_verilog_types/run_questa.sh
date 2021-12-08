#!/bin/bash

vlog -O4 hdl/dut.sv
vsim -c -do ../.questa/questa.do -pli ../target/release/libtest_verilog_types.so dut
