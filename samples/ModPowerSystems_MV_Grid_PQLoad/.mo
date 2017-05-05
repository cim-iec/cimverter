model ../../samples/ModPowerSystems_MV_Grid_PQLoad/ 
annotation(Diagram(coordinateSystem(extent = {{0.00,0.00},{400.00,-400.00}})), Icon(coordinateSystem(extent = {{160.0,-160.0},{180.0,260.0}})));  
inner ModPowerSystems.System System(f_nom(displayUnit = "Hz") = 50.0) 
annotation(Placement(visible = true, transformation(extent = {{0.0,-30.0},{30.0,0.0}}, rotation = 0)));
ModPowerSystems.PhasorSinglePhase.Connections.BusBar CIM_N13(Vnom = 20000.000)
annotation (Placement(visible = true, transformation(extent = {{-8.0,-8.0},{8.0,8.0}}, rotation = 0, origin = {223.8,-138.0})));
ModPowerSystems.PhasorSinglePhase.Connections.BusBar CIM_N12(Vnom = 20000.000)
annotation (Placement(visible = true, transformation(extent = {{-8.0,-8.0},{8.0,8.0}}, rotation = 0, origin = {229.8,-98.0})));
ModPowerSystems.PhasorSinglePhase.Connections.BusBar CIM_N14(Vnom = 20000.000)
annotation (Placement(visible = true, transformation(extent = {{-8.0,-8.0},{8.0,8.0}}, rotation = 0, origin = {228.8,-172.0})));
ModPowerSystems.PhasorSinglePhase.Connections.BusBar CIM_N0(Vnom = 110000.000)
annotation (Placement(visible = true, transformation(extent = {{-8.0,-8.0},{8.0,8.0}}, rotation = 0, origin = {153.8,-40.0})));
ModPowerSystems.PhasorSinglePhase.Connections.BusBar CIM_N1(Vnom = 20000.000)
annotation (Placement(visible = true, transformation(extent = {{-8.0,-8.0},{8.0,8.0}}, rotation = 0, origin = {87.9,-94.0})));
ModPowerSystems.PhasorSinglePhase.Connections.BusBar CIM_N3(Vnom = 20000.000)
annotation (Placement(visible = true, transformation(extent = {{-8.0,-8.0},{8.0,8.0}}, rotation = 0, origin = {92.5,-150.5})));
ModPowerSystems.PhasorSinglePhase.Connections.BusBar CIM_N2(Vnom = 20000.000)
annotation (Placement(visible = true, transformation(extent = {{-8.0,-8.0},{8.0,8.0}}, rotation = 0, origin = {86.8,-123.8})));
ModPowerSystems.PhasorSinglePhase.Connections.BusBar CIM_N10(Vnom = 20000.000)
annotation (Placement(visible = true, transformation(extent = {{-8.0,-8.0},{8.0,8.0}}, rotation = 0, origin = {90.8,-216.5})));
ModPowerSystems.PhasorSinglePhase.Connections.BusBar CIM_N11(Vnom = 20000.000)
annotation (Placement(visible = true, transformation(extent = {{-8.0,-8.0},{8.0,8.0}}, rotation = 0, origin = {84.8,-192.0})));
ModPowerSystems.PhasorSinglePhase.Connections.BusBar CIM_N5(Vnom = 20000.000)
annotation (Placement(visible = true, transformation(extent = {{-8.0,-8.0},{8.0,8.0}}, rotation = 0, origin = {43.8,-216.0})));
ModPowerSystems.PhasorSinglePhase.Connections.BusBar CIM_N4(Vnom = 20000.000)
annotation (Placement(visible = true, transformation(extent = {{-8.0,-8.0},{8.0,8.0}}, rotation = 0, origin = {60.8,-173.8})));
ModPowerSystems.PhasorSinglePhase.Connections.BusBar CIM_N6(Vnom = 20000.000)
annotation (Placement(visible = true, transformation(extent = {{-8.0,-8.0},{8.0,8.0}}, rotation = 0, origin = {200.8,-274.0})));
ModPowerSystems.PhasorSinglePhase.Connections.BusBar CIM_N7(Vnom = 20000.000)
annotation (Placement(visible = true, transformation(extent = {{-8.0,-8.0},{8.0,8.0}}, rotation = 0, origin = {198.8,-246.0})));
ModPowerSystems.PhasorSinglePhase.Connections.BusBar CIM_N8(Vnom = 20000.000)
annotation (Placement(visible = true, transformation(extent = {{-8.0,-8.0},{8.0,8.0}}, rotation = 0, origin = {173.8,-216.0})));
ModPowerSystems.PhasorSinglePhase.Connections.BusBar CIM_N9(Vnom = 20000.000)
annotation (Placement(visible = true, transformation(extent = {{-8.0,-8.0},{8.0,8.0}}, rotation = 0, origin = {102.8,-261.0})));
ModPowerSystems.PhasorSinglePhase.Sources.Slack CIM_HV_Netz(Vnom(displayUnit = "V") = 110000.000, f(displayUnit = "Hz") = 50.0, phiV(displayUnit = "rad") = 0.000)
annotation (Placement(visible = true, transformation(extent = {{-5.0,-5.0},{5.0,5.0}}, rotation = -180, origin = {130.9,-19.2})));
ModPowerSystems.PhasorSinglePhase.Loads.PQLoad CIM_Load13_I(Pnom(displayUnit = "W") = 0.031, Qnom(displayUnit = "var") = 0.019, Vnom(displayUnit = "V") = 20000.000)
annotation (Placement(visible = true, transformation(extent = {{-8.0,-8.0},{8.0,8.0}}, rotation = 0, origin = {234.8,-145.8})));
ModPowerSystems.PhasorSinglePhase.Loads.PQLoad CIM_Load12_H(Pnom(displayUnit = "W") = 14.438, Qnom(displayUnit = "var") = 2.888, Vnom(displayUnit = "V") = 20000.000)
annotation (Placement(visible = true, transformation(extent = {{-8.0,-8.0},{8.0,8.0}}, rotation = 0, origin = {237.1,-107.8})));
ModPowerSystems.PhasorSinglePhase.Loads.PQLoad CIM_Load12_I(Pnom(displayUnit = "W") = 4.813, Qnom(displayUnit = "var") = 1.636, Vnom(displayUnit = "V") = 20000.000)
annotation (Placement(visible = true, transformation(extent = {{-8.0,-8.0},{8.0,8.0}}, rotation = 0, origin = {249.2,-107.8})));
ModPowerSystems.PhasorSinglePhase.Loads.PQLoad CIM_Load14_H(Pnom(displayUnit = "W") = 0.198, Qnom(displayUnit = "var") = 0.050, Vnom(displayUnit = "V") = 20000.000)
annotation (Placement(visible = true, transformation(extent = {{-8.0,-8.0},{8.0,8.0}}, rotation = 0, origin = {230.8,-181.8})));
ModPowerSystems.PhasorSinglePhase.Loads.PQLoad CIM_Load14_I(Pnom(displayUnit = "W") = 0.316, Qnom(displayUnit = "var") = 0.196, Vnom(displayUnit = "V") = 20000.000)
annotation (Placement(visible = true, transformation(extent = {{-8.0,-8.0},{8.0,8.0}}, rotation = 0, origin = {242.6,-181.8})));
ModPowerSystems.PhasorSinglePhase.Loads.PQLoad CIM_Load1_I(Pnom(displayUnit = "W") = 4.772, Qnom(displayUnit = "var") = 0.954, Vnom(displayUnit = "V") = 20000.000)
annotation (Placement(visible = true, transformation(extent = {{-8.0,-8.0},{8.0,8.0}}, rotation = 0, origin = {106.8,-105.8})));
ModPowerSystems.PhasorSinglePhase.Loads.PQLoad CIM_Load1_H(Pnom(displayUnit = "W") = 15.000, Qnom(displayUnit = "var") = 3.100, Vnom(displayUnit = "V") = 20000.000)
annotation (Placement(visible = true, transformation(extent = {{-8.0,-8.0},{8.0,8.0}}, rotation = 0, origin = {96.8,-105.8})));
ModPowerSystems.PhasorSinglePhase.Loads.PQLoad CIM_Load3_H(Pnom(displayUnit = "W") = 0.254, Qnom(displayUnit = "var") = 0.634, Vnom(displayUnit = "V") = 20000.000)
annotation (Placement(visible = true, transformation(extent = {{-8.0,-8.0},{8.0,8.0}}, rotation = 0, origin = {94.8,-159.8})));
ModPowerSystems.PhasorSinglePhase.Loads.PQLoad CIM_Load3_I(Pnom(displayUnit = "W") = 0.224, Qnom(displayUnit = "var") = 0.139, Vnom(displayUnit = "V") = 20000.000)
annotation (Placement(visible = true, transformation(extent = {{-8.0,-8.0},{8.0,8.0}}, rotation = 0, origin = {108.8,-159.8})));
ModPowerSystems.PhasorSinglePhase.Loads.PQLoad CIM_Load10_I(Pnom(displayUnit = "W") = 0.062, Qnom(displayUnit = "var") = 0.038, Vnom(displayUnit = "V") = 20000.000)
annotation (Placement(visible = true, transformation(extent = {{-8.0,-8.0},{8.0,8.0}}, rotation = 0, origin = {102.8,-227.8})));
ModPowerSystems.PhasorSinglePhase.Loads.PQLoad CIM_Load10_H(Pnom(displayUnit = "W") = 0.477, Qnom(displayUnit = "var") = 0.120, Vnom(displayUnit = "V") = 20000.000)
annotation (Placement(visible = true, transformation(extent = {{-8.0,-8.0},{8.0,8.0}}, rotation = 0, origin = {88.8,-227.8})));
ModPowerSystems.PhasorSinglePhase.Loads.PQLoad CIM_Load11_H(Pnom(displayUnit = "W") = 0.302, Qnom(displayUnit = "var") = 0.076, Vnom(displayUnit = "V") = 20000.000)
annotation (Placement(visible = true, transformation(extent = {{-8.0,-8.0},{8.0,8.0}}, rotation = 0, origin = {94.8,-201.8})));
ModPowerSystems.PhasorSinglePhase.Loads.PQLoad CIM_Load4_H(Pnom(displayUnit = "W") = 0.397, Qnom(displayUnit = "var") = 0.099, Vnom(displayUnit = "V") = 20000.000)
annotation (Placement(visible = true, transformation(extent = {{-8.0,-8.0},{8.0,8.0}}, rotation = 0, origin = {58.8,-184.5})));
ModPowerSystems.PhasorSinglePhase.Loads.PQLoad CIM_Load6_H(Pnom(displayUnit = "W") = 0.504, Qnom(displayUnit = "var") = 0.126, Vnom(displayUnit = "V") = 20000.000)
annotation (Placement(visible = true, transformation(extent = {{-8.0,-8.0},{8.0,8.0}}, rotation = 0, origin = {212.8,-283.8})));
ModPowerSystems.PhasorSinglePhase.Loads.PQLoad CIM_Load7_I(Pnom(displayUnit = "W") = 0.070, Qnom(displayUnit = "var") = 0.044, Vnom(displayUnit = "V") = 20000.000)
annotation (Placement(visible = true, transformation(extent = {{-8.0,-8.0},{8.0,8.0}}, rotation = 0, origin = {210.8,-255.8})));
ModPowerSystems.PhasorSinglePhase.Loads.PQLoad CIM_Load8_H(Pnom(displayUnit = "W") = 0.588, Qnom(displayUnit = "var") = 0.147, Vnom(displayUnit = "V") = 20000.000)
annotation (Placement(visible = true, transformation(extent = {{-8.0,-8.0},{8.0,8.0}}, rotation = 0, origin = {152.8,-225.0})));
ModPowerSystems.PhasorSinglePhase.Loads.PQLoad CIM_Load9_I(Pnom(displayUnit = "W") = 0.525, Qnom(displayUnit = "var") = 0.325, Vnom(displayUnit = "V") = 20000.000)
annotation (Placement(visible = true, transformation(extent = {{-8.0,-8.0},{8.0,8.0}}, rotation = 0, origin = {112.8,-267.8})));
ModPowerSystems.PhasorSinglePhase.Lines.PiLine CIM_L13_14(Imax(displayUnit = "A") = 410.000, Sr(displayUnit = "W") = 1.000000, g = 0.000000, length=2.990000, r=0.127000, x=0.121000, b=0.0000797965)
annotation (Placement(visible = true, transformation(extent = {{-8.0,-8.0},{8.0,8.0}}, rotation = -90, origin = {222.8,-155.0})));
ModPowerSystems.PhasorSinglePhase.Lines.PiLine CIM_L12_13(Imax(displayUnit = "A") = 320.000, Sr(displayUnit = "W") = 1.000000, g = 0.000000, length=4.890000, r=0.207000, x=0.121000, b=0.0000797965)
annotation (Placement(visible = true, transformation(extent = {{-8.0,-8.0},{8.0,8.0}}, rotation = -90, origin = {222.8,-118.0})));
ModPowerSystems.PhasorSinglePhase.Lines.PiLine CIM_L1_2(Imax(displayUnit = "A") = 320.000, Sr(displayUnit = "W") = 1.000000, g = 0.000000, length=2.820000, r=0.207000, x=0.121000, b=0.0000797965)
annotation (Placement(visible = true, transformation(extent = {{-8.0,-8.0},{8.0,8.0}}, rotation = -90, origin = {86.7,-108.9})));
ModPowerSystems.PhasorSinglePhase.Lines.PiLine CIM_L3_4(Imax(displayUnit = "A") = 287.000, Sr(displayUnit = "W") = 1.000000, g = 0.000000, length=0.610000, r=0.251000, x=0.125000, b=0.0000738274)
annotation (Placement(visible = true, transformation(extent = {{-8.0,-8.0},{8.0,8.0}}, rotation = -90, origin = {58.8,-162.2})));
ModPowerSystems.PhasorSinglePhase.Lines.PiLine CIM_L2_3(Imax(displayUnit = "A") = 287.000, Sr(displayUnit = "W") = 1.000000, g = 0.000000, length=4.420000, r=0.251000, x=0.125000, b=0.0000738274)
annotation (Placement(visible = true, transformation(extent = {{-8.0,-8.0},{8.0,8.0}}, rotation = -90, origin = {86.5,-137.2})));
ModPowerSystems.PhasorSinglePhase.Lines.PiLine CIM_L9_10(Imax(displayUnit = "A") = 287.000, Sr(displayUnit = "W") = 1.000000, g = 0.000000, length=0.770000, r=0.251000, x=0.125000, b=0.0000738274)
annotation (Placement(visible = true, transformation(extent = {{-8.0,-8.0},{8.0,8.0}}, rotation = -90, origin = {84.1,-242.8})));
ModPowerSystems.PhasorSinglePhase.Lines.PiLine CIM_L10_11(Imax(displayUnit = "A") = 287.000, Sr(displayUnit = "W") = 1.000000, g = 0.000000, length=0.330000, r=0.251000, x=0.125000, b=0.0000738276)
annotation (Placement(visible = true, transformation(extent = {{-8.0,-8.0},{8.0,8.0}}, rotation = -90, origin = {80.8,-204.2})));
ModPowerSystems.PhasorSinglePhase.Lines.PiLine CIM_L5_6(Imax(displayUnit = "A") = 287.000, Sr(displayUnit = "W") = 1.000000, g = 0.000000, length=1.540000, r=0.251000, x=0.125000, b=0.0000738274)
annotation (Placement(visible = true, transformation(extent = {{-8.0,-8.0},{8.0,8.0}}, rotation = -90, origin = {119.8,-268.5})));
ModPowerSystems.PhasorSinglePhase.Lines.PiLine CIM_L4_5(Imax(displayUnit = "A") = 287.000, Sr(displayUnit = "W") = 1.000000, g = 0.000000, length=0.560000, r=0.251000, x=0.125000, b=0.0000738275)
annotation (Placement(visible = true, transformation(extent = {{-8.0,-8.0},{8.0,8.0}}, rotation = -90, origin = {44.8,-194.9})));
ModPowerSystems.PhasorSinglePhase.Lines.PiLine CIM_L3_8(Imax(displayUnit = "A") = 287.000, Sr(displayUnit = "W") = 1.000000, g = 0.000000, length=1.300000, r=0.251000, x=0.125000, b=0.0000738275)
annotation (Placement(visible = true, transformation(extent = {{-8.0,-8.0},{8.0,8.0}}, rotation = -90, origin = {134.8,-183.2})));
ModPowerSystems.PhasorSinglePhase.Lines.PiLine CIM_L7_8(Imax(displayUnit = "A") = 287.000, Sr(displayUnit = "W") = 1.000000, g = 0.000000, length=1.670000, r=0.251000, x=0.125000, b=0.0000738274)
annotation (Placement(visible = true, transformation(extent = {{-8.0,-8.0},{8.0,8.0}}, rotation = -90, origin = {194.8,-231.0})));
ModPowerSystems.PhasorSinglePhase.Lines.PiLine CIM_L8_9(Imax(displayUnit = "A") = 287.000, Sr(displayUnit = "W") = 1.000000, g = 0.000000, length=0.320000, r=0.251000, x=0.125000, b=0.0000738275)
annotation (Placement(visible = true, transformation(extent = {{-8.0,-8.0},{8.0,8.0}}, rotation = -90, origin = {124.1,-242.7})));
ModPowerSystems.PhasorSinglePhase.Transformers.Transformer CIM_TR1(Vnom1 = 110000.000, Vnom2 = 20000.000, Sr(displayUnit = "W") = 40000000.000, URr = 0.63000, Ukr = 12.04000)
annotation (Placement(visible = true, transformation(extent = {{-8.0,-8.0},{8.0,8.0}}, rotation = -90, origin = {86.0,-64.3})));
ModPowerSystems.PhasorSinglePhase.Transformers.Transformer CIM_TR2(Vnom1 = 110000.000, Vnom2 = 20000.000, Sr(displayUnit = "W") = 40000000.000, URr = 0.62000, Ukr = 12.04000)
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
end ../../samples/ModPowerSystems_MV_Grid_PQLoad/; 
