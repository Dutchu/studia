DSCH 3.8
VERSION 17.09.2022 06:07:20
BB(-20,-10,129,70)
SYM  #nand2
BB(10,5,45,25)
TITLE 22 16  #&
MODEL 202
PROP                                                                                                                                   
REC(0,0,0,0, )
VIS 0
PIN(10,20,0.000,0.000)b
PIN(10,10,0.000,0.000)a
PIN(45,15,0.006,0.003)s
LIG(10,20,18,20)
LIG(18,5,18,25)
LIG(37,17,34,21)
LIG(38,15,37,17)
LIG(37,13,38,15)
LIG(34,9,37,13)
LIG(29,6,34,9)
LIG(34,21,29,24)
LIG(29,24,18,25)
LIG(18,5,29,6)
LIG(10,10,18,10)
LIG(42,15,45,15)
LIG(40,15,40,15)
VLG nand nand2(out,a,b);
FSYM
SYM  #nand2
BB(10,45,45,65)
TITLE 22 56  #&
MODEL 202
PROP                                                                                                                                   
REC(0,0,0,0, )
VIS 0
PIN(10,60,0.000,0.000)b
PIN(10,50,0.000,0.000)a
PIN(45,55,0.006,0.003)s
LIG(10,60,18,60)
LIG(18,45,18,65)
LIG(37,57,34,61)
LIG(38,55,37,57)
LIG(37,53,38,55)
LIG(34,49,37,53)
LIG(29,46,34,49)
LIG(34,61,29,64)
LIG(29,64,18,65)
LIG(18,45,29,46)
LIG(10,50,18,50)
LIG(42,55,45,55)
LIG(40,55,40,55)
VLG nand nand2(out,a,b);
FSYM
SYM  #light
BB(123,40,129,54)
TITLE 125 54  #~Q
MODEL 49
PROP                                                                                                                                   
REC(124,41,4,4,r)
VIS 1
PIN(125,55,0.000,0.000)~Q
LIG(128,46,128,41)
LIG(128,41,127,40)
LIG(124,41,124,46)
LIG(127,51,127,48)
LIG(126,51,129,51)
LIG(126,53,128,51)
LIG(127,53,129,51)
LIG(123,48,129,48)
LIG(125,48,125,55)
LIG(123,46,123,48)
LIG(129,46,123,46)
LIG(129,48,129,46)
LIG(125,40,124,41)
LIG(127,40,125,40)
FSYM
SYM  #light
BB(123,-10,129,4)
TITLE 125 4  #Q
MODEL 49
PROP                                                                                                                                   
REC(124,-9,4,4,r)
VIS 1
PIN(125,5,0.000,0.000)Q
LIG(128,-4,128,-9)
LIG(128,-9,127,-10)
LIG(124,-9,124,-4)
LIG(127,1,127,-2)
LIG(126,1,129,1)
LIG(126,3,128,1)
LIG(127,3,129,1)
LIG(123,-2,129,-2)
LIG(125,-2,125,5)
LIG(123,-4,123,-2)
LIG(129,-4,123,-4)
LIG(129,-2,129,-4)
LIG(125,-10,124,-9)
LIG(127,-10,125,-10)
FSYM
SYM  #nand2
BB(70,50,105,70)
TITLE 82 61  #&
MODEL 202
PROP                                                                                                                                   
REC(0,5,0,0, )
VIS 0
PIN(70,65,0.000,0.000)b
PIN(70,55,0.000,0.000)a
PIN(105,60,0.006,0.003)s
LIG(70,65,78,65)
LIG(78,50,78,70)
LIG(97,62,94,66)
LIG(98,60,97,62)
LIG(97,58,98,60)
LIG(94,54,97,58)
LIG(89,51,94,54)
LIG(94,66,89,69)
LIG(89,69,78,70)
LIG(78,50,89,51)
LIG(70,55,78,55)
LIG(102,60,105,60)
LIG(100,60,100,60)
VLG nand nand2(out,a,b);
FSYM
SYM  #clock
BB(-20,57,-5,63)
TITLE -15 60  #clock1
MODEL 69
PROP   10.00 10.00                                                                                                                               
REC(-18,58,6,4,r)
VIS 1
PIN(-5,60,0.150,0.075)clk1
LIG(-10,60,-5,60)
LIG(-15,58,-17,58)
LIG(-11,58,-13,58)
LIG(-10,57,-10,63)
LIG(-20,63,-20,57)
LIG(-15,62,-15,58)
LIG(-13,58,-13,62)
LIG(-13,62,-15,62)
LIG(-17,62,-19,62)
LIG(-17,58,-17,62)
LIG(-10,63,-20,63)
LIG(-10,57,-20,57)
FSYM
SYM  #nand2
BB(70,0,105,20)
TITLE 82 11  #&
MODEL 202
PROP                                                                                                                                   
REC(0,-5,0,0, )
VIS 0
PIN(70,15,0.000,0.000)b
PIN(70,5,0.000,0.000)a
PIN(105,10,0.006,0.003)s
LIG(70,15,78,15)
LIG(78,0,78,20)
LIG(97,12,94,16)
LIG(98,10,97,12)
LIG(97,8,98,10)
LIG(94,4,97,8)
LIG(89,1,94,4)
LIG(94,16,89,19)
LIG(89,19,78,20)
LIG(78,0,89,1)
LIG(70,5,78,5)
LIG(102,10,105,10)
LIG(100,10,100,10)
VLG nand nand2(out,a,b);
FSYM
SYM  #button
BB(-9,6,0,14)
TITLE -5 10  #D
MODEL 59
PROP                                                                                                                                   
REC(-8,7,6,6,r)
VIS 1
PIN(0,10,0.000,0.000)D
LIG(-1,10,0,10)
LIG(-9,14,-9,6)
LIG(-1,14,-9,14)
LIG(-1,6,-1,14)
LIG(-9,6,-1,6)
LIG(-8,13,-8,7)
LIG(-2,13,-8,13)
LIG(-2,7,-2,13)
LIG(-8,7,-2,7)
FSYM
CNC(115 60)
CNC(0 60)
CNC(55 15)
CNC(115 10)
LIG(0,10,10,10)
LIG(55,65,70,65)
LIG(55,55,55,65)
LIG(45,55,55,55)
LIG(125,60,125,55)
LIG(0,20,10,20)
LIG(115,60,125,60)
LIG(125,10,125,5)
LIG(115,10,125,10)
LIG(0,60,0,20)
LIG(-5,60,0,60)
LIG(0,60,10,60)
LIG(10,50,5,50)
LIG(105,10,115,10)
LIG(115,25,115,10)
LIG(80,25,115,25)
LIG(5,50,5,40)
LIG(5,40,10,35)
LIG(10,35,15,30)
LIG(15,30,55,30)
LIG(45,15,55,15)
LIG(55,15,55,5)
LIG(55,5,70,5)
LIG(55,30,55,15)
LIG(70,15,65,15)
LIG(70,55,65,55)
LIG(115,40,115,60)
LIG(105,60,115,60)
LIG(65,40,65,55)
LIG(65,40,70,35)
LIG(70,35,75,30)
LIG(65,15,65,25)
LIG(65,25,70,30)
LIG(70,30,75,35)
LIG(75,30,80,25)
LIG(75,35,80,40)
LIG(80,40,115,40)
FFIG C:\Users\Bartek\Desktop\studia\sem4\techniki_cyfrowe\lab2\2.4_stat.sch
