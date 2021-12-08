#!/bin/bash

cargo build --release
vlog -O4 hdl/dff.v
vsim -c -do ../.questa/questa.do -pli ../target/release/libtest_dff.so dff
