// DSCH 3.8
// 17.09.2022 12:03:22
// C:\Users\Bartek\Desktop\studia\sem4\techniki_cyfrowe\lab1\1.7.sch

module 17( B,A,carry,sum);
 input B,A;
 output carry,sum;
 wire ;
 and #(2) and2_1(carry,B,A);
 xor #(2) xor2_2(sum,A,B);
endmodule

// Simulation parameters in Verilog Format
always
#200 B=~B;
#400 A=~A;

// Simulation parameters
// B CLK 1 1
// A CLK 2 2
