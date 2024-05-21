module dff_Struct(clk, D, clear, preset, Q, Q_BAR); //D Flip Flop (-ve edge)   
    
    input  clk, D, clear, preset;   //inputs
    output Q,Q_BAR;                 //outputs
    wire   w0, w1, w2, w3, Q_master, Q_BAR_master, D_BAR; // internal nets
    
    not U0 (clear_BAR, clear); //clear_BAR = ~clear
    not U1 (preset_BAR, preset); //preset_BAR = ~preset

    nand U2 (Q_master,preset_BAR,Q_BAR_master,w0); //Q_master = 1 if preset = 1
    nand U3 (Q_BAR_master,clear_BAR,Q_master,w1); //Q_BAR_master = 1 if clear = 1
 
    not U4 (D_BAR, D); //D_BAR = ~D
    nand U5 (w0,D,clk); //w0 = ~(D.clk)
    nand U6 (w1,D_BAR,clk); //w1 = ~(~D.clk) 
 
    nand U7 (Q_master,preset_BAR,Q_BAR_master,w0); //Q_master(n+1) = ~(~preset.~Q_master(n).w0)
    nand U8 (Q_BAR_master,clear_BAR,Q_master,w1); //~Q_master(n+1) = ~(~clear.Q_master(n+1).w1)

    not U9 (clk_BAR,clk);

    nand U10 (w2,Q_master,clk_BAR);
    nand U11 (w3,Q_BAR_master,clk_BAR);

    nand U12 (Q,Q_BAR,w2); //Q(n+1) = ~(~Q(n).w2)
    nand U13 (Q_BAR,Q,w3); //~Q(n+1) = ~(Q(n+1).w3)
    
endmodule

module mux21_Struct(D0, D1, S, Y);                  //2-1 MUX
    
    input D0, D1, S;    //inputs
    output Y;           //output
    wire w0, w1, S_BAR; //internal nets

    not U0 (S_BAR,S);
    and U1 (w1,D1,S);
    and U2 (w0,D0,S_BAR);
    or U3 (Y,w0,w1);    // Y = S.D1 + ~S.D0

endmodule

module inputShiftReg_Struct(A,shift,preset,clk,clear,O);    //Input Shift Register (8-bit)
	
    input [7:0] A;						//8 bit input
	input shift,preset,clk,clear;		//*usual meanings*
	output O;					        //Current MSB of the input
	wire [6:0] M,Q;						//M represents wire going from MUX to D-FF & Q is output of D-FF
	wire [7:0] Q_BAR;					//Q_BAR is output of D-FF, not needed in this scope presently

	//8 series of D-FF connected to convert parallel input into series output

	dff_Struct D0(clk,A[0],clear,preset,Q[0],Q_BAR[0]);

	mux21_Struct M0(A[1],Q[0],shift,M[0]);
	dff_Struct D1(clk,M[0],clear,preset,Q[1],Q_BAR[1]);

	mux21_Struct M1(A[2],Q[1],shift,M[1]);
	dff_Struct D2(clk,M[1],clear,preset,Q[2],Q_BAR[2]);

	mux21_Struct M2(A[3],Q[2],shift,M[2]);
	dff_Struct D3(clk,M[2],clear,preset,Q[3],Q_BAR[3]);

	mux21_Struct M3(A[4],Q[3],shift,M[3]);
	dff_Struct D4(clk,M[3],clear,preset,Q[4],Q_BAR[4]);

	mux21_Struct M4(A[5],Q[4],shift,M[4]);
	dff_Struct D5(clk,M[4],clear,preset,Q[5],Q_BAR[5]);

	mux21_Struct M5(A[6],Q[5],shift,M[5]);
	dff_Struct D6(clk,M[5],clear,preset,Q[6],Q_BAR[6]);

	mux21_Struct M6(A[7],Q[6],shift,M[6]);
	dff_Struct D7(clk,M[6],clear,preset,O,Q_BAR[7]);

endmodule

module FA_Struct(a, b, cin, cout, sum);             //Full Adder
    
    input  a, b, cin;      // a and b are bits to be added, cin is carry-in
    output cout, sum;      // cout is carry out
    wire   w1, w2, w3, w4; // internal nets

    xor U1  (w1, a, b); //w1 = a^b
    xor U2  (sum, w1, cin); //sum = (a^b)^carry_in
    and U3  (w2, a, b); //w2 = a.b
    and U4  (w3, a, cin); //w3 = a.carry_in
    and U5  (w4, b, cin); //w4 = b.carry_in
    or  U6  (cout, w2, w3, w4); //carry_out = a.b + a.carry_in + b.carry_in
endmodule

module RCA_Struct(A, B, cin, S, cout);              //4-bit Ripple Carry Adder
    
    input[3:0] A,B; // A and B are 4-bit numbers to be added
    input cin;      // carry-in
    output[3:0] S;  // Sum of A and B
    output cout;    // carry-out
    wire c1, c2, c3;// internal nets

    // 4 instantiated 1-bit full adders
    FA_Struct fa0 (A[0], B[0], cin, c1, S[0]);
    FA_Struct fa1 (A[1], B[1], c1, c2, S[1]);
    FA_Struct fa2 (A[2], B[2], c2, c3, S[2]);
    FA_Struct fa3 (A[3], B[3], c3, cout, S[3]);

endmodule

module conditionalAdder_Struct(A,S,cout);           //Conditional 3 Adder (adds 3 to the number if >4)
    
    input[3:0] A;
    output[3:0] S;
    output cout;
    reg[3:0] num;
    wire[3:0] add;
    wire enable,w1,w2,w3;

    //w1- check if 0th bit or 1st bit set
    //w2- checks if number >=5 <=7
    or U0 (w1,A[0],A[1]);
    and U1 (w2,w1,A[2]);

    //if number >4 set enable to 1
    or U2 (enable,w2,A[3]);

    initial begin
        num=4'b0011;
    end
    
    //computing the number to be added (0 or 3)
    and U3 (add[0],enable,num[0]);
    and U4 (add[1],enable,num[1]);
    and U5 (add[2],enable,num[2]);
    and U6 (add[3],enable,num[3]);

    RCA_Struct U (A,add,1'b0,S,cout);

endmodule

module nibbleConvertor_Struct(A,shift,preset,clear,serip,clk,O,serop);  //Nibble Convertor
    
    input[3:0] A;   //Number A can be parallel loaded into the nibble
    input shift, preset, clear, serip,clk; //*usual meanings*
    output[3:0] O;  //output nibble
    output serop;   //serial output

    wire[3:0] Q,Q_BAR,caop;  //Q- Outputs from DFFs, 
                             //caop- Output from Conditional adder  
    wire dummy; //cout from conditional adder

    mux21_Struct M0 (A[0],serip,shift,O[0]);
    mux21_Struct M1 (A[1],caop[0],shift,O[1]);
    mux21_Struct M2 (A[2],caop[1],shift,O[2]);
    mux21_Struct M3 (A[3],caop[2],shift,O[3]);

    dff_Struct D0 (clk,O[0],clear,preset,Q[0],Q_BAR[0]);
    dff_Struct D1 (clk,O[1],clear,preset,Q[1],Q_BAR[1]);
    dff_Struct D2 (clk,O[2],clear,preset,Q[2],Q_BAR[2]);
    dff_Struct D3 (clk,O[3],clear,preset,Q[3],Q_BAR[3]);
    
    conditionalAdder_Struct condS (Q,caop,dummy);
    // always @(clk) $display("inside DFF: %d clk=%d O=%d",$time,clk,O);
   
    or U0 (serop,caop[3],0);   //serial output := MSB of CA output

endmodule

//-----------TOP MODULE-----------

// module test_dff();
//     // Testbench of above code
//     reg   clk, D, clear, preset;
//     wire Q, Q_BAR; // internal nets

//     dff_Struct U1 (clk, D, clear, preset, Q, Q_BAR);

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

// module test_piso();
//     // Testbench of above code
//     reg clk, clear, preset, shift;
//     reg[7:0] X;
//     wire O; // internal nets

//     inputShiftReg_Struct U1 (X, shift, preset, clk, clear, O);

//     initial begin
//         $monitor( "O = %b s = %b clk = %b" ,O,shift,clk);
//         clk = 0;
//         X = 8'b01111110;
//         clear=1;preset=0;shift=0;
//         #1 clear=0; shift=0;
//         #1 shift=1;
//         #12 $finish;
//     end

//     always #1 clk = ~clk;
// endmodule

module top();
	
    reg[7:0] A;
	reg clk,shift,preset,clear;
	reg [3:0] dummy1,dummy2,dummy3;

	wire[3:0] digit1,digit2,digit3;			//eg: number-564 has 5 as digit3, 6 as digit2 and 4 as digit1
	wire O,serout1,serout2,serout3;			//serout is carry over in Nibble converter
	
	//cicuit construction below-

    //instantiating input shift register
	inputShiftReg_Struct PISO (A,shift,preset,clk,clear,O);

    //instantiating 3 nibble convertors for implementing Double Dabble
	nibbleConvertor_Struct N1 (dummy1,shift,preset,clear,O,clk,digit1,serout1);
	nibbleConvertor_Struct N2 (dummy2,shift,preset,clear,serout1,clk,digit2,serout2);
	nibbleConvertor_Struct N3 (dummy3,shift,preset,clear,serout2,clk,digit3,serout3);

	initial begin
		$dumpfile("top.vcd");
		$dumpvars(0,top);
 		clk = 0;

 		A = 8'b10011110;		//change input binary string here for testing

        clear=1;preset=0;shift=0;
        dummy1=4'b0000; dummy2=4'b0000; dummy3=4'b0000;
        #1 clear=0; shift=0;
        #1 shift=1;
 	end
 	
 	initial begin
 		#17 $finish; //stop the clock after 8 complete clock cycles (i.e. 8 bit shifts)
 	end
 	always #1 $monitor("binary= %d | BCD= %b %b %b | BCD in decimal=%d %d %d | PISO=%b | clock=%d", A,digit3,digit2,digit1,digit3,digit2,digit1,O,clk);	
 	always #1 clk = ~clk;		//replicates clock functionality

endmodule

/*
Steps:
1. Change the input from line number 193
2. Run the following commands on terminal for simulating the double dabble algorithm
iverilog scld.v
vvp a.out
*/