// DSCH 3.8
// 17.09.2022 00:04:08
// C:\Users\Bartek\Desktop\studia\sem4\techniki_cyfrowe\lab1\1.8.sch

module 18( in1,in2,in3,sum,carry);
 input in1,in2,in3;
 output sum,carry;
 wire w3,w4,w7,w8,w9,w10,w11,w12;
 wire w13,w16;
 nand #(2) nand2_1(carry,w3,w4);
 nand #(2) nand2_2(w4,in1,w7);
 nand #(2) nand2_3(w10,w8,w9);
 nand #(2) nand2_4(w9,w3,w3);
 nand #(2) nand2_5(w12,in1,w11);
 nand #(2) nand2_6(w11,w3,w7);
 nand #(3) nand2_7(w3,w13,in3);
 nand #(3) nand2_8(w3,in2,w16);
 nand #(2) nand2_9(w7,w13,w16);
 nand #(2) nand2_10(sum,w10,w12);
 nand #(3) nand2_11(w3,in2,in3);
 not #(1) inv_12(w8,in1);
 not #(1) inv_13(w16,in3);
 not #(1) inv_14(w13,in2);
endmodule

// Simulation parameters in Verilog Format
always
#200 in1=~in1;
#400 in2=~in2;
#800 in3=~in3;

// Simulation parameters
// in1 CLK 1 1
// in2 CLK 2 2
// in3 CLK 4 4
