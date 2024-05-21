/*
 *  Group 20
 *  SCLD LAB ASSIGNMENT 8
 */


/* 4-BIT RCA START */

// fulladder
module fulladder(X, Y, Ci, S, Co);
    input X, Y, Ci;
    output S, Co;
    wire w1,w2,w3;
    
    xor G1(w1, X, Y);
    xor G2(S, w1, Ci);
    and G3(w2, w1, Ci);
    and G4(w3, X, Y);
    or G5(Co, w2, w3);
endmodule

// 4bit ripple carry adder
module ripple_adder(X0, X1, X2, X3, Y0, Y1, Y2, Y3, Ci, S0, S1, S2, S3, Co);
    input X0, X1, X2, X3, Y0, Y1, Y2, Y3, Ci;
    output S0, S1, S2, S3;
    output Co;
    wire w1, w2, w3;
    
    fulladder u1(X0, Y0, Ci, S0, w1);
    fulladder u2(X1, Y1, w1, S1, w2);
    fulladder u3(X2, Y2, w2, S2, w3);
    fulladder u4(X3, Y3, w3, S3, Co);
endmodule
 
// module test_ripple();
//     // Testbench of ripple carry adder
//     reg[3:0] X, Y;
//     wire[3:0] S;
//     wire Co;

//     ripple_adder R1 (X[0],X[1],X[2],X[3],Y[0],Y[1],Y[2],Y[3],1'b0,S[0],S[1],S[2],S[3],Co);

//     initial begin
//         $display("Testing ripple carry adder");
//         $monitor("S[0] = %b S[1] = %b S[2] = %b S[3] = %b Co = %b",S[0],S[1],S[2],S[3],Co);
//         X[0] = 1'b1;
//         X[1] = 1'b1;
//         X[2] = 1'b1;
//         X[3] = 1'b1;
//         Y[0] = 1'b0;
//         Y[1] = 1'b0;
//         Y[2] = 1'b1;
//         Y[3] = 1'b0;
//     end
// endmodule

/* 4-BIT RCA END */


/* MULTIPLEXER START */

module multiplexer(D0, D1, S, O);
    // if S = 0, O = D0
    // if S = 1, O = D1
    input D0, D1, S;
    output O;
    wire w1, w2, w3;

    not U1 (w1,S);
    and U2 (w2, S, D1);
    and U3 (w3, w1, D0);
    or U4 (O, w2, w3);
endmodule

// module test_multiplexer();
//     // Testbench of multiplexer
//     reg D0, D1, S;
//     wire O;

//     multiplexer M1 (D0,D1,S,O);

//     initial begin
//         $display("Testing multiplexer");
//         $monitor("D0 = %b D1 = %b S = %b O = %b",D0,D1,S,O);
//         D0 = 1'b0;
//         D1 = 1'b1;
//         S = 1'b0;
//     end
// endmodule

// module dff_Struct(clk, D, Q);
//  input  clk, D;
//  output Q;

//  wire   clk, s0, s1, D, Q, Q_BAR; // internal nets
 
//  nand U1 (s0,D,clk);   // U1: local name of the nand instance
//  nand U2 (s1,s0,clk);  // U2: local name of the nand instance
//  nand U3 (Q,Q_BAR,s0); // U3: local name of the nand instance
//  nand U4 (Q_BAR,Q,s1); // U4: local name of the nand instance

// endmodule

/* MULTIPLEXER END */


/* D FLIP FLOP START */

module master_slave_dff(D, clk, clear, preset, Q, Q_BAR);
    input D, clk, clear, preset;
    output Q, Q_BAR;

    wire w1, w2, w3, w4, Q_master, Q_master_BAR, D_BAR, clk_BAR, clear_BAR, preset_BAR;

    not U1 (clear_BAR, clear);
    not U2 (preset_BAR, preset);
    not U3 (D_BAR, D);
    not U4 (clk_BAR, clk);

    nand U5 (Q_master, preset_BAR, Q_master_BAR, w1);
    nand U6 (Q_master_BAR, clear_BAR, Q_master, w2);

    nand U7 (w1, D, clk);
    nand U8 (w2, D_BAR, clk);
    nand U9 (w3, Q_master, clk_BAR);
    nand U10 (w4, Q_master_BAR, clk_BAR);
    
    nand U11 (Q, Q_BAR, w3);
    nand U12 (Q_BAR, Q, w4);
endmodule

// module test_dff();
//     // Testbench of above code
//     reg   clk, D, clear, preset;
//     wire Q, Q_BAR; // internal nets

//     master_slave_dff U1 (D, clk, clear, preset, Q, Q_BAR);

//     initial begin
//         $monitor( "clk = %b D = %b Q = %b Q_BAR = %b" ,clk, D, Q, Q_BAR);
//         clk = 0;
//         D = 0;
//         preset = 0;
//         clear = 1;
//         #1 clear = 0;
//         #1 D = 1;
//         #3 D = 0;
//         #3 D = 0;
//         #3 D = 1;
//         #3 D = 0;
//         #3 $finish;
//     end

//     always #1 clk = ~clk;
// endmodule

/* D FLIP FLOP END */


/* PISO REGISTER START */

module piso_register(X0, X1, X2, X3, X4, X5, X6, X7, parallel_on, clk, clear, preset, O);
    input X0, X1, X2, X3, X4, X5, X6, X7, parallel_on, clk, clear, preset;
    output O;
    wire w0, w1, w2, w3, w4, w5, w6, w_BAR0, w_BAR1, w_BAR2, w_BAR3, w_BAR4, w_BAR5, w_BAR6, w_BAR7;
    wire m0, m1, m2, m3, m4, m5, m6;

    master_slave_dff D0 (X0, clk, clear, preset, w0, w_BAR0);

    multiplexer M1 (w0, X1, parallel_on, m0);
    master_slave_dff D1 (m0, clk, clear, preset, w1, w_BAR1);

    multiplexer M2 (w1, X2, parallel_on, m1);
    master_slave_dff D2 (m1, clk, clear, preset, w2, w_BAR2);

    multiplexer M3 (w2, X3, parallel_on, m2);
    master_slave_dff D3 (m2, clk, clear, preset, w3, w_BAR3);

    multiplexer M4 (w3, X4, parallel_on, m3);
    master_slave_dff D4 (m3, clk, clear, preset, w4, w_BAR4);

    multiplexer M5 (w4, X5, parallel_on, m4);
    master_slave_dff D5 (m4, clk, clear, preset, w5, w_BAR5);

    multiplexer M6 (w5, X6, parallel_on, m5);
    master_slave_dff D6 (m5, clk, clear, preset, w6, w_BAR6);

    multiplexer M7 (w6, X7, parallel_on, m6);
    master_slave_dff D7 (m6, clk, clear, preset, O, w_BAR7);
endmodule

// module test_piso();
//     // Testbench of above code
//     reg clk, clear, preset, X0, X1, X2, X3, X4, X5, X6, X7, parallel_on;
//     wire O; // internal nets

//     piso_register U1 (X0, X1, X2, X3, X4, X5, X6, X7, parallel_on, clk, clear, preset, O);

//     initial begin
//         $monitor( "O = %b p = %b clk = %b" ,O,parallel_on,clk);
//         clk = 0;
//         X0 = 1'b0;
//         X1 = 1'b1;
//         X2 = 1'b1;
//         X3 = 1'b1;
//         X4 = 1'b1;
//         X5 = 1'b1;
//         X6 = 1'b1;
//         X7 = 1'b0;
//         clear=1;preset=0;parallel_on=1;
//         #1 clear=0; parallel_on=1;
//         #1 parallel_on=0;
//         #12 $finish;
//     end

//     always #1 clk = ~clk;
// endmodule

/* PISO REGISTER END */


/* CONDITIONAL ADDER START */

module add_3_if_greater_4(A0,A1,A2,A3,S0,S1,S2,S3,O);
    input A0,A1,A2,A3;
    output S0,S1,S2,S3;
    output O;
    reg[3:0] three;
    wire on,w0,w1,w2,add0,add1,add2,add3;

    or U0 (w0,A0,A1);
    and U1 (w1,w0,A2);
    or U2 (on,w1,A3);

    initial begin
        three=4'b0011;
    end
    
    and U3 (add0,on,three[0]);
    and U4 (add1,on,three[1]);
    and U5 (add2,on,three[2]);
    and U6 (add3,on,three[3]);

    ripple_adder U (A0,A1,A2,A3,add0,add1,add2,add3,1'b0,S0,S1,S2,S3,O);
endmodule

/* CONDITIONAL ADDER END */


/* NIBBLE CONVERTOR START */

module nibble_convertor(A0,A1,A2,A3,parallel_on,preset,clear,serial_input,clk,O0,O1,O2,O3,serial_output);
    input A0, A1, A2, A3, parallel_on, preset, clear, serial_input, clk;
    output O0,O1,O2,O3,serial_output;

    wire Q0,Q1,Q2,Q3,Q_BAR0,Q_BAR1,Q_BAR2,Q_BAR3,carry0,carry1,carry2,carry3; 

    multiplexer M0 (A0,serial_input,parallel_on,O0);
    multiplexer M1 (A1,carry0,parallel_on,O1);
    multiplexer M2 (A2,carry1,parallel_on,O2);
    multiplexer M3 (A3,carry2,parallel_on,O3);

    master_slave_dff D0 (O0,clk,clear,preset,Q0,Q_BAR0);
    master_slave_dff D1 (O1,clk,clear,preset,Q1,Q_BAR1);
    master_slave_dff D2 (O2,clk,clear,preset,Q2,Q_BAR2);
    master_slave_dff D3 (O3,clk,clear,preset,Q3,Q_BAR3);
    
    add_3_if_greater_4 condS (Q0,Q1,Q2,Q3,carry0,carry1,carry2,carry3,temp);
    or U1 (serial_output,carry3,0);
endmodule

/* NIBBLE CONVERTOR END */


/* TOP MODULE START */

module top_module();
	
    reg[7:0] A;
	reg[3:0] temp1,temp2,temp3;
	reg parallel_on,clk,preset,clear;
	wire[3:0] digit1,digit2,digit3;
	wire serial_output0,serial_output1,serial_output2,serial_output3;
	
	piso_register PISO (A[0],A[1],A[2],A[3],A[4],A[5],A[6],A[7],parallel_on,clk,clear,preset,serial_output0);
	nibble_convertor N1 (temp1[0],temp1[1],temp1[2],temp1[3],~parallel_on,preset,clear,serial_output0,clk,digit1[0],digit1[1],digit1[2],digit1[3],serial_output1);
	nibble_convertor N2 (temp2[0],temp2[1],temp2[2],temp2[3],~parallel_on,preset,clear,serial_output1,clk,digit2[0],digit2[1],digit2[2],digit2[3],serial_output2);
	nibble_convertor N3 (temp3[0],temp3[1],temp3[2],temp3[3],~parallel_on,preset,clear,serial_output2,clk,digit3[0],digit3[1],digit3[2],digit3[3],serial_output3);

	initial begin
		$dumpfile("top_module.vcd");
		$dumpvars(0,top_module);
 		clk = 0;

 		A = 8'b01111110;
        $display("Number = %d", A);
        $monitor("bcd = %b %b %b, bcd in decimal = %d %d %d",digit3,digit2,digit1,digit3,digit2,digit1);
        clear=1;
        preset=0;
        parallel_on=1;
        temp1=4'b0000;
        temp2=4'b0000;
        temp3=4'b0000;
        #1 clear=0;
        parallel_on=1;
        #1 parallel_on=0;
 	end
 	
 	initial begin 
        #17 $finish; 
    end
 	always #1 clk = ~clk;
endmodule

/* TOP MODULE END */
