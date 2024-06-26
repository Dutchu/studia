DSCH 3.8
VERSION 17.09.2022 12:18:13
BB(1,-45,139,40)
SYM  #vss
BB(105,32,115,40)
TITLE 109 37  #vss
MODEL 0
PROP                                                                                                                                    
REC(105,30,0,0,b)
VIS 0
PIN(110,30,0.000,0.000)vss
LIG(110,30,110,35)
LIG(105,35,115,35)
LIG(105,38,107,35)
LIG(107,38,109,35)
LIG(109,38,111,35)
LIG(111,38,113,35)
FSYM
SYM  #button
BB(1,6,10,14)
TITLE 5 10  #B
MODEL 59
PROP                                                                                                                                    
REC(2,7,6,6,r)
VIS 1
PIN(10,10,0.000,0.000)B
LIG(9,10,10,10)
LIG(1,14,1,6)
LIG(9,14,1,14)
LIG(9,6,9,14)
LIG(1,6,9,6)
LIG(2,13,2,7)
LIG(8,13,2,13)
LIG(8,7,8,13)
LIG(2,7,8,7)
FSYM
SYM  #pmos
BB(40,10,60,30)
TITLE 45 15  #pmos
MODEL 902
PROP   0.5u 0.05u MP                                                                                                                               
REC(45,10,15,19,r)
VIS 0
PIN(40,10,0.000,0.000)s
PIN(50,30,0.000,0.000)g
PIN(60,10,0.000,0.000)d
LIG(50,30,50,24)
LIG(50,22,50,22)
LIG(56,20,44,20)
LIG(56,18,44,18)
LIG(44,10,44,18)
LIG(40,10,44,10)
LIG(56,10,56,18)
LIG(60,10,56,10)
VLG pmos pmos(drain,source,gate);
FSYM
SYM  #nmos
BB(90,5,110,25)
TITLE 105 10  #nmos
MODEL 901
PROP   0.3u 0.05u MN                                                                                                                               
REC(91,10,19,15,r)
VIS 0
PIN(110,25,0.000,0.000)s
PIN(90,15,0.000,0.000)g
PIN(110,5,0.000,0.000)d
LIG(100,15,90,15)
LIG(100,21,100,9)
LIG(102,21,102,9)
LIG(110,9,102,9)
LIG(110,5,110,9)
LIG(110,21,102,21)
LIG(110,25,110,21)
VLG nmos nmos(drain,source,gate);
FSYM
SYM  #nmos
BB(90,-30,110,-10)
TITLE 105 -25  #nmos
MODEL 901
PROP   0.3u 0.05u MN                                                                                                                               
REC(91,-25,19,15,r)
VIS 0
PIN(110,-10,0.000,0.000)s
PIN(90,-20,0.000,0.000)g
PIN(110,-30,0.000,0.000)d
LIG(100,-20,90,-20)
LIG(100,-14,100,-26)
LIG(102,-14,102,-26)
LIG(110,-26,102,-26)
LIG(110,-30,110,-26)
LIG(110,-14,102,-14)
LIG(110,-10,110,-14)
VLG nmos nmos(drain,source,gate);
FSYM
SYM  #button
BB(1,-34,10,-26)
TITLE 5 -30  #A
MODEL 59
PROP                                                                                                                                    
REC(2,-33,6,6,r)
VIS 1
PIN(10,-30,0.000,0.000)A
LIG(9,-30,10,-30)
LIG(1,-26,1,-34)
LIG(9,-26,1,-26)
LIG(9,-34,9,-26)
LIG(1,-34,9,-34)
LIG(2,-27,2,-33)
LIG(8,-27,2,-27)
LIG(8,-33,8,-27)
LIG(2,-33,8,-33)
FSYM
SYM  #pmos
BB(40,-30,60,-10)
TITLE 45 -25  #pmos
MODEL 902
PROP   0.5u 0.05u MP                                                                                                                               
REC(45,-30,15,19,r)
VIS 0
PIN(40,-30,0.000,0.000)s
PIN(50,-10,0.000,0.000)g
PIN(60,-30,0.000,0.000)d
LIG(50,-10,50,-16)
LIG(50,-18,50,-18)
LIG(56,-20,44,-20)
LIG(56,-22,44,-22)
LIG(44,-30,44,-22)
LIG(40,-30,44,-30)
LIG(56,-30,56,-22)
LIG(60,-30,56,-30)
VLG pmos pmos(drain,source,gate);
FSYM
SYM  #light
BB(133,-45,139,-31)
TITLE 135 -31  #light1
MODEL 49
PROP                                                                                                                                    
REC(134,-44,4,4,r)
VIS 1
PIN(135,-30,0.000,0.000)out1
LIG(138,-39,138,-44)
LIG(138,-44,137,-45)
LIG(134,-44,134,-39)
LIG(137,-34,137,-37)
LIG(136,-34,139,-34)
LIG(136,-32,138,-34)
LIG(137,-32,139,-34)
LIG(133,-37,139,-37)
LIG(135,-37,135,-30)
LIG(133,-39,133,-37)
LIG(139,-39,133,-39)
LIG(139,-37,139,-39)
LIG(135,-45,134,-44)
LIG(137,-45,135,-45)
FSYM
CNC(70 -30)
CNC(25 -30)
CNC(35 10)
LIG(35,-10,90,-10)
LIG(60,-30,70,-30)
LIG(60,10,70,10)
LIG(70,10,70,-30)
LIG(110,25,110,30)
LIG(110,-10,110,5)
LIG(70,-30,135,-30)
LIG(90,-10,90,15)
LIG(25,30,80,30)
LIG(25,-30,40,-30)
LIG(10,-30,25,-30)
LIG(25,-30,25,30)
LIG(80,-20,90,-20)
LIG(80,30,80,-20)
LIG(35,10,40,10)
LIG(35,10,35,-10)
LIG(10,10,35,10)
FFIG C:\Users\Bartek\Desktop\studia\sem4\techniki_cyfrowe\lab5\5.1.sch
