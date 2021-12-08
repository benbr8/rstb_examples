#!/bin/bash

xrun -64 hdl/dut.sv -access rwc -loadvpi ../target/release/libtest_concurrent_assertions.so:vpi_entry_point
