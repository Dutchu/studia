DSCH 3.8
VERSION 17.09.2022 07:38:32
BB(36,-15,149,80)
SYM  #light
BB(143,25,149,39)
TITLE 145 39  #Y
MODEL 49
PROP                                                                                                                                   
REC(144,26,4,4,r)
VIS 1
PIN(145,40,0.000,0.000)Y
LIG(148,31,148,26)
LIG(148,26,147,25)
LIG(144,26,144,31)
LIG(147,36,147,33)
LIG(146,36,149,36)
LIG(146,38,148,36)
LIG(147,38,149,36)
LIG(143,33,149,33)
LIG(145,33,145,40)
LIG(143,31,143,33)
LIG(149,31,143,31)
LIG(149,33,149,31)
LIG(145,25,144,26)
LIG(147,25,145,25)
FSYM
SYM  #button
BB(36,21,45,29)
TITLE 40 25  #B
MODEL 59
PROP                                                                                                                                   
REC(37,22,6,6,r)
VIS 1
PIN(45,25,0.000,0.000)B
LIG(44,25,45,25)
LIG(36,29,36,21)
LIG(44,29,36,29)
LIG(44,21,44,29)
LIG(36,21,44,21)
LIG(37,28,37,22)
LIG(43,28,37,28)
LIG(43,22,43,28)
LIG(37,22,43,22)
FSYM
SYM  #nmos
BB(100,55,120,75)
TITLE 105 60  #nmos
MODEL 901
PROP   0.3u 0.05u MN                                                                                                                              
REC(100,60,19,15,r)
VIS 0
PIN(100,75,0.000,0.000)s
PIN(120,65,0.000,0.000)g
PIN(100,55,0.000,0.005)d
LIG(110,65,120,65)
LIG(110,71,110,59)
LIG(108,71,108,59)
LIG(100,59,108,59)
LIG(100,55,100,59)
LIG(100,71,108,71)
LIG(100,75,100,71)
VLG nmos nmos(drain,source,gate);
FSYM
SYM  #nmos
BB(70,55,90,75)
TITLE 85 60  #nmos
MODEL 901
PROP   0.3u 0.05u MN                                                                                                                              
REC(71,60,19,15,r)
VIS 0
PIN(90,75,0.000,0.000)s
PIN(70,65,0.000,0.000)g
PIN(90,55,0.000,0.005)d
LIG(80,65,70,65)
LIG(80,71,80,59)
LIG(82,71,82,59)
LIG(90,59,82,59)
LIG(90,55,90,59)
LIG(90,71,82,71)
LIG(90,75,90,71)
VLG nmos nmos(drain,source,gate);
FSYM
SYM  #button
BB(36,-4,45,4)
TITLE 40 0  #A
MODEL 59
PROP                                                                                                                                   
REC(37,-3,6,6,r)
VIS 1
PIN(45,0,0.000,0.000)A
LIG(44,0,45,0)
LIG(36,4,36,-4)
LIG(44,4,36,4)
LIG(44,-4,44,4)
LIG(36,-4,44,-4)
LIG(37,3,37,-3)
LIG(43,3,37,3)
LIG(43,-3,43,3)
LIG(37,-3,43,-3)
FSYM
SYM  #pmos
BB(75,15,95,35)
TITLE 90 20  #pmos
MODEL 902
PROP   0.5u 0.05u MP                                                                                                                              
REC(76,20,19,15,r)
VIS 0
PIN(95,15,0.000,0.000)s
PIN(75,25,0.000,0.000)g
PIN(95,35,0.000,0.005)d
LIG(75,25,81,25)
LIG(83,25,83,25)
LIG(85,31,85,19)
LIG(87,31,87,19)
LIG(95,19,87,19)
LIG(95,15,95,19)
LIG(95,31,87,31)
LIG(95,35,95,31)
VLG pmos pmos(drain,source,gate);
FSYM
SYM  #pmos
BB(75,-10,95,10)
TITLE 90 -5  #pmos
MODEL 902
PROP   0.5u 0.05u MP                                                                                                                              
REC(76,-5,19,15,r)
VIS 0
PIN(95,-10,0.000,0.000)s
PIN(75,0,0.000,0.000)g
PIN(95,10,0.000,0.002)d
LIG(75,0,81,0)
LIG(83,0,83,0)
LIG(85,6,85,-6)
LIG(87,6,87,-6)
LIG(95,-6,87,-6)
LIG(95,-10,95,-6)
LIG(95,6,87,6)
LIG(95,10,95,6)
VLG pmos pmos(drain,source,gate);
FSYM
SYM  #vdd
BB(125,-10,135,0)
TITLE 128 -6  #vdd
MODEL 1
PROP                                                                                                                                   
REC(35,-20,0,0, )
VIS 0
PIN(130,-10,0.000,0.000)vdd
LIG(130,-10,130,-5)
LIG(130,-5,125,-5)
LIG(125,-5,130,0)
LIG(130,0,135,-5)
LIG(135,-5,130,-5)
FSYM
SYM  #vss
BB(130,65,140,73)
TITLE 134 68  #vss
MODEL 0
PROP                                                                                                                                    
REC(130,75,0,0,b)
VIS 0
PIN(135,75,0.000,0.000)vss
LIG(135,75,135,70)
LIG(130,70,140,70)
LIG(130,67,132,70)
LIG(132,67,134,70)
LIG(134,67,136,70)
LIG(136,67,138,70)
FSYM
CNC(95 50)
CNC(95 40)
CNC(55 25)
CNC(60 0)
CNC(95 75)
LIG(145,45,145,40)
LIG(95,75,95,80)
LIG(100,50,100,55)
LIG(130,-15,130,-10)
LIG(55,25,75,25)
LIG(45,25,55,25)
LIG(95,-15,130,-15)
LIG(95,-10,95,-15)
LIG(95,10,95,15)
LIG(140,45,145,45)
LIG(140,40,140,45)
LIG(95,50,100,50)
LIG(95,35,95,40)
LIG(60,0,75,0)
LIG(45,0,60,0)
LIG(60,0,60,65)
LIG(60,65,70,65)
LIG(95,40,140,40)
LIG(90,75,95,75)
LIG(135,80,135,75)
LIG(95,75,100,75)
LIG(95,80,135,80)
LIG(55,25,55,45)
LIG(55,45,125,45)
LIG(125,45,125,65)
LIG(125,65,120,65)
LIG(90,55,90,50)
LIG(90,50,95,50)
LIG(95,40,95,50)
FFIG C:\Users\Bartek\Desktop\studia\sem4\techniki_cyfrowe\lab4\4.2_NOR.sch