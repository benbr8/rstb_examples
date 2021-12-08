#!/bin/bash

vlog -O4 hdl/dut.sv
vsim -do ../.questa/questa_gui.do -pli ../target/release/libtest_concurrent_assertions.so dut