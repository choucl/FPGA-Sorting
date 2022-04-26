`include "def.v"

module parity_generator(
    input [31:0] data_i,
    output       parity_bit_o
);
    // even parity
    assign parity_bit_o = ^data_i[31:0];

endmodule
