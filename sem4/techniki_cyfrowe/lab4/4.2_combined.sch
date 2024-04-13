DSCH 3.8
VERSION 17.09.2022 07:49:13
BB(66,-5,154,65)
SYM  #light
BB(148,30,154,44)
TITLE 150 44  #NOR
MODEL 49
PROP                                                                                                                                   
REC(149,31,4,4,r)
VIS 1
PIN(150,45,0.000,0.000)NOR
LIG(153,36,153,31)
LIG(153,31,152,30)
LIG(149,31,149,36)
LIG(152,41,152,38)
LIG(151,41,154,41)
LIG(151,43,153,41)
LIG(152,43,154,41)
LIG(148,38,154,38)
LIG(150,38,150,45)
LIG(148,36,148,38)
LIG(154,36,148,36)
LIG(154,38,154,36)
LIG(150,30,149,31)
LIG(152,30,150,30)
FSYM
SYM  #light
BB(148,-5,154,9)
TITLE 150 9  #NAND
MODEL 49
PROP                                                                                                                                   
REC(149,-4,4,4,r)
VIS 1
PIN(150,10,0.000,0.000)NAND
LIG(153,1,153,-4)
LIG(153,-4,152,-5)
LIG(149,-4,149,1)
LIG(152,6,152,3)
LIG(151,6,154,6)
LIG(151,8,153,6)
LIG(152,8,154,6)
LIG(148,3,154,3)
LIG(150,3,150,10)
LIG(148,1,148,3)
LIG(154,1,148,1)
LIG(154,3,154,1)
LIG(150,-5,149,-4)
LIG(152,-5,150,-5)
FSYM
SYM  #42_NAND
BB(105,0,145,30)
TITLE 115 -7  #42_NAND
MODEL 6000
PROP                                                                                                                                   
REC(110,5,30,20,r)
VIS 5
PIN(105,10,0.000,0.000)B
PIN(105,20,0.000,0.000)A
PIN(145,10,0.006,0.006)Y
LIG(105,10,110,10)
LIG(105,20,110,20)
LIG(140,10,145,10)
LIG(110,5,110,25)
LIG(110,5,140,5)
LIG(140,5,140,25)
LIG(140,25,110,25)
VLG module 42_NAND( B,A,Y);
VLG input B,A;
VLG output Y;
VLG wire w5;
VLG nmos #(1) nmos_1(Y,w5,A); // 0.3u 0.05u
VLG nmos #(1) nmos_2(w5,vss,B); // 0.3u 0.05u
VLG pmos #(1) pmos_3(Y,vdd,A); // 0.5u 0.05u
VLG pmos #(1) pmos_4(Y,vdd,B); // 0.5u 0.05u
VLG endmodule
FSYM
SYM  #42_NOR
BB(105,35,145,65)
TITLE 115 28  #42_NOR
MODEL 6000
PROP                                                                                                                                   
REC(110,40,30,20,r)
VIS 5
PIN(105,45,0.000,0.000)B
PIN(105,55,0.000,0.000)A
PIN(145,45,0.006,0.006)Y
LIG(105,45,110,45)
LIG(105,55,110,55)
LIG(140,45,145,45)
LIG(110,40,110,60)
LIG(110,40,140,40)
LIG(140,40,140,60)
LIG(140,60,110,60)
VLG module 42_NOR( B,A,Y);
VLG input B,A;
VLG output Y;
VLG wire w5;
VLG nmos #(1) nmos_1(Y,vss,B); // 0.3u 0.05u
VLG nmos #(1) nmos_2(Y,vss,A); // 0.3u 0.05u
VLG pmos #(1) pmos_3(Y,w5,B); // 0.5u 0.05u
VLG pmos #(1) pmos_4(w5,vdd,A); // 0.5u 0.05u
VLG endmodule
FSYM
SYM  #button
BB(66,51,75,59)
TITLE 70 55  #A
MODEL 59
PROP                                                                                                                                   
REC(67,52,6,6,r)
VIS 1
PIN(75,55,0.000,0.000)A
LIG(74,55,75,55)
LIG(66,59,66,51)
LIG(74,59,66,59)
LIG(74,51,74,59)
LIG(66,51,74,51)
LIG(67,58,67,52)
LIG(73,58,67,58)
LIG(73,52,73,58)
LIG(67,52,73,52)
FSYM
SYM  #button
BB(66,6,75,14)
TITLE 70 10  #B
MODEL 59
PROP                                                                                                                                   
REC(67,7,6,6,r)
VIS 1
PIN(75,10,0.000,0.000)B
LIG(74,10,75,10)
LIG(66,14,66,6)
LIG(74,14,66,14)
LIG(74,6,74,14)
LIG(66,6,74,6)
LIG(67,13,67,7)
LIG(73,13,67,13)
LIG(73,7,73,13)
LIG(67,7,73,7)
FSYM
CNC(95 55)
CNC(85 10)
LIG(145,45,150,45)
LIG(95,55,95,20)
LIG(75,55,95,55)
LIG(95,55,105,55)
LIG(95,20,105,20)
LIG(145,10,150,10)
LIG(85,10,85,45)
LIG(75,10,85,10)
LIG(85,10,105,10)
LIG(85,45,105,45)
FFIG C:\Users\Bartek\Desktop\studia\sem4\techniki_cyfrowe\lab4\4.2_combined.sch
