model Slack_Load_Line_Sample 
annotation(Diagram(coordinateSystem(extent = {{0.00,0.00},{400.00,-400.00}})), Icon(coordinateSystem(extent = {{160.0,-160.0},{180.0,260.0}})));  
inner ModPowerSystems.System System(f_nom(displayUnit = "Hz") = 50.0) 
annotation(Placement(visible = true, transformation(extent = {{0.0,-30.0},{30.0,0.0}}, rotation = 0)));
ModPowerSystems.PhasorSinglePhase.Connections.BusBar CIM_N0(Vnom = 20000.000)
annotation (Placement(visible = true, transformation(extent = {{-8.0,-8.0},{8.0,8.0}}, rotation = 0, origin = {87.0,-70.0})));
ModPowerSystems.PhasorSinglePhase.Connections.BusBar CIM_N1(Vnom = 20000.000)
annotation (Placement(visible = true, transformation(extent = {{-8.0,-8.0},{8.0,8.0}}, rotation = 0, origin = {88.0,-86.0})));
ModPowerSystems.PhasorSinglePhase.Sources.Slack CIM_SL(Vnom(displayUnit = "V") = 20000.000, f(displayUnit = "Hz") = 50.0, phiV(displayUnit = "rad") = 0.000)
annotation (Placement(visible = true, transformation(extent = {{-5.0,-5.0},{5.0,5.0}}, rotation = -180, origin = {88.0,-55.2})));
ModPowerSystems.PhasorSinglePhase.Loads.PQLoad CIM_PQ0(Pnom(displayUnit = "W") = 0.000, Qnom(displayUnit = "var") = 0.000, Vnom(displayUnit = "V") = 20000.000)
annotation (Placement(visible = true, transformation(extent = {{-8.0,-8.0},{8.0,8.0}}, rotation = 0, origin = {88.0,-93.8})));
ModPowerSystems.PhasorSinglePhase.Lines.PiLine CIM_L0(Imax(displayUnit = "A") = 320.000, Sr(displayUnit = "W") = 1.000000, g = 0.000000, length=4.890000, r=0.337000, x=0.358000, b=0.0000511699)
annotation (Placement(visible = true, transformation(extent = {{-8.0,-8.0},{8.0,8.0}}, rotation = -90, origin = {88.0,-78.0})));
equation
 connect(CIM_N0.T,CIM_L0.T1)
annotation(Line(points={{87.00,-70.00},{87.00,-86.00},{88.00,-86.00}},color = {0,0,0}, smooth = Smooth.None));
 connect(CIM_N0.T,CIM_SL.T)
annotation(Line(points={{87.00,-70.00},{87.00,-55.20},{88.00,-55.20}},color = {0,0,0}, smooth = Smooth.None));
 connect(CIM_N1.T,CIM_L0.T2)
annotation(Line(points={{88.00,-86.00},{88.00,-70.00}},color = {0,0,0}, smooth = Smooth.None));
 connect(CIM_N1.T,CIM_PQ0.T)
annotation(Line(points={{88.00,-86.00},{88.00,-85.80}},color = {0,0,0}, smooth = Smooth.None));
end Slack_Load_Line_Sample; 
