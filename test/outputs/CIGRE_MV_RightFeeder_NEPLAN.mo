model CIGRE_MV_RightFeeder_NEPLAN 
inner ModPowerSystems.Base.System System(freq_nom(displayUnit = "Hz") = 50.0) 
annotation(Placement(visible = true, transformation(extent = {{0.0,-30.0},{30.0,0.0}}, rotation = 0)));
ModPowerSystems.PhasorSinglePhase.Connections.BusBar CIM_N13(Vnom = 20000.000)
annotation (Placement(visible = true, transformation(extent = {{-8.0,-8.0},{8.0,8.0}}, rotation = 0, origin = {223.8,-138.0})));
ModPowerSystems.PhasorSinglePhase.Connections.BusBar CIM_N12(Vnom = 20000.000)
annotation (Placement(visible = true, transformation(extent = {{-8.0,-8.0},{8.0,8.0}}, rotation = 0, origin = {229.8,-98.0})));
ModPowerSystems.PhasorSinglePhase.Connections.BusBar CIM_N0(Vnom = 110000.000)
annotation (Placement(visible = true, transformation(extent = {{-8.0,-8.0},{8.0,8.0}}, rotation = 0, origin = {153.8,-40.0})));
ModPowerSystems.PhasorSinglePhase.Slack.Slack CIM_HV_Netz(Vnom(displayUnit = "V") = 110000.000, phiV(displayUnit = "rad") = 0.000)
annotation (Placement(visible = true, transformation(extent = {{-5.0,-5.0},{5.0,5.0}}, rotation = -180, origin = {130.9,-19.2})));
ModPowerSystems.PhasorSinglePhase.Loads.PQLoad CIM_Load13_I(Pnom(displayUnit = "W") = 32000.000, Qnom(displayUnit = "var") = 20000.000, Vnom(displayUnit = "V") = 20000.000)
annotation (Placement(visible = true, transformation(extent = {{-8.0,-8.0},{8.0,8.0}}, rotation = 0, origin = {234.8,-145.8})));
ModPowerSystems.PhasorSinglePhase.Loads.PQLoad CIM_Load12_H(Pnom(displayUnit = "W") = 15000000.000, Qnom(displayUnit = "var") = 3000000.000, Vnom(displayUnit = "V") = 20000.000)
annotation (Placement(visible = true, transformation(extent = {{-8.0,-8.0},{8.0,8.0}}, rotation = 0, origin = {237.1,-107.8})));
ModPowerSystems.PhasorSinglePhase.Loads.PQLoad CIM_Load12_I(Pnom(displayUnit = "W") = 5000000.000, Qnom(displayUnit = "var") = 1700000.000, Vnom(displayUnit = "V") = 20000.000)
annotation (Placement(visible = true, transformation(extent = {{-8.0,-8.0},{8.0,8.0}}, rotation = 0, origin = {249.2,-107.8})));
ModPowerSystems.PhasorSinglePhase.Connections.PiLine CIM_L12_13(Imax(displayUnit = "A") = 320.000, Sr(displayUnit = "W") = 1.000000, g = 0.000000, length=4.890000, r=0.337000, x=0.358000, b=0.0000511699)
annotation (Placement(visible = true, transformation(extent = {{-8.0,-8.0},{8.0,8.0}}, rotation = -90, origin = {222.8,-118.0})));
ModPowerSystems.PhasorSinglePhase.Transformers.Transformer CIM_TR2(Vnom1 = 110000.000, Vnom2 = 20000.000, Sr(displayUnit = "W") = 40000000.000, URr = 0.63000, Ukr = 12.04000)
annotation (Placement(visible = true, transformation(extent = {{-8.0,-8.0},{8.0,8.0}}, rotation = -90, origin = {222.8,-68.0})));
equation
 connect(CIM_N13.Pin1,CIM_L12_13.Pin2)
annotation(Line(points={{223.80,-138.00},{223.80,-110.00},{222.80,-110.00}},color = {0,0,0}, smooth = Smooth.None));
 connect(CIM_N13.Pin1,CIM_Load13_I.Pin1)
annotation(Line(points={{223.80,-138.00},{234.80,-138.00},{234.80,-137.80}},color = {0,0,0}, smooth = Smooth.None));
 connect(CIM_N12.Pin1,CIM_L12_13.Pin1)
annotation(Line(points={{229.80,-98.00},{229.80,-126.00},{222.80,-126.00}},color = {0,0,0}, smooth = Smooth.None));
 connect(CIM_N12.Pin1,CIM_TR2.Pin2)
annotation(Line(points={{229.80,-98.00},{229.80,-60.00},{222.80,-60.00}},color = {0,0,0}, smooth = Smooth.None));
 connect(CIM_N12.Pin1,CIM_Load12_H.Pin1)
annotation(Line(points={{229.80,-98.00},{229.80,-99.80},{237.10,-99.80}},color = {0,0,0}, smooth = Smooth.None));
 connect(CIM_N12.Pin1,CIM_Load12_I.Pin1)
annotation(Line(points={{229.80,-98.00},{249.20,-98.00},{249.20,-99.80}},color = {0,0,0}, smooth = Smooth.None));
 connect(CIM_N0.Pin1,CIM_TR2.Pin1)
annotation(Line(points={{153.80,-40.00},{153.80,-58.00},{222.80,-58.00},{222.80,-76.00}},color = {0,0,0}, smooth = Smooth.None));
 connect(CIM_N0.Pin1,CIM_HV_Netz.Pin1)
annotation(Line(points={{153.80,-40.00},{153.80,-29.60},{130.90,-29.60},{130.90,-19.20}},color = {0,0,0}, smooth = Smooth.None));
annotation(Diagram(coordinateSystem(extent = {{0.00,0.00},{400.00,-400.00}})), Icon(coordinateSystem(extent = {{160.0,-160.0},{180.0,260.0}})));  
end CIGRE_MV_RightFeeder_NEPLAN; 