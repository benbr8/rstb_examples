`timescale 1ps/1ps

module dff (
   input d /* verilator public */,
   input rstn /* verilator public */,
   input clk /* verilator public */,
   output reg q /* verilator public */
);

   wire notd;

   n not_inst (.i(d), .o(notd));

   always @ (posedge clk)
   begin
      if (!rstn)
         q <= 0;
      else
         q <= notd;
   end

endmodule