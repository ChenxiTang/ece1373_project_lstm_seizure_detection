/////////////////////////
//D flip flop          //
/////////////////////////


module dff(
	input wire clk,
	input wire reset,
	input wire in,
	output reg out
);
	always@(posedge clk)begin
		if(reset)begin
			out=0;
		end
		else begin
			out=in;
		end
	
	end


endmodule
            