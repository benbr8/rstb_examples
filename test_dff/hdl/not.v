`timescale 1ps/1ps

module n (
   input i /* verilator public */,
   output o /* verilator public */
);

   assign o = !i;

endmodule