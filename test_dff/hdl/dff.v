`timescale 1ps/1ps

module dff (
   input d /* verilator public */,
   input rstn /* verilator public */,
   input clk /* verilator public */,
   output reg q /* verilator public */
);


   always @ (posedge clk)
   begin
      if (!rstn)
         q <= 0;
      else
         q <= d;
   end

endmodule