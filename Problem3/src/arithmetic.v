`include "def.v"

module arithmetic(
    input signed [7:0]      a_i,
    input signed [7:0]      b_i,
    input [1:0]             operator_i,
    output reg signed [7:0] result_o,
    output reg overflow
);

    reg signed [15:0] result;

    always @(*) begin
        case (operator_i)
            `ADD: result_o = a_i + b_i;
            `SUB: result_o = a_i - b_i;
            `MUL: begin
                result   = a_i * b_i;
                result_o = result[7:0];
            end
            default: begin
            end
        endcase
        
    end

    always @(*) begin
        case (operator_i)
            `ADD: begin
                if (a_i[7] == b_i[7] && a_i[7] != result_o[7])
                    overflow = 1'b1;
                else
                    overflow = 1'b0;
            end
            `SUB: begin
                // pos - neg = neg
                if (a_i[7] == 1'b0 && b_i[7] == 1'b1 && result_o[7] == 1'b1)
                    overflow = 1'b1;
                // neg - pos = pos
                else if (a_i[7] == 1'b1 && b_i[7] == 1'b0 && result_o[7] == 1'b0)
                    overflow = 1'b1;
                else
                    overflow = 1'b0;
            end
            `MUL: begin
                // check if result[15:7] are the same
                if (result[15] == 1'b0 && |result[15:7] != 1'b0)
                    overflow = 1'b1;
                else if (result[15] == 1'b1 && &result[15:7] != 1'b1)
                    overflow = 1'b1;
                else
                    overflow = 1'b0;
            end
            default: begin
            end
        endcase
    end

endmodule
