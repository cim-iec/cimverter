model Roonet_NE 
annotation(Diagram(coordinateSystem(extent = {{0.00,0.00},{400.00,-400.00}})), Icon(coordinateSystem(extent = {{160.0,-160.0},{180.0,260.0}})));  
inner ModPowerSystems.System System(f_nom(displayUnit = "Hz") = 50.0, init = "steady", simMode = "steady") 
annotation(Placement(visible = true, transformation(extent = {{0.0,-30.0},{30.0,0.0}}, rotation = 0)));
ModPowerSystems.SinglePhase.Connections.BusBar CIM_N13(Vnom = 20000)
annotation (Placement(visible = true, transformation(extent = {{-8.0,-8.0},{8.0,8.0}}, rotation = 0, origin = {223.8,-138.0})));
ModPowerSystems.SinglePhase.Connections.BusBar CIM_N12(Vnom = 20000)
annotation (Placement(visible = true, transformation(extent = {{-8.0,-8.0},{8.0,8.0}}, rotation = 0, origin = {229.8,-98.0})));
ModPowerSystems.SinglePhase.Connections.BusBar CIM_N14(Vnom = 20000)
annotation (Placement(visible = true, transformation(extent = {{-8.0,-8.0},{8.0,8.0}}, rotation = 0, origin = {228.8,-172.0})));
ModPowerSystems.SinglePhase.Connections.BusBar CIM_N0(Vnom = 110000)
annotation (Placement(visible = true, transformation(extent = {{-8.0,-8.0},{8.0,8.0}}, rotation = 0, origin = {153.8,-40.0})));
ModPowerSystems.SinglePhase.Connections.BusBar CIM_N1(Vnom = 20000)
annotation (Placement(visible = true, transformation(extent = {{-8.0,-8.0},{8.0,8.0}}, rotation = 0, origin = {87.9,-94.0})));
ModPowerSystems.SinglePhase.Connections.BusBar CIM_N3(Vnom = 20000)
annotation (Placement(visible = true, transformation(extent = {{-8.0,-8.0},{8.0,8.0}}, rotation = 0, origin = {92.5,-150.5})));
ModPowerSystems.SinglePhase.Connections.BusBar CIM_N2(Vnom = 20000)
annotation (Placement(visible = true, transformation(extent = {{-8.0,-8.0},{8.0,8.0}}, rotation = 0, origin = {86.8,-123.8})));
ModPowerSystems.SinglePhase.Connections.BusBar CIM_N10(Vnom = 20000)
annotation (Placement(visible = true, transformation(extent = {{-8.0,-8.0},{8.0,8.0}}, rotation = 0, origin = {90.8,-216.5})));
ModPowerSystems.SinglePhase.Connections.BusBar CIM_N11(Vnom = 20000)
annotation (Placement(visible = true, transformation(extent = {{-8.0,-8.0},{8.0,8.0}}, rotation = 0, origin = {84.8,-192.0})));
ModPowerSystems.SinglePhase.Connections.BusBar CIM_N5(Vnom = 20000)
annotation (Placement(visible = true, transformation(extent = {{-8.0,-8.0},{8.0,8.0}}, rotation = 0, origin = {43.8,-216.0})));
ModPowerSystems.SinglePhase.Connections.BusBar CIM_N4(Vnom = 20000)
annotation (Placement(visible = true, transformation(extent = {{-8.0,-8.0},{8.0,8.0}}, rotation = 0, origin = {60.8,-173.8})));
ModPowerSystems.SinglePhase.Connections.BusBar CIM_N6(Vnom = 20000)
annotation (Placement(visible = true, transformation(extent = {{-8.0,-8.0},{8.0,8.0}}, rotation = 0, origin = {200.8,-274.0})));
ModPowerSystems.SinglePhase.Connections.BusBar CIM_N7(Vnom = 20000)
annotation (Placement(visible = true, transformation(extent = {{-8.0,-8.0},{8.0,8.0}}, rotation = 0, origin = {198.8,-246.0})));
ModPowerSystems.SinglePhase.Connections.BusBar CIM_N8(Vnom = 20000)
annotation (Placement(visible = true, transformation(extent = {{-8.0,-8.0},{8.0,8.0}}, rotation = 0, origin = {173.8,-216.0})));
ModPowerSystems.SinglePhase.Connections.BusBar CIM_N9(Vnom = 20000)
annotation (Placement(visible = true, transformation(extent = {{-8.0,-8.0},{8.0,8.0}}, rotation = 0, origin = {102.8,-261.0})));
ModPowerSystems.SinglePhase.Sources.Slack CIM_HV_Netz(Vnom(displayUnit = "V") = 110.00, f(displayUnit = "Hz") = 50.0, phiV(displayUnit = "rad") = 0.00)
annotation (Placement(visible = true, transformation(extent = {{-5.0,-5.0},{5.0,5.0}}, rotation = -180, origin = {130.9,-19.2})));
ModPowerSystems.SinglePhase.Loads.PQLoad CIM_Load13_I(Pnom(displayUnit = "W") = 0.00, Qnom(displayUnit = "var") = 0.00, Vnom(displayUnit = "V") = 20.00)
annotation (Placement(visible = true, transformation(extent = {{-8.0,-8.0},{8.0,8.0}}, rotation = 0, origin = {234.8,-145.8})));
ModPowerSystems.SinglePhase.Loads.PQLoad CIM_Load12_H(Pnom(displayUnit = "W") = 0.00, Qnom(displayUnit = "var") = 0.00, Vnom(displayUnit = "V") = 20.00)
annotation (Placement(visible = true, transformation(extent = {{-8.0,-8.0},{8.0,8.0}}, rotation = 0, origin = {237.1,-107.8})));
ModPowerSystems.SinglePhase.Loads.PQLoad CIM_Load12_I(Pnom(displayUnit = "W") = 0.00, Qnom(displayUnit = "var") = 0.00, Vnom(displayUnit = "V") = 20.00)
annotation (Placement(visible = true, transformation(extent = {{-8.0,-8.0},{8.0,8.0}}, rotation = 0, origin = {249.2,-107.8})));
ModPowerSystems.SinglePhase.Loads.PQLoad CIM_Load14_H(Pnom(displayUnit = "W") = 0.00, Qnom(displayUnit = "var") = 0.00, Vnom(displayUnit = "V") = 20.00)
annotation (Placement(visible = true, transformation(extent = {{-8.0,-8.0},{8.0,8.0}}, rotation = 0, origin = {230.8,-181.8})));
ModPowerSystems.SinglePhase.Loads.PQLoad CIM_Load14_I(Pnom(displayUnit = "W") = 0.00, Qnom(displayUnit = "var") = 0.00, Vnom(displayUnit = "V") = 20.00)
annotation (Placement(visible = true, transformation(extent = {{-8.0,-8.0},{8.0,8.0}}, rotation = 0, origin = {242.6,-181.8})));
ModPowerSystems.SinglePhase.Loads.PQLoad CIM_Load1_I(Pnom(displayUnit = "W") = 0.00, Qnom(displayUnit = "var") = 0.00, Vnom(displayUnit = "V") = 20.00)
annotation (Placement(visible = true, transformation(extent = {{-8.0,-8.0},{8.0,8.0}}, rotation = 0, origin = {106.8,-105.8})));
ModPowerSystems.SinglePhase.Loads.PQLoad CIM_Load1_H(Pnom(displayUnit = "W") = 0.00, Qnom(displayUnit = "var") = 0.00, Vnom(displayUnit = "V") = 20.00)
annotation (Placement(visible = true, transformation(extent = {{-8.0,-8.0},{8.0,8.0}}, rotation = 0, origin = {96.8,-105.8})));
ModPowerSystems.SinglePhase.Loads.PQLoad CIM_Load3_H(Pnom(displayUnit = "W") = 0.00, Qnom(displayUnit = "var") = 0.00, Vnom(displayUnit = "V") = 20.00)
annotation (Placement(visible = true, transformation(extent = {{-8.0,-8.0},{8.0,8.0}}, rotation = 0, origin = {94.8,-159.8})));
ModPowerSystems.SinglePhase.Loads.PQLoad CIM_Load3_I(Pnom(displayUnit = "W") = 0.00, Qnom(displayUnit = "var") = 0.00, Vnom(displayUnit = "V") = 20.00)
annotation (Placement(visible = true, transformation(extent = {{-8.0,-8.0},{8.0,8.0}}, rotation = 0, origin = {108.8,-159.8})));
ModPowerSystems.SinglePhase.Loads.PQLoad CIM_Load10_I(Pnom(displayUnit = "W") = 0.00, Qnom(displayUnit = "var") = 0.00, Vnom(displayUnit = "V") = 20.00)
annotation (Placement(visible = true, transformation(extent = {{-8.0,-8.0},{8.0,8.0}}, rotation = 0, origin = {102.8,-227.8})));
ModPowerSystems.SinglePhase.Loads.PQLoad CIM_Load10_H(Pnom(displayUnit = "W") = 0.00, Qnom(displayUnit = "var") = 0.00, Vnom(displayUnit = "V") = 20.00)
annotation (Placement(visible = true, transformation(extent = {{-8.0,-8.0},{8.0,8.0}}, rotation = 0, origin = {88.8,-227.8})));
ModPowerSystems.SinglePhase.Loads.PQLoad CIM_Load11_H(Pnom(displayUnit = "W") = 0.00, Qnom(displayUnit = "var") = 0.00, Vnom(displayUnit = "V") = 20.00)
annotation (Placement(visible = true, transformation(extent = {{-8.0,-8.0},{8.0,8.0}}, rotation = 0, origin = {94.8,-201.8})));
ModPowerSystems.SinglePhase.Loads.PQLoad CIM_Load4_H(Pnom(displayUnit = "W") = 0.00, Qnom(displayUnit = "var") = 0.00, Vnom(displayUnit = "V") = 20.00)
annotation (Placement(visible = true, transformation(extent = {{-8.0,-8.0},{8.0,8.0}}, rotation = 0, origin = {58.8,-184.5})));
ModPowerSystems.SinglePhase.Loads.PQLoad CIM_Load6_H(Pnom(displayUnit = "W") = 0.00, Qnom(displayUnit = "var") = 0.00, Vnom(displayUnit = "V") = 20.00)
annotation (Placement(visible = true, transformation(extent = {{-8.0,-8.0},{8.0,8.0}}, rotation = 0, origin = {212.8,-283.8})));
ModPowerSystems.SinglePhase.Loads.PQLoad CIM_Load7_I(Pnom(displayUnit = "W") = 0.00, Qnom(displayUnit = "var") = 0.00, Vnom(displayUnit = "V") = 20.00)
annotation (Placement(visible = true, transformation(extent = {{-8.0,-8.0},{8.0,8.0}}, rotation = 0, origin = {210.8,-255.8})));
ModPowerSystems.SinglePhase.Loads.PQLoad CIM_Load8_H(Pnom(displayUnit = "W") = 0.00, Qnom(displayUnit = "var") = 0.00, Vnom(displayUnit = "V") = 20.00)
annotation (Placement(visible = true, transformation(extent = {{-8.0,-8.0},{8.0,8.0}}, rotation = 0, origin = {152.8,-225.0})));
ModPowerSystems.SinglePhase.Loads.PQLoad CIM_Load9_I(Pnom(displayUnit = "W") = 0.00, Qnom(displayUnit = "var") = 0.00, Vnom(displayUnit = "V") = 20.00)
annotation (Placement(visible = true, transformation(extent = {{-8.0,-8.0},{8.0,8.0}}, rotation = 0, origin = {112.8,-267.8})));
ModPowerSystems.SinglePhase.Lines.PiLine CIM_L13_14(Imax(displayUnit = "A") = 100.00, Sr(displayUnit = "W") = 1, g = 0, length=2.99, r=0.380, x=0.362, b=0.0002385914)
annotation (Placement(visible = true, transformation(extent = {{-8.0,-8.0},{8.0,8.0}}, rotation = -90, origin = {222.8,-155.0})));
ModPowerSystems.SinglePhase.Lines.PiLine CIM_L12_13(Imax(displayUnit = "A") = 100.00, Sr(displayUnit = "W") = 1, g = 0, length=4.89, r=1.012, x=0.592, b=0.0003902047)
annotation (Placement(visible = true, transformation(extent = {{-8.0,-8.0},{8.0,8.0}}, rotation = -90, origin = {222.8,-118.0})));
ModPowerSystems.SinglePhase.Lines.PiLine CIM_L1_2(Imax(displayUnit = "A") = 100.00, Sr(displayUnit = "W") = 1, g = 0, length=2.82, r=0.584, x=0.341, b=0.0002250260)
annotation (Placement(visible = true, transformation(extent = {{-8.0,-8.0},{8.0,8.0}}, rotation = -90, origin = {86.7,-108.9})));
ModPowerSystems.SinglePhase.Lines.PiLine CIM_L3_4(Imax(displayUnit = "A") = 100.00, Sr(displayUnit = "W") = 1, g = 0, length=0.61, r=0.153, x=0.076, b=0.0000450347)
annotation (Placement(visible = true, transformation(extent = {{-8.0,-8.0},{8.0,8.0}}, rotation = -90, origin = {58.8,-162.2})));
ModPowerSystems.SinglePhase.Lines.PiLine CIM_L2_3(Imax(displayUnit = "A") = 100.00, Sr(displayUnit = "W") = 1, g = 0, length=4.42, r=1.109, x=0.552, b=0.0003263172)
annotation (Placement(visible = true, transformation(extent = {{-8.0,-8.0},{8.0,8.0}}, rotation = -90, origin = {86.5,-137.2})));
ModPowerSystems.SinglePhase.Lines.PiLine CIM_L9_10(Imax(displayUnit = "A") = 100.00, Sr(displayUnit = "W") = 1, g = 0, length=0.77, r=0.193, x=0.096, b=0.0000568471)
annotation (Placement(visible = true, transformation(extent = {{-8.0,-8.0},{8.0,8.0}}, rotation = -90, origin = {84.1,-242.8})));
ModPowerSystems.SinglePhase.Lines.PiLine CIM_L10_11(Imax(displayUnit = "A") = 100.00, Sr(displayUnit = "W") = 1, g = 0, length=0.33, r=0.083, x=0.041, b=0.0000243631)
annotation (Placement(visible = true, transformation(extent = {{-8.0,-8.0},{8.0,8.0}}, rotation = -90, origin = {80.8,-204.2})));
ModPowerSystems.SinglePhase.Lines.PiLine CIM_L5_6(Imax(displayUnit = "A") = 100.00, Sr(displayUnit = "W") = 1, g = 0, length=1.54, r=0.387, x=0.193, b=0.0001136942)
annotation (Placement(visible = true, transformation(extent = {{-8.0,-8.0},{8.0,8.0}}, rotation = -90, origin = {119.8,-268.5})));
ModPowerSystems.SinglePhase.Lines.PiLine CIM_L4_5(Imax(displayUnit = "A") = 100.00, Sr(displayUnit = "W") = 1, g = 0, length=0.56, r=0.141, x=0.070, b=0.0000413434)
annotation (Placement(visible = true, transformation(extent = {{-8.0,-8.0},{8.0,8.0}}, rotation = -90, origin = {44.8,-194.9})));
ModPowerSystems.SinglePhase.Lines.PiLine CIM_L3_8(Imax(displayUnit = "A") = 100.00, Sr(displayUnit = "W") = 1, g = 0, length=1.30, r=0.326, x=0.163, b=0.0000959757)
annotation (Placement(visible = true, transformation(extent = {{-8.0,-8.0},{8.0,8.0}}, rotation = -90, origin = {134.8,-183.2})));
ModPowerSystems.SinglePhase.Lines.PiLine CIM_L7_8(Imax(displayUnit = "A") = 100.00, Sr(displayUnit = "W") = 1, g = 0, length=1.67, r=0.419, x=0.209, b=0.0001232918)
annotation (Placement(visible = true, transformation(extent = {{-8.0,-8.0},{8.0,8.0}}, rotation = -90, origin = {194.8,-231.0})));
ModPowerSystems.SinglePhase.Lines.PiLine CIM_L8_9(Imax(displayUnit = "A") = 100.00, Sr(displayUnit = "W") = 1, g = 0, length=0.32, r=0.080, x=0.040, b=0.0000236248)
annotation (Placement(visible = true, transformation(extent = {{-8.0,-8.0},{8.0,8.0}}, rotation = -90, origin = {124.1,-242.7})));
ModPowerSystems.SinglePhase.Transformers.Transformer CIM_TR1(Vnom1 = 110000.00, Vnom2 = 20000.00, Sr(displayUnit = "W") = 40000000, URr = 12.04, Ukr = 0.63)
annotation (Placement(visible = true, transformation(extent = {{-8.0,-8.0},{8.0,8.0}}, rotation = -90, origin = {86.0,-64.3})));
ModPowerSystems.SinglePhase.Transformers.Transformer CIM_TR2(Vnom1 = 110000.00, Vnom2 = 20000.00, Sr(displayUnit = "W") = 40000000, URr = 12.04, Ukr = 0.62)
annotation (Placement(visible = true, transformation(extent = {{-8.0,-8.0},{8.0,8.0}}, rotation = -90, origin = {222.8,-68.0})));
equation
 connect(CIM_N13.T,CIM_L12_13.T2)
annotation(Line(points={{223.80,-138.00},{223.80,-110.00},{222.80,-110.00}},color = {0,0,0}, smooth = Smooth.None));
 connect(CIM_N13.T,CIM_L13_14.T1)
annotation(Line(points={{223.80,-138.00},{223.80,-163.00},{222.80,-163.00}},color = {0,0,0}, smooth = Smooth.None));
 connect(CIM_N13.T,CIM_Load13_I.T)
annotation(Line(points={{223.80,-138.00},{234.80,-138.00},{234.80,-137.80}},color = {0,0,0}, smooth = Smooth.None));
 connect(CIM_N12.T,CIM_L12_13.T1)
annotation(Line(points={{229.80,-98.00},{229.80,-126.00},{222.80,-126.00}},color = {0,0,0}, smooth = Smooth.None));
 connect(CIM_N12.T,CIM_TR2.T2)
annotation(Line(points={{229.80,-98.00},{229.80,-60.00},{222.80,-60.00}},color = {0,0,0}, smooth = Smooth.None));
 connect(CIM_N12.T,CIM_Load12_H.T)
annotation(Line(points={{229.80,-98.00},{229.80,-99.80},{237.10,-99.80}},color = {0,0,0}, smooth = Smooth.None));
 connect(CIM_N12.T,CIM_Load12_I.T)
annotation(Line(points={{229.80,-98.00},{249.20,-98.00},{249.20,-99.80}},color = {0,0,0}, smooth = Smooth.None));
 connect(CIM_N14.T,CIM_L13_14.T2)
annotation(Line(points={{228.80,-172.00},{228.80,-147.00},{222.80,-147.00}},color = {0,0,0}, smooth = Smooth.None));
 connect(CIM_N14.T,CIM_Load14_H.T)
annotation(Line(points={{228.80,-172.00},{228.80,-173.80},{230.80,-173.80}},color = {0,0,0}, smooth = Smooth.None));
 connect(CIM_N14.T,CIM_Load14_I.T)
annotation(Line(points={{228.80,-172.00},{242.60,-172.00},{242.60,-173.80}},color = {0,0,0}, smooth = Smooth.None));
 connect(CIM_N0.T,CIM_TR1.T1)
annotation(Line(points={{153.80,-40.00},{153.80,-56.15},{86.00,-56.15},{86.00,-72.30}},color = {0,0,0}, smooth = Smooth.None));
 connect(CIM_N0.T,CIM_TR2.T1)
annotation(Line(points={{153.80,-40.00},{153.80,-58.00},{222.80,-58.00},{222.80,-76.00}},color = {0,0,0}, smooth = Smooth.None));
 connect(CIM_N0.T,CIM_HV_Netz.T)
annotation(Line(points={{153.80,-40.00},{153.80,-29.60},{130.90,-29.60},{130.90,-19.20}},color = {0,0,0}, smooth = Smooth.None));
 connect(CIM_N1.T,CIM_L1_2.T1)
annotation(Line(points={{87.90,-94.00},{87.90,-116.90},{86.65,-116.90}},color = {0,0,0}, smooth = Smooth.None));
 connect(CIM_N1.T,CIM_TR1.T2)
annotation(Line(points={{87.90,-94.00},{87.90,-56.30},{86.00,-56.30}},color = {0,0,0}, smooth = Smooth.None));
 connect(CIM_N1.T,CIM_Load1_I.T)
annotation(Line(points={{87.90,-94.00},{106.80,-94.00},{106.80,-97.80}},color = {0,0,0}, smooth = Smooth.None));
 connect(CIM_N1.T,CIM_Load1_H.T)
annotation(Line(points={{87.90,-94.00},{96.80,-94.00},{96.80,-97.80}},color = {0,0,0}, smooth = Smooth.None));
 connect(CIM_N3.T,CIM_L2_3.T2)
annotation(Line(points={{92.50,-150.50},{92.50,-129.15},{86.50,-129.15}},color = {0,0,0}, smooth = Smooth.None));
 connect(CIM_N3.T,CIM_L3_4.T1)
annotation(Line(points={{92.50,-150.50},{92.50,-160.32},{58.80,-160.32},{58.80,-170.15}},color = {0,0,0}, smooth = Smooth.None));
 connect(CIM_N3.T,CIM_L3_8.T2)
annotation(Line(points={{92.50,-150.50},{92.50,-162.88},{134.80,-162.88},{134.80,-175.25}},color = {0,0,0}, smooth = Smooth.None));
 connect(CIM_N3.T,CIM_Load3_H.T)
annotation(Line(points={{92.50,-150.50},{92.50,-151.80},{94.80,-151.80}},color = {0,0,0}, smooth = Smooth.None));
 connect(CIM_N3.T,CIM_Load3_I.T)
annotation(Line(points={{92.50,-150.50},{108.80,-150.50},{108.80,-151.80}},color = {0,0,0}, smooth = Smooth.None));
 connect(CIM_N2.T,CIM_L2_3.T1)
annotation(Line(points={{86.80,-123.80},{86.80,-145.15},{86.50,-145.15}},color = {0,0,0}, smooth = Smooth.None));
 connect(CIM_N2.T,CIM_L1_2.T2)
annotation(Line(points={{86.80,-123.80},{86.80,-100.90},{86.65,-100.90}},color = {0,0,0}, smooth = Smooth.None));
 connect(CIM_N10.T,CIM_L10_11.T2)
annotation(Line(points={{90.80,-216.50},{90.80,-206.38},{80.80,-206.38},{80.80,-196.25}},color = {0,0,0}, smooth = Smooth.None));
 connect(CIM_N10.T,CIM_L9_10.T1)
annotation(Line(points={{90.80,-216.50},{90.80,-250.83},{84.13,-250.83}},color = {0,0,0}, smooth = Smooth.None));
 connect(CIM_N10.T,CIM_Load10_I.T)
annotation(Line(points={{90.80,-216.50},{102.80,-216.50},{102.80,-219.80}},color = {0,0,0}, smooth = Smooth.None));
 connect(CIM_N10.T,CIM_Load10_H.T)
annotation(Line(points={{90.80,-216.50},{90.80,-219.80},{88.80,-219.80}},color = {0,0,0}, smooth = Smooth.None));
 connect(CIM_N11.T,CIM_L10_11.T1)
annotation(Line(points={{84.80,-192.00},{84.80,-212.25},{80.80,-212.25}},color = {0,0,0}, smooth = Smooth.None));
 connect(CIM_N11.T,CIM_Load11_H.T)
annotation(Line(points={{84.80,-192.00},{94.80,-192.00},{94.80,-193.80}},color = {0,0,0}, smooth = Smooth.None));
 connect(CIM_N5.T,CIM_L4_5.T2)
annotation(Line(points={{43.80,-216.00},{43.80,-186.90},{44.80,-186.90}},color = {0,0,0}, smooth = Smooth.None));
 connect(CIM_N5.T,CIM_L5_6.T1)
annotation(Line(points={{43.80,-216.00},{43.80,-246.25},{119.80,-246.25},{119.80,-276.50}},color = {0,0,0}, smooth = Smooth.None));
 connect(CIM_N4.T,CIM_L3_4.T2)
annotation(Line(points={{60.80,-173.80},{60.80,-154.15},{58.80,-154.15}},color = {0,0,0}, smooth = Smooth.None));
 connect(CIM_N4.T,CIM_L4_5.T1)
annotation(Line(points={{60.80,-173.80},{60.80,-188.35},{44.80,-188.35},{44.80,-202.90}},color = {0,0,0}, smooth = Smooth.None));
 connect(CIM_N4.T,CIM_Load4_H.T)
annotation(Line(points={{60.80,-173.80},{60.80,-176.50},{58.80,-176.50}},color = {0,0,0}, smooth = Smooth.None));
 connect(CIM_N6.T,CIM_L5_6.T2)
annotation(Line(points={{200.80,-274.00},{200.80,-267.25},{119.80,-267.25},{119.80,-260.50}},color = {0,0,0}, smooth = Smooth.None));
 connect(CIM_N6.T,CIM_Load6_H.T)
annotation(Line(points={{200.80,-274.00},{212.80,-274.00},{212.80,-275.80}},color = {0,0,0}, smooth = Smooth.None));
 connect(CIM_N7.T,CIM_L7_8.T2)
annotation(Line(points={{198.80,-246.00},{198.80,-223.00},{194.80,-223.00}},color = {0,0,0}, smooth = Smooth.None));
 connect(CIM_N7.T,CIM_Load7_I.T)
annotation(Line(points={{198.80,-246.00},{210.80,-246.00},{210.80,-247.80}},color = {0,0,0}, smooth = Smooth.None));
 connect(CIM_N8.T,CIM_L3_8.T1)
annotation(Line(points={{173.80,-216.00},{173.80,-203.62},{134.80,-203.62},{134.80,-191.25}},color = {0,0,0}, smooth = Smooth.None));
 connect(CIM_N8.T,CIM_L7_8.T1)
annotation(Line(points={{173.80,-216.00},{173.80,-227.50},{194.80,-227.50},{194.80,-239.00}},color = {0,0,0}, smooth = Smooth.None));
 connect(CIM_N8.T,CIM_L8_9.T2)
annotation(Line(points={{173.80,-216.00},{173.80,-225.33},{124.13,-225.33},{124.13,-234.67}},color = {0,0,0}, smooth = Smooth.None));
 connect(CIM_N8.T,CIM_Load8_H.T)
annotation(Line(points={{173.80,-216.00},{152.80,-216.00},{152.80,-217.00}},color = {0,0,0}, smooth = Smooth.None));
 connect(CIM_N9.T,CIM_L8_9.T1)
annotation(Line(points={{102.80,-261.00},{102.80,-255.83},{124.13,-255.83},{124.13,-250.67}},color = {0,0,0}, smooth = Smooth.None));
 connect(CIM_N9.T,CIM_L9_10.T2)
annotation(Line(points={{102.80,-261.00},{102.80,-247.92},{84.13,-247.92},{84.13,-234.83}},color = {0,0,0}, smooth = Smooth.None));
 connect(CIM_N9.T,CIM_Load9_I.T)
annotation(Line(points={{102.80,-261.00},{112.80,-261.00},{112.80,-259.80}},color = {0,0,0}, smooth = Smooth.None));
end Roonet_NE; 
