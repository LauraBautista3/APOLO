//----------------------------------------------------------------------------
//
//----------------------------------------------------------------------------
`timescale 1 ns / 100 ps

module system_tb;

//----------------------------------------------------------------------------
// Parameter (may differ for physical synthesis)
//----------------------------------------------------------------------------
parameter tck              = 10;       // clock period in ns
parameter uart_baud_rate   = 1152000;  // uart baud rate for simulation 

parameter clk_freq = 1000000000 / tck; // Frequenzy in HZ
//----------------------------------------------------------------------------
//
//----------------------------------------------------------------------------
reg        clk;
reg        rst;
wire       led;

wire [7:0] Q;
reg   [7:0] gpio;

//----------------------------------------------------------------------------
// UART STUFF (testbench uart, simulating a comm. partner)
//----------------------------------------------------------------------------
wire         uart_rxd;
wire         uart_txd;

//----------------------------------------------------------------------------
// Device Under Test 
//----------------------------------------------------------------------------
system #(
	.clk_freq(           clk_freq         ),
	.uart_baud_rate(     uart_baud_rate   )
) dut  (
	.clk(          clk    ),
	// Debug
	.rst(          rst    ),
	.led(          led    ),
	// Uart
	.uart_rxd(  uart_rxd  ),
	.uart_txd(  uart_txd  ),
	.gpio_io(Q)
);

/* Clocking device */
initial         clk <= 0;
always #(tck/2) clk <= ~clk;
assign Q = gpio;
/* Simulation setup */
initial begin



	$dumpfile("system_tb.vcd");
	//$monitor("%b,%b,%b,%b",clk,rst,uart_txd,uart_rxd);
	$dumpvars(-1, dut);
	//$dumpvars(-1,clk,rst,uart_txd);
	// reset
	#0  rst <= 1;
	#40 rst <= 0;
 
    gpio <=8'h01;
    #10000 gpio <= 8'h00;
    #88000 gpio <=8'h01;
    #8000 gpio <= 8'h00;
    #36000 gpio <=8'h01;
    #8000 gpio <= 8'h00;
    #36000 gpio <=8'h01;
    #8000 gpio <= 8'h00;
    #36000 gpio <=8'h01;
    #8000 gpio <= 8'h00;
    
    #4000 gpio <=8'h01;
    #4000 gpio <=8'h0;
    #4000 gpio <=8'h01;
    #4000 gpio <=8'h0;
    #4000 gpio <=8'h01;
    #4000 gpio <=8'h0;
    #4000 gpio <=8'h01;
    #4000 gpio <=8'h0;
    
    
    #8000 gpio <=8'h01;

	#(tck*15000) $finish;
end



endmodule
