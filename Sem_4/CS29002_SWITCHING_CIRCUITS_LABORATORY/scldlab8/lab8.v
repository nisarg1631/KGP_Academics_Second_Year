/* 4-bit RCA START */

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

// Testbench of ripple carry adder

// module test_ripple();
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

/* 4-bit RCA END */


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

// Testbench of multiplexer

// module test_multiplexer();
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

/* MULTIPLEXER END */


/* DFF START */

module master_slave_dff(D, clk, clear, preset, Q, Q_BAR);
    input  clk, D, clear, preset;
    output Q, Q_BAR;

    wire   w1, w2, w3, w4, Q_master, Q_master_BAR, D_BAR, clk_BAR, clear_BAR, preset_BAR;

    not U1 (clear_BAR, clear);
    not U2 (preset_BAR, preset);
    not U3 (clk_BAR, clk);
    not U4 (D_BAR, D);

    nand U5 (w1, D, clk);
    nand U6 (w2, D_BAR, clk);

    nand U7 (Q_master, preset_BAR, Q_master_BAR, w1);
    nand U8 (Q_master_BAR, clear_BAR, Q_master, w2);

    nand U9 (w3, Q_master, clk_BAR);
    nand U10 (w4, Q_master_BAR, clk_BAR);
 
    nand U11 (Q, preset_BAR, Q_BAR, w3);
    nand U12 (Q_BAR, clear_BAR, Q, w4);
endmodule

// Testbench of dff

// module test_dff();
//     reg   clk, D, clear, preset;
//     wire Q, Q_BAR;

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

//     always #2 clk = ~clk;
// endmodule

/* DFF END */
