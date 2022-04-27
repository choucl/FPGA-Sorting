`include "def.v"

module sorting(
    input             clk_i,
    input             rst_ni,
    input             start_clear_i, // start signal
    input [31:0]      nums_i,        // 8 4-bit numbers
    output reg        valid_o,       // pull while finishing sorting
    output reg [31:0] sorted_nums_o  // 8 4-bit numbers
);

    // using counting sort
    reg [3:0]  counter;
    reg [3:0]  insert_num;
    reg [63:0] counts;

    // state machine
    reg [1:0 ] cstate;
    parameter  IDLE  = 2'd0,
               COUNT = 2'd1,
               SORT  = 2'd2,
               DONE  = 2'd3;


    // Use while COUNT
    reg [3:0] target_num;

    always @(*) begin
        case (counter)
            4'd0: target_num = nums_i[`ZERO];
            4'd1: target_num = nums_i[`ONE];
            4'd2: target_num = nums_i[`TWO];
            4'd3: target_num = nums_i[`THREE];
            4'd4: target_num = nums_i[`FOUR];
            4'd5: target_num = nums_i[`FIVE];
            4'd6: target_num = nums_i[`SIX];
            4'd7: target_num = nums_i[`SEVEN];
            default: target_num = 4'd0;
        endcase
    end

    // Use while SORT(insert numbers)
    reg [3:0] target_count;

    always @(*) begin
        case (insert_num)
            4'd0:   target_count = counts[`ZERO];
            4'd1:   target_count = counts[`ONE];
            4'd2:   target_count = counts[`TWO];
            4'd3:   target_count = counts[`THREE];
            4'd4:   target_count = counts[`FOUR];
            4'd5:   target_count = counts[`FIVE];
            4'd6:   target_count = counts[`SIX];
            4'd7:   target_count = counts[`SEVEN];
            4'd8:   target_count = counts[`EIGHT];
            4'd9:   target_count = counts[`NINE];
            4'd10:  target_count = counts[`TEN];
            4'd11:  target_count = counts[`ELEVEN];
            4'd12:  target_count = counts[`TWELVE];
            4'd13:  target_count = counts[`THIRTEEN];
            4'd14:  target_count = counts[`FOURTEEN];
            4'd15:  target_count = counts[`FIFTEEN];
        endcase
    end

    // counting sort procedure
    always @(posedge clk_i) begin
        if (rst_ni == 1'b0) begin                     // synchronous reset
            counter       <= 4'd0;
            insert_num    <= 4'd0;
            sorted_nums_o <= 32'd0;
            counts        <= 64'd0;
            valid_o       <= 1'b0;
            cstate        <= IDLE;
        end else if (cstate == IDLE) begin
            if (start_clear_i == 1'b1) begin          // receive start signal
                cstate <= COUNT; 
            end else
                cstate <= cstate;
        end else if (cstate == DONE) begin
            if (start_clear_i == 1'b0) begin          // receive clear signal
                counter       <= 4'd0;
                insert_num    <= 4'd0;
                sorted_nums_o <= 32'd0;
                counts        <= 64'd0;
                valid_o       <= 1'b0;
                cstate        <= IDLE;
            end else
                cstate <= cstate;
        end else if (valid_o == 1'b0) begin
            if (cstate == COUNT) begin          // calculate counts
                case (target_num)
                    4'd0:   counts[`ZERO]     <= counts[`ZERO]     + 4'd1;
                    4'd1:   counts[`ONE]      <= counts[`ONE]      + 4'd1;
                    4'd2:   counts[`TWO]      <= counts[`TWO]      + 4'd1;
                    4'd3:   counts[`THREE]    <= counts[`THREE]    + 4'd1;
                    4'd4:   counts[`FOUR]     <= counts[`FOUR]     + 4'd1;
                    4'd5:   counts[`FIVE]     <= counts[`FIVE]     + 4'd1;
                    4'd6:   counts[`SIX]      <= counts[`SIX]      + 4'd1;
                    4'd7:   counts[`SEVEN]    <= counts[`SEVEN]    + 4'd1;
                    4'd8:   counts[`EIGHT]    <= counts[`EIGHT]    + 4'd1;
                    4'd9:   counts[`NINE]     <= counts[`NINE]     + 4'd1;
                    4'd10:  counts[`TEN]      <= counts[`TEN]      + 4'd1;
                    4'd11:  counts[`ELEVEN]   <= counts[`ELEVEN]   + 4'd1;
                    4'd12:  counts[`TWELVE]   <= counts[`TWELVE]   + 4'd1;
                    4'd13:  counts[`THIRTEEN] <= counts[`THIRTEEN] + 4'd1;
                    4'd14:  counts[`FOURTEEN] <= counts[`FOURTEEN] + 4'd1;
                    4'd15:  counts[`FIFTEEN]  <= counts[`FIFTEEN]  + 4'd1;
                endcase
                if (counter != 4'd7)
                    counter <= counter + 4'd1;
                else begin
                    cstate  <= SORT;
                    counter <= 4'd0;
                end
            // sorting
            // insert_num is the number that will be inserted
            end else if (cstate == SORT) begin
                // if the current number can be inserted
                if (target_count != 4'd0) begin
                    // insert number
                    case (counter)
                        4'd0: sorted_nums_o[`ZERO]  <= insert_num;
                        4'd1: sorted_nums_o[`ONE]   <= insert_num;
                        4'd2: sorted_nums_o[`TWO]   <= insert_num;
                        4'd3: sorted_nums_o[`THREE] <= insert_num;
                        4'd4: sorted_nums_o[`FOUR]  <= insert_num;
                        4'd5: sorted_nums_o[`FIVE]  <= insert_num;
                        4'd6: sorted_nums_o[`SIX]   <= insert_num;
                        4'd7: sorted_nums_o[`SEVEN] <= insert_num;
                        default: sorted_nums_o <= 32'd0;
                    endcase
                    // reduce count
                    case (insert_num)
                        4'd0:   counts[`ZERO]     <= counts[`ZERO]     - 4'd1;
                        4'd1:   counts[`ONE]      <= counts[`ONE]      - 4'd1;
                        4'd2:   counts[`TWO]      <= counts[`TWO]      - 4'd1;
                        4'd3:   counts[`THREE]    <= counts[`THREE]    - 4'd1;
                        4'd4:   counts[`FOUR]     <= counts[`FOUR]     - 4'd1;
                        4'd5:   counts[`FIVE]     <= counts[`FIVE]     - 4'd1;
                        4'd6:   counts[`SIX]      <= counts[`SIX]      - 4'd1;
                        4'd7:   counts[`SEVEN]    <= counts[`SEVEN]    - 4'd1;
                        4'd8:   counts[`EIGHT]    <= counts[`EIGHT]    - 4'd1;
                        4'd9:   counts[`NINE]     <= counts[`NINE]     - 4'd1;
                        4'd10:  counts[`TEN]      <= counts[`TEN]      - 4'd1;
                        4'd11:  counts[`ELEVEN]   <= counts[`ELEVEN]   - 4'd1;
                        4'd12:  counts[`TWELVE]   <= counts[`TWELVE]   - 4'd1;
                        4'd13:  counts[`THIRTEEN] <= counts[`THIRTEEN] - 4'd1;
                        4'd14:  counts[`FOURTEEN] <= counts[`FOURTEEN] - 4'd1;
                        4'd15:  counts[`FIFTEEN]  <= counts[`FIFTEEN]  - 4'd1;
                    endcase
                    counter <= counter + 4'd1;
                end else begin // if the current count = 0, no insertion is needed
                    if (insert_num == 4'd15) begin
                        valid_o <= 1'b1;
                        cstate  <= DONE;
                    end else begin
                        insert_num <= insert_num + 4'd1;
                    end
                end
            end
        end
    end

endmodule
