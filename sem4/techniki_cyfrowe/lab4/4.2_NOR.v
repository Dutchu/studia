// DSCH 3.8
// 17.09.2022 07:41:10
// C:\Users\Bartek\Desktop\studia\sem4\techniki_cyfrowe\lab4\4.2_NOR.sch

module 42_NOR( B,A,Y);
 input B,A;
 output Y;
 wire w5;
 nmos #(1) nmos_1(Y,vss,B); // 0.3u 0.05u
 nmos #(1) nmos_2(Y,vss,A); // 0.3u 0.05u
 pmos #(1) pmos_3(Y,w5,B); // 0.5u 0.05u
 pmos #(1) pmos_4(w5,vdd,A); // 0.5u 0.05u
endmodule

// Simulation parameters in Verilog Format
always
#200 B=~B;
#400 A=~A;

// Simulation parameters
// B CLK 1 1
// A CLK 2 2
