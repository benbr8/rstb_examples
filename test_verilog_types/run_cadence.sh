#!/bin/bash

xrun -64 hdl/dut.sv -access rwc -loadvpi ../target/release/libtest_verilog_types.so:vpi_entry_point
