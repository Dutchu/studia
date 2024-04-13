DSCH 3.8
VERSION 17.09.2022 07:04:49
BB(16,-10,89,70)
SYM  #button
BB(16,26,25,34)
TITLE 20 30  #button1
MODEL 59
PROP                                                                                                                                   
REC(17,27,6,6,r)
VIS 1
PIN(25,30,0.000,0.000)in1
LIG(24,30,25,30)
LIG(16,34,16,26)
LIG(24,34,16,34)
LIG(24,26,24,34)
LIG(16,26,24,26)
LIG(17,33,17,27)
LIG(23,33,17,33)
LIG(23,27,23,33)
LIG(17,27,23,27)
FSYM
SYM  #vdd
BB(60,-10,70,0)
TITLE 63 -4  #vdd
MODEL 1
PROP                                                                                                                                   
REC(0,0,0,0, )
VIS 0
PIN(65,0,0.000,0.000)vdd
LIG(65,0,65,-5)
LIG(65,-5,60,-5)
LIG(60,-5,65,-10)
LIG(65,-10,70,-5)
LIG(70,-5,65,-5)
FSYM
SYM  #light
BB(83,10,89,24)
TITLE 85 24  #light2
MODEL 49
PROP                                                                                                                                   
REC(84,11,4,4,r)
VIS 1
PIN(85,25,0.000,0.000)out2
LIG(88,16,88,11)
LIG(88,11,87,10)
LIG(84,11,84,16)
LIG(87,21,87,18)
LIG(86,21,89,21)
LIG(86,23,88,21)
LIG(87,23,89,21)
LIG(83,18,89,18)
LIG(85,18,85,25)
LIG(83,16,83,18)
LIG(89,16,83,16)
LIG(89,18,89,16)
LIG(85,10,84,11)
LIG(87,10,85,10)
FSYM
SYM  #vss
BB(60,62,70,70)
TITLE 64 67  #vss
MODEL 0
PROP                                                                                                                                    
REC(60,60,0,0,b)
VIS 0
PIN(65,60,0.000,0.000)vss
LIG(65,60,65,65)
LIG(60,65,70,65)
LIG(60,68,62,65)
LIG(62,68,64,65)
LIG(64,68,66,65)
LIG(66,68,68,65)
FSYM
SYM  #nmos
BB(45,35,65,55)
TITLE 60 40  #nmos
MODEL 901
PROP   0.3u 0.05u MN                                                                                                                              
REC(46,40,19,15,r)
VIS 0
PIN(65,55,0.000,0.000)s
PIN(45,45,0.000,0.000)g
PIN(65,35,0.000,0.003)d
LIG(55,45,45,45)
LIG(55,51,55,39)
LIG(57,51,57,39)
LIG(65,39,57,39)
LIG(65,35,65,39)
LIG(65,51,57,51)
LIG(65,55,65,51)
VLG nmos nmos(drain,source,gate);
FSYM
SYM  #pmos
BB(45,5,65,25)
TITLE 60 10  #pmos
MODEL 902
PROP   0.5u 0.05u MP                                                                                                                              
REC(46,10,19,15,r)
VIS 0
PIN(65,5,0.000,0.000)s
PIN(45,15,0.000,0.000)g
PIN(65,25,0.000,0.003)d
LIG(45,15,51,15)
LIG(53,15,53,15)
LIG(55,21,55,9)
LIG(57,21,57,9)
LIG(65,9,57,9)
LIG(65,5,65,9)
LIG(65,21,57,21)
LIG(65,25,65,21)
VLG pmos pmos(drain,source,gate);
FSYM
CNC(40 30)
CNC(40 30)
CNC(65 30)
LIG(25,30,40,30)
LIG(40,30,40,45)
LIG(40,15,40,30)
LIG(85,25,85,30)
LIG(65,30,65,35)
LIG(65,25,65,30)
LIG(65,30,85,30)
LIG(65,55,65,60)
LIG(65,0,65,5)
LIG(40,45,45,45)
LIG(40,15,45,15)
FFIG C:\Users\Bartek\Desktop\studia\sem4\techniki_cyfrowe\lab4\4.1.sch
