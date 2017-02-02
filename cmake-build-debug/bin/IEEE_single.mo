model IEEE_single 
annotation(Diagram(coordinateSystem(extent = {{0.00,0.00},{400.00,-400.00}})), Icon(coordinateSystem(extent = {{160.0,-160.0},{180.0,260.0}})));  
inner ModPowerSystems.System System(f_nom(displayUnit = "Hz") = 50.0, init = "steady", simMode = "steady") 
annotation(Placement(visible = true, transformation(extent = {{0.0,-30.0},{30.0,0.0}}, rotation = 0)));
ModPowerSystems.SinglePhase.Connections.BusBar CIM_BUS_11__13_8(Vnom = 13800)
annotation (Placement(visible = true, transformation(extent = {{-8.0,-8.0},{8.0,8.0}}, rotation = 0, origin = {61.0,-50.0})));
ModPowerSystems.SinglePhase.Connections.BusBar CIM_BUS_12__13_8(Vnom = 13800)
annotation (Placement(visible = true, transformation(extent = {{-8.0,-8.0},{8.0,8.0}}, rotation = 0, origin = {106.0,-116.0})));
ModPowerSystems.SinglePhase.Connections.BusBar CIM_BUS_13__13_8(Vnom = 13800)
annotation (Placement(visible = true, transformation(extent = {{-8.0,-8.0},{8.0,8.0}}, rotation = 0, origin = {147.0,-92.0})));
ModPowerSystems.SinglePhase.Connections.BusBar CIM_BUS_6___13_8(Vnom = 13800)
annotation (Placement(visible = true, transformation(extent = {{-8.0,-8.0},{8.0,8.0}}, rotation = 0, origin = {148.0,-50.0})));
ModPowerSystems.SinglePhase.Connections.BusBar CIM_BUS_4___69_0(Vnom = 69000)
annotation (Placement(visible = true, transformation(extent = {{-8.0,-8.0},{8.0,8.0}}, rotation = 0, origin = {233.0,-152.0})));
ModPowerSystems.SinglePhase.Connections.BusBar CIM_BUS_5___69_0(Vnom = 69000)
annotation (Placement(visible = true, transformation(extent = {{-8.0,-8.0},{8.0,8.0}}, rotation = 0, origin = {236.0,-108.0})));
ModPowerSystems.SinglePhase.Connections.BusBar CIM_BUS_1___69_0(Vnom = 69000)
annotation (Placement(visible = true, transformation(extent = {{-8.0,-8.0},{8.0,8.0}}, rotation = 0, origin = {244.0,-50.0})));
ModPowerSystems.SinglePhase.Connections.BusBar CIM_BUS_3___69_0(Vnom = 69000)
annotation (Placement(visible = true, transformation(extent = {{-8.0,-8.0},{8.0,8.0}}, rotation = 0, origin = {346.0,-176.0})));
ModPowerSystems.SinglePhase.Connections.BusBar CIM_BUS_2___69_0(Vnom = 69000)
annotation (Placement(visible = true, transformation(extent = {{-8.0,-8.0},{8.0,8.0}}, rotation = 0, origin = {347.0,-66.0})));
ModPowerSystems.SinglePhase.Connections.BusBar CIM_BUS_8___18_0(Vnom = 18000)
annotation (Placement(visible = true, transformation(extent = {{-8.0,-8.0},{8.0,8.0}}, rotation = 0, origin = {239.0,-262.0})));
ModPowerSystems.SinglePhase.Connections.BusBar CIM_BUS_7___13_8(Vnom = 13800)
annotation (Placement(visible = true, transformation(extent = {{-8.0,-8.0},{8.0,8.0}}, rotation = 0, origin = {237.0,-204.0})));
ModPowerSystems.SinglePhase.Connections.BusBar CIM_BUS_14__13_8(Vnom = 13800)
annotation (Placement(visible = true, transformation(extent = {{-8.0,-8.0},{8.0,8.0}}, rotation = 0, origin = {147.0,-140.0})));
ModPowerSystems.SinglePhase.Connections.BusBar CIM_BUS_9___13_8(Vnom = 13800)
annotation (Placement(visible = true, transformation(extent = {{-8.0,-8.0},{8.0,8.0}}, rotation = 0, origin = {151.0,-174.0})));
ModPowerSystems.SinglePhase.Connections.BusBar CIM_BUS_10__13_8(Vnom = 13800)
annotation (Placement(visible = true, transformation(extent = {{-8.0,-8.0},{8.0,8.0}}, rotation = 0, origin = {63.0,-170.0})));
ModPowerSystems.SinglePhase.Sources.Slack CIM_GNBUS_1___69_0(Vnom(displayUnit = "V") = 69.00, f(displayUnit = "Hz") = 50.0, phiV(displayUnit = "rad") = 0.00)
annotation (Placement(visible = true, transformation(extent = {{-5.0,-5.0},{5.0,5.0}}, rotation = -270, origin = {242.0,-40.2})));
ModPowerSystems.SinglePhase.Generation.SolarGenerator CIM_GNBUS_6___13_8(ControllerType = 0, CurtailLimit = 70.00, Pnom(displayUnit = "{PNOM_DISPLAYUNIT}") = 500000.00, 
StatusOn = true, Vnom = 110000.00, W_loss(start = 0.00), W_total(start = 0.00), enableInputPload = false, enableOutputPsolar = false, profileFileName = "NoName", profileName = "NoName") 
annotation (Placement(visible = true, transformation(extent = {{-5.0,-5.0},{5.0,5.0}}, rotation = -180, origin = {156.0,-40.2})));
ModPowerSystems.SinglePhase.Generation.SolarGenerator CIM_GNBUS_3___69_0(ControllerType = 0, CurtailLimit = 70.00, Pnom(displayUnit = "{PNOM_DISPLAYUNIT}") = 500000.00, 
StatusOn = true, Vnom = 110000.00, W_loss(start = 0.00), W_total(start = 0.00), enableInputPload = false, enableOutputPsolar = false, profileFileName = "NoName", profileName = "NoName") 
annotation (Placement(visible = true, transformation(extent = {{-5.0,-5.0},{5.0,5.0}}, rotation = 0, origin = {348.0,-185.8})));
ModPowerSystems.SinglePhase.Generation.SolarGenerator CIM_GNBUS_2___69_0(ControllerType = 0, CurtailLimit = 70.00, Pnom(displayUnit = "{PNOM_DISPLAYUNIT}") = 500000.00, 
StatusOn = true, Vnom = 110000.00, W_loss(start = 0.00), W_total(start = 0.00), enableInputPload = false, enableOutputPsolar = false, profileFileName = "NoName", profileName = "NoName") 
annotation (Placement(visible = true, transformation(extent = {{-5.0,-5.0},{5.0,5.0}}, rotation = -180, origin = {350.0,-56.2})));
ModPowerSystems.SinglePhase.Generation.SolarGenerator CIM_GNBUS_8___18_0(ControllerType = 0, CurtailLimit = 70.00, Pnom(displayUnit = "{PNOM_DISPLAYUNIT}") = 500000.00, 
StatusOn = true, Vnom = 110000.00, W_loss(start = 0.00), W_total(start = 0.00), enableInputPload = false, enableOutputPsolar = false, profileFileName = "NoName", profileName = "NoName") 
annotation (Placement(visible = true, transformation(extent = {{-5.0,-5.0},{5.0,5.0}}, rotation = -180, origin = {248.0,-252.2})));
ModPowerSystems.SinglePhase.Loads.PQLoad CIM_LDBUS_11__13_8(Pnom(displayUnit = "W") = 0.00, Qnom(displayUnit = "var") = 0.00, Vnom(displayUnit = "V") = 13.80)
annotation (Placement(visible = true, transformation(extent = {{-8.0,-8.0},{8.0,8.0}}, rotation = -180, origin = {60.0,-46.2})));
ModPowerSystems.SinglePhase.Loads.PQLoad CIM_LDBUS_12__13_8(Pnom(displayUnit = "W") = 0.00, Qnom(displayUnit = "var") = 0.00, Vnom(displayUnit = "V") = 13.80)
annotation (Placement(visible = true, transformation(extent = {{-8.0,-8.0},{8.0,8.0}}, rotation = 0, origin = {106.0,-119.8})));
ModPowerSystems.SinglePhase.Loads.PQLoad CIM_LDBUS_13__13_8(Pnom(displayUnit = "W") = 0.00, Qnom(displayUnit = "var") = 0.00, Vnom(displayUnit = "V") = 13.80)
annotation (Placement(visible = true, transformation(extent = {{-8.0,-8.0},{8.0,8.0}}, rotation = 0, origin = {134.0,-95.8})));
ModPowerSystems.SinglePhase.Loads.PQLoad CIM_LDBUS_6___13_8(Pnom(displayUnit = "W") = 0.00, Qnom(displayUnit = "var") = 0.00, Vnom(displayUnit = "V") = 13.80)
annotation (Placement(visible = true, transformation(extent = {{-8.0,-8.0},{8.0,8.0}}, rotation = -180, origin = {140.0,-46.2})));
ModPowerSystems.SinglePhase.Loads.PQLoad CIM_LDBUS_4___69_0(Pnom(displayUnit = "W") = 0.00, Qnom(displayUnit = "var") = 0.00, Vnom(displayUnit = "V") = 69.00)
annotation (Placement(visible = true, transformation(extent = {{-8.0,-8.0},{8.0,8.0}}, rotation = 0, origin = {226.0,-159.8})));
ModPowerSystems.SinglePhase.Loads.PQLoad CIM_LDBUS_5___69_0(Pnom(displayUnit = "W") = 0.00, Qnom(displayUnit = "var") = 0.00, Vnom(displayUnit = "V") = 69.00)
annotation (Placement(visible = true, transformation(extent = {{-8.0,-8.0},{8.0,8.0}}, rotation = 0, origin = {222.0,-111.8})));
ModPowerSystems.SinglePhase.Loads.PQLoad CIM_LDBUS_3___69_0(Pnom(displayUnit = "W") = 0.00, Qnom(displayUnit = "var") = 0.00, Vnom(displayUnit = "V") = 69.00)
annotation (Placement(visible = true, transformation(extent = {{-8.0,-8.0},{8.0,8.0}}, rotation = -180, origin = {338.0,-172.2})));
ModPowerSystems.SinglePhase.Loads.PQLoad CIM_LDBUS_2___69_0(Pnom(displayUnit = "W") = 0.00, Qnom(displayUnit = "var") = 0.00, Vnom(displayUnit = "V") = 69.00)
annotation (Placement(visible = true, transformation(extent = {{-8.0,-8.0},{8.0,8.0}}, rotation = 0, origin = {342.0,-69.8})));
ModPowerSystems.SinglePhase.Loads.PQLoad CIM_LDBUS_7___13_8(Pnom(displayUnit = "W") = 0.00, Qnom(displayUnit = "var") = 0.00, Vnom(displayUnit = "V") = 13.80)
annotation (Placement(visible = true, transformation(extent = {{-8.0,-8.0},{8.0,8.0}}, rotation = -180, origin = {246.0,-200.2})));
ModPowerSystems.SinglePhase.Loads.PQLoad CIM_LDBUS_14__13_8(Pnom(displayUnit = "W") = 0.00, Qnom(displayUnit = "var") = 0.00, Vnom(displayUnit = "V") = 13.80)
annotation (Placement(visible = true, transformation(extent = {{-8.0,-8.0},{8.0,8.0}}, rotation = 0, origin = {140.0,-143.8})));
ModPowerSystems.SinglePhase.Loads.PQLoad CIM_LDBUS_9___13_8(Pnom(displayUnit = "W") = 0.00, Qnom(displayUnit = "var") = 0.00, Vnom(displayUnit = "V") = 13.80)
annotation (Placement(visible = true, transformation(extent = {{-8.0,-8.0},{8.0,8.0}}, rotation = 0, origin = {140.0,-177.8})));
ModPowerSystems.SinglePhase.Loads.PQLoad CIM_LDBUS_10__13_8(Pnom(displayUnit = "W") = 0.00, Qnom(displayUnit = "var") = 0.00, Vnom(displayUnit = "V") = 13.80)
annotation (Placement(visible = true, transformation(extent = {{-8.0,-8.0},{8.0,8.0}}, rotation = 0, origin = {58.0,-173.8})));
ModPowerSystems.SinglePhase.Lines.PiLine CIM_BRANCH_19(Imax(displayUnit = "A") = 100.00, Sr(displayUnit = "W") = 1, g = 0, length=1.00, r=0.421, x=0.381, b=0.0000000000)
annotation (Placement(visible = true, transformation(extent = {{-8.0,-8.0},{8.0,8.0}}, rotation = -90, origin = {130.0,-108.0})));
ModPowerSystems.SinglePhase.Lines.PiLine CIM_BRANCH_20(Imax(displayUnit = "A") = 100.00, Sr(displayUnit = "W") = 1, g = 0, length=1.00, r=0.326, x=0.663, b=0.0000000000)
annotation (Placement(visible = true, transformation(extent = {{-8.0,-8.0},{8.0,8.0}}, rotation = -90, origin = {152.0,-116.0})));
ModPowerSystems.SinglePhase.Lines.PiLine CIM_BRANCH_12(Imax(displayUnit = "A") = 100.00, Sr(displayUnit = "W") = 1, g = 0, length=1.00, r=0.234, x=0.487, b=0.0000000000)
annotation (Placement(visible = true, transformation(extent = {{-8.0,-8.0},{8.0,8.0}}, rotation = -90, origin = {118.0,-81.5})));
ModPowerSystems.SinglePhase.Lines.PiLine CIM_BRANCH_13(Imax(displayUnit = "A") = 100.00, Sr(displayUnit = "W") = 1, g = 0, length=1.00, r=0.126, x=0.248, b=0.0000000000)
annotation (Placement(visible = true, transformation(extent = {{-8.0,-8.0},{8.0,8.0}}, rotation = -90, origin = {152.0,-71.0})));
ModPowerSystems.SinglePhase.Lines.PiLine CIM_BRANCH_11(Imax(displayUnit = "A") = 100.00, Sr(displayUnit = "W") = 1, g = 0, length=1.00, r=0.181, x=0.379, b=0.0000000000)
annotation (Placement(visible = true, transformation(extent = {{-8.0,-8.0},{8.0,8.0}}, rotation = -90, origin = {101.0,-57.0})));
ModPowerSystems.SinglePhase.Lines.PiLine CIM_BRANCH_7(Imax(displayUnit = "A") = 100.00, Sr(displayUnit = "W") = 1, g = 0, length=1.00, r=0.636, x=2.005, b=0.0002688509)
annotation (Placement(visible = true, transformation(extent = {{-8.0,-8.0},{8.0,8.0}}, rotation = -90, origin = {232.0,-130.0})));
ModPowerSystems.SinglePhase.Lines.PiLine CIM_BRANCH_1(Imax(displayUnit = "A") = 100.00, Sr(displayUnit = "W") = 1, g = 0, length=1.00, r=0.923, x=2.817, b=0.0011090105)
annotation (Placement(visible = true, transformation(extent = {{-8.0,-8.0},{8.0,8.0}}, rotation = -90, origin = {295.0,-57.0})));
ModPowerSystems.SinglePhase.Lines.PiLine CIM_BRANCH_2(Imax(displayUnit = "A") = 100.00, Sr(displayUnit = "W") = 1, g = 0, length=1.00, r=2.572, x=10.619, b=0.0010333961)
annotation (Placement(visible = true, transformation(extent = {{-8.0,-8.0},{8.0,8.0}}, rotation = -90, origin = {244.0,-79.0})));
ModPowerSystems.SinglePhase.Lines.PiLine CIM_BRANCH_6(Imax(displayUnit = "A") = 100.00, Sr(displayUnit = "W") = 1, g = 0, length=1.00, r=3.190, x=8.143, b=0.0007267380)
annotation (Placement(visible = true, transformation(extent = {{-8.0,-8.0},{8.0,8.0}}, rotation = -90, origin = {298.0,-150.0})));
ModPowerSystems.SinglePhase.Lines.PiLine CIM_BRANCH_3(Imax(displayUnit = "A") = 100.00, Sr(displayUnit = "W") = 1, g = 0, length=1.00, r=2.237, x=9.425, b=0.0009199746)
annotation (Placement(visible = true, transformation(extent = {{-8.0,-8.0},{8.0,8.0}}, rotation = -90, origin = {356.0,-121.0})));
ModPowerSystems.SinglePhase.Lines.PiLine CIM_BRANCH_4(Imax(displayUnit = "A") = 100.00, Sr(displayUnit = "W") = 1, g = 0, length=1.00, r=2.767, x=8.395, b=0.0007855490)
annotation (Placement(visible = true, transformation(extent = {{-8.0,-8.0},{8.0,8.0}}, rotation = -90, origin = {297.0,-116.5})));
ModPowerSystems.SinglePhase.Lines.PiLine CIM_BRANCH_5(Imax(displayUnit = "A") = 100.00, Sr(displayUnit = "W") = 1, g = 0, length=1.00, r=2.711, x=8.278, b=0.0007141355)
annotation (Placement(visible = true, transformation(extent = {{-8.0,-8.0},{8.0,8.0}}, rotation = -90, origin = {295.0,-81.5})));
ModPowerSystems.SinglePhase.Lines.PiLine CIM_BRANCH_15(Imax(displayUnit = "A") = 100.00, Sr(displayUnit = "W") = 1, g = 0, length=1.00, r=0.000, x=0.210, b=0.0000000000)
annotation (Placement(visible = true, transformation(extent = {{-8.0,-8.0},{8.0,8.0}}, rotation = -90, origin = {190.0,-192.5})));
ModPowerSystems.SinglePhase.Lines.PiLine CIM_BRANCH_16(Imax(displayUnit = "A") = 100.00, Sr(displayUnit = "W") = 1, g = 0, length=1.00, r=0.061, x=0.161, b=0.0000000000)
annotation (Placement(visible = true, transformation(extent = {{-8.0,-8.0},{8.0,8.0}}, rotation = -90, origin = {104.0,-163.0})));
ModPowerSystems.SinglePhase.Lines.PiLine CIM_BRANCH_17(Imax(displayUnit = "A") = 100.00, Sr(displayUnit = "W") = 1, g = 0, length=1.00, r=0.242, x=0.515, b=0.0000000000)
annotation (Placement(visible = true, transformation(extent = {{-8.0,-8.0},{8.0,8.0}}, rotation = -90, origin = {152.0,-157.0})));
ModPowerSystems.SinglePhase.Lines.PiLine CIM_BRANCH_18(Imax(displayUnit = "A") = 100.00, Sr(displayUnit = "W") = 1, g = 0, length=1.00, r=0.156, x=0.366, b=0.0000000000)
annotation (Placement(visible = true, transformation(extent = {{-8.0,-8.0},{8.0,8.0}}, rotation = -90, origin = {62.0,-110.0})));
ModPowerSystems.SinglePhase.Transformers.Transformer CIM_BRANCH_9(Vnom1 = 69000.00, Vnom2 = 13800.00, Sr(displayUnit = "W") = 100000000, URr = 52.22, Ukr = 0.00)
annotation (Placement(visible = true, transformation(extent = {{-8.0,-8.0},{8.0,8.0}}, rotation = -359, origin = {200.0,-135.9})));
ModPowerSystems.SinglePhase.Transformers.Transformer CIM_BRANCH_8(Vnom1 = 69000.00, Vnom2 = 13800.00, Sr(displayUnit = "W") = 100000000, URr = 20.00, Ukr = 0.00)
annotation (Placement(visible = true, transformation(extent = {{-8.0,-8.0},{8.0,8.0}}, rotation = -90, origin = {238.0,-171.6})));
ModPowerSystems.SinglePhase.Transformers.Transformer CIM_BRANCH_10(Vnom1 = 69000.00, Vnom2 = 13800.00, Sr(displayUnit = "W") = 100000000, URr = 21.89, Ukr = 0.00)
annotation (Placement(visible = true, transformation(extent = {{-8.0,-8.0},{8.0,8.0}}, rotation = -359, origin = {200.4,-76.0})));
ModPowerSystems.SinglePhase.Transformers.Transformer CIM_BRANCH_14(Vnom1 = 13800.00, Vnom2 = 18000.00, Sr(displayUnit = "W") = 100000000, URr = 17.61, Ukr = 0.00)
annotation (Placement(visible = true, transformation(extent = {{-8.0,-8.0},{8.0,8.0}}, rotation = -90, origin = {238.0,-221.6})));
equation
 connect(CIM_BUS_11__13_8.T,CIM_BRANCH_18.T2)
annotation(Line(points={{61.00,-50.00},{61.00,-102.00},{62.00,-102.00}},color = {0,0,0}, smooth = Smooth.None));
 connect(CIM_BUS_11__13_8.T,CIM_BRANCH_11.T2)
annotation(Line(points={{61.00,-50.00},{101.00,-50.00},{101.00,-49.00}},color = {0,0,0}, smooth = Smooth.None));
 connect(CIM_BUS_11__13_8.T,CIM_LDBUS_11__13_8.T)
annotation(Line(points={{61.00,-50.00},{61.00,-54.20},{60.00,-54.20}},color = {0,0,0}, smooth = Smooth.None));
 connect(CIM_BUS_12__13_8.T,CIM_BRANCH_12.T2)
annotation(Line(points={{106.00,-116.00},{106.00,-94.75},{118.00,-94.75},{118.00,-73.50}},color = {0,0,0}, smooth = Smooth.None));
 connect(CIM_BUS_12__13_8.T,CIM_BRANCH_19.T1)
annotation(Line(points={{106.00,-116.00},{130.00,-116.00}},color = {0,0,0}, smooth = Smooth.None));
 connect(CIM_BUS_12__13_8.T,CIM_LDBUS_12__13_8.T)
annotation(Line(points={{106.00,-116.00},{106.00,-111.80}},color = {0,0,0}, smooth = Smooth.None));
 connect(CIM_BUS_13__13_8.T,CIM_BRANCH_13.T2)
annotation(Line(points={{147.00,-92.00},{147.00,-63.00},{152.00,-63.00}},color = {0,0,0}, smooth = Smooth.None));
 connect(CIM_BUS_13__13_8.T,CIM_BRANCH_19.T2)
annotation(Line(points={{147.00,-92.00},{130.00,-92.00},{130.00,-100.00}},color = {0,0,0}, smooth = Smooth.None));
 connect(CIM_BUS_13__13_8.T,CIM_BRANCH_20.T1)
annotation(Line(points={{147.00,-92.00},{147.00,-124.00},{152.00,-124.00}},color = {0,0,0}, smooth = Smooth.None));
 connect(CIM_BUS_13__13_8.T,CIM_LDBUS_13__13_8.T)
annotation(Line(points={{147.00,-92.00},{134.00,-92.00},{134.00,-87.80}},color = {0,0,0}, smooth = Smooth.None));
 connect(CIM_BUS_6___13_8.T,CIM_BRANCH_12.T1)
annotation(Line(points={{148.00,-50.00},{148.00,-69.75},{118.00,-69.75},{118.00,-89.50}},color = {0,0,0}, smooth = Smooth.None));
 connect(CIM_BUS_6___13_8.T,CIM_BRANCH_13.T1)
annotation(Line(points={{148.00,-50.00},{148.00,-79.00},{152.00,-79.00}},color = {0,0,0}, smooth = Smooth.None));
 connect(CIM_BUS_6___13_8.T,CIM_BRANCH_11.T1)
annotation(Line(points={{148.00,-50.00},{148.00,-57.50},{101.00,-57.50},{101.00,-65.00}},color = {0,0,0}, smooth = Smooth.None));
 connect(CIM_BUS_6___13_8.T,CIM_BRANCH_10.T2)
annotation(Line(points={{148.00,-50.00},{148.00,-63.00},{208.40,-63.00},{208.40,-76.00}},color = {0,0,0}, smooth = Smooth.None));
 connect(CIM_BUS_6___13_8.T,CIM_GNBUS_6___13_8.T)
annotation(Line(points={{148.00,-50.00},{148.00,-45.10},{156.00,-45.10},{156.00,-40.20}},color = {0,0,0}, smooth = Smooth.None));
 connect(CIM_BUS_6___13_8.T,CIM_LDBUS_6___13_8.T)
annotation(Line(points={{148.00,-50.00},{148.00,-54.20},{140.00,-54.20}},color = {0,0,0}, smooth = Smooth.None));
 connect(CIM_BUS_4___69_0.T,CIM_BRANCH_7.T1)
annotation(Line(points={{233.00,-152.00},{233.00,-138.00},{232.00,-138.00}},color = {0,0,0}, smooth = Smooth.None));
 connect(CIM_BUS_4___69_0.T,CIM_BRANCH_4.T2)
annotation(Line(points={{233.00,-152.00},{233.00,-130.25},{297.00,-130.25},{297.00,-108.50}},color = {0,0,0}, smooth = Smooth.None));
 connect(CIM_BUS_4___69_0.T,CIM_BRANCH_6.T2)
annotation(Line(points={{233.00,-152.00},{233.00,-147.00},{298.00,-147.00},{298.00,-142.00}},color = {0,0,0}, smooth = Smooth.None));
 connect(CIM_BUS_4___69_0.T,CIM_BRANCH_9.T1)
annotation(Line(points={{233.00,-152.00},{233.00,-143.95},{192.00,-143.95},{192.00,-135.90}},color = {0,0,0}, smooth = Smooth.None));
 connect(CIM_BUS_4___69_0.T,CIM_BRANCH_8.T1)
annotation(Line(points={{233.00,-152.00},{233.00,-179.60},{238.00,-179.60}},color = {0,0,0}, smooth = Smooth.None));
 connect(CIM_BUS_4___69_0.T,CIM_LDBUS_4___69_0.T)
annotation(Line(points={{233.00,-152.00},{233.00,-151.80},{226.00,-151.80}},color = {0,0,0}, smooth = Smooth.None));
 connect(CIM_BUS_5___69_0.T,CIM_BRANCH_7.T2)
annotation(Line(points={{236.00,-108.00},{236.00,-122.00},{232.00,-122.00}},color = {0,0,0}, smooth = Smooth.None));
 connect(CIM_BUS_5___69_0.T,CIM_BRANCH_2.T2)
annotation(Line(points={{236.00,-108.00},{236.00,-71.00},{244.00,-71.00}},color = {0,0,0}, smooth = Smooth.None));
 connect(CIM_BUS_5___69_0.T,CIM_BRANCH_5.T2)
annotation(Line(points={{236.00,-108.00},{236.00,-90.75},{295.00,-90.75},{295.00,-73.50}},color = {0,0,0}, smooth = Smooth.None));
 connect(CIM_BUS_5___69_0.T,CIM_BRANCH_10.T1)
annotation(Line(points={{236.00,-108.00},{236.00,-92.00},{192.40,-92.00},{192.40,-76.00}},color = {0,0,0}, smooth = Smooth.None));
 connect(CIM_BUS_5___69_0.T,CIM_LDBUS_5___69_0.T)
annotation(Line(points={{236.00,-108.00},{222.00,-108.00},{222.00,-103.80}},color = {0,0,0}, smooth = Smooth.None));
 connect(CIM_BUS_1___69_0.T,CIM_BRANCH_1.T1)
annotation(Line(points={{244.00,-50.00},{244.00,-57.50},{295.00,-57.50},{295.00,-65.00}},color = {0,0,0}, smooth = Smooth.None));
 connect(CIM_BUS_1___69_0.T,CIM_BRANCH_2.T1)
annotation(Line(points={{244.00,-50.00},{244.00,-87.00}},color = {0,0,0}, smooth = Smooth.None));
 connect(CIM_BUS_1___69_0.T,CIM_GNBUS_1___69_0.T)
annotation(Line(points={{244.00,-50.00},{244.00,-40.20},{242.00,-40.20}},color = {0,0,0}, smooth = Smooth.None));
 connect(CIM_BUS_3___69_0.T,CIM_BRANCH_3.T2)
annotation(Line(points={{346.00,-176.00},{346.00,-144.50},{356.00,-144.50},{356.00,-113.00}},color = {0,0,0}, smooth = Smooth.None));
 connect(CIM_BUS_3___69_0.T,CIM_BRANCH_6.T1)
annotation(Line(points={{346.00,-176.00},{346.00,-167.00},{298.00,-167.00},{298.00,-158.00}},color = {0,0,0}, smooth = Smooth.None));
 connect(CIM_BUS_3___69_0.T,CIM_GNBUS_3___69_0.T)
annotation(Line(points={{346.00,-176.00},{346.00,-185.80},{348.00,-185.80}},color = {0,0,0}, smooth = Smooth.None));
 connect(CIM_BUS_3___69_0.T,CIM_LDBUS_3___69_0.T)
annotation(Line(points={{346.00,-176.00},{346.00,-180.20},{338.00,-180.20}},color = {0,0,0}, smooth = Smooth.None));
 connect(CIM_BUS_2___69_0.T,CIM_BRANCH_1.T2)
annotation(Line(points={{347.00,-66.00},{347.00,-57.50},{295.00,-57.50},{295.00,-49.00}},color = {0,0,0}, smooth = Smooth.None));
 connect(CIM_BUS_2___69_0.T,CIM_BRANCH_3.T1)
annotation(Line(points={{347.00,-66.00},{347.00,-97.50},{356.00,-97.50},{356.00,-129.00}},color = {0,0,0}, smooth = Smooth.None));
 connect(CIM_BUS_2___69_0.T,CIM_BRANCH_4.T1)
annotation(Line(points={{347.00,-66.00},{347.00,-95.25},{297.00,-95.25},{297.00,-124.50}},color = {0,0,0}, smooth = Smooth.None));
 connect(CIM_BUS_2___69_0.T,CIM_BRANCH_5.T1)
annotation(Line(points={{347.00,-66.00},{347.00,-77.75},{295.00,-77.75},{295.00,-89.50}},color = {0,0,0}, smooth = Smooth.None));
 connect(CIM_BUS_2___69_0.T,CIM_GNBUS_2___69_0.T)
annotation(Line(points={{347.00,-66.00},{347.00,-56.20},{350.00,-56.20}},color = {0,0,0}, smooth = Smooth.None));
 connect(CIM_BUS_2___69_0.T,CIM_LDBUS_2___69_0.T)
annotation(Line(points={{347.00,-66.00},{347.00,-61.80},{342.00,-61.80}},color = {0,0,0}, smooth = Smooth.None));
 connect(CIM_BUS_8___18_0.T,CIM_BRANCH_14.T2)
annotation(Line(points={{239.00,-262.00},{239.00,-213.60},{238.00,-213.60}},color = {0,0,0}, smooth = Smooth.None));
 connect(CIM_BUS_8___18_0.T,CIM_GNBUS_8___18_0.T)
annotation(Line(points={{239.00,-262.00},{239.00,-257.10},{248.00,-257.10},{248.00,-252.20}},color = {0,0,0}, smooth = Smooth.None));
 connect(CIM_BUS_7___13_8.T,CIM_BRANCH_15.T1)
annotation(Line(points={{237.00,-204.00},{190.00,-204.00},{190.00,-200.50}},color = {0,0,0}, smooth = Smooth.None));
 connect(CIM_BUS_7___13_8.T,CIM_BRANCH_8.T2)
annotation(Line(points={{237.00,-204.00},{237.00,-163.60},{238.00,-163.60}},color = {0,0,0}, smooth = Smooth.None));
 connect(CIM_BUS_7___13_8.T,CIM_BRANCH_14.T1)
annotation(Line(points={{237.00,-204.00},{237.00,-229.60},{238.00,-229.60}},color = {0,0,0}, smooth = Smooth.None));
 connect(CIM_BUS_7___13_8.T,CIM_LDBUS_7___13_8.T)
annotation(Line(points={{237.00,-204.00},{246.00,-204.00},{246.00,-208.20}},color = {0,0,0}, smooth = Smooth.None));
 connect(CIM_BUS_14__13_8.T,CIM_BRANCH_17.T2)
annotation(Line(points={{147.00,-140.00},{147.00,-149.00},{152.00,-149.00}},color = {0,0,0}, smooth = Smooth.None));
 connect(CIM_BUS_14__13_8.T,CIM_BRANCH_20.T2)
annotation(Line(points={{147.00,-140.00},{147.00,-108.00},{152.00,-108.00}},color = {0,0,0}, smooth = Smooth.None));
 connect(CIM_BUS_14__13_8.T,CIM_LDBUS_14__13_8.T)
annotation(Line(points={{147.00,-140.00},{147.00,-135.80},{140.00,-135.80}},color = {0,0,0}, smooth = Smooth.None));
 connect(CIM_BUS_9___13_8.T,CIM_BRANCH_15.T2)
annotation(Line(points={{151.00,-174.00},{151.00,-179.25},{190.00,-179.25},{190.00,-184.50}},color = {0,0,0}, smooth = Smooth.None));
 connect(CIM_BUS_9___13_8.T,CIM_BRANCH_16.T1)
annotation(Line(points={{151.00,-174.00},{104.00,-174.00},{104.00,-171.00}},color = {0,0,0}, smooth = Smooth.None));
 connect(CIM_BUS_9___13_8.T,CIM_BRANCH_17.T1)
annotation(Line(points={{151.00,-174.00},{151.00,-165.00},{152.00,-165.00}},color = {0,0,0}, smooth = Smooth.None));
 connect(CIM_BUS_9___13_8.T,CIM_BRANCH_9.T2)
annotation(Line(points={{151.00,-174.00},{151.00,-154.95},{208.00,-154.95},{208.00,-135.90}},color = {0,0,0}, smooth = Smooth.None));
 connect(CIM_BUS_9___13_8.T,CIM_LDBUS_9___13_8.T)
annotation(Line(points={{151.00,-174.00},{140.00,-174.00},{140.00,-169.80}},color = {0,0,0}, smooth = Smooth.None));
 connect(CIM_BUS_10__13_8.T,CIM_BRANCH_16.T2)
annotation(Line(points={{63.00,-170.00},{63.00,-162.50},{104.00,-162.50},{104.00,-155.00}},color = {0,0,0}, smooth = Smooth.None));
 connect(CIM_BUS_10__13_8.T,CIM_BRANCH_18.T1)
annotation(Line(points={{63.00,-170.00},{63.00,-118.00},{62.00,-118.00}},color = {0,0,0}, smooth = Smooth.None));
 connect(CIM_BUS_10__13_8.T,CIM_LDBUS_10__13_8.T)
annotation(Line(points={{63.00,-170.00},{63.00,-165.80},{58.00,-165.80}},color = {0,0,0}, smooth = Smooth.None));
end IEEE_single; 
