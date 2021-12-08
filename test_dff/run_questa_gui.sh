#!/bin/bash

cargo build --release
vlog -O4 hdl/dff.v
vsim -do ../.questa/questa_gui.do -pli ../target/release/libtest_dff.so  dff