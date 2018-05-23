model modpowersystems_slack_trafo_load_sample_v1 
inner ModPowerSystems.Base.System System(freq_nom(displayUnit = "Hz") = 50.0) 
annotation(Placement(visible = true, transformation(extent = {{0.0,-30.0},{30.0,0.0}}, rotation = 0)));
ModPowerSystems.PhasorSinglePhase.Connections.BusBar CIM_N0(Vnom = 110000.000)
annotation (Placement(visible = true, transformation(extent = {{-8.0,-8.0},{8.0,8.0}}, rotation = 0, origin = {88.0,-70.0})));
ModPowerSystems.PhasorSinglePhase.Connections.BusBar CIM_N1(Vnom = 20000.000)
annotation (Placement(visible = true, transformation(extent = {{-8.0,-8.0},{8.0,8.0}}, rotation = 0, origin = {88.0,-118.0})));
ModPowerSystems.PhasorSinglePhase.Slack.Slack CIM_SL(Vnom(displayUnit = "V") = 110000.000, phiV(displayUnit = "rad") = 0.000)
annotation (Placement(visible = true, transformation(extent = {{-5.0,-5.0},{5.0,5.0}}, rotation = -180, origin = {88.0,-55.2})));
ModPowerSystems.PhasorSinglePhase.Loads.PQLoad CIM_PQ0(Pnom(displayUnit = "W") = 330000.000, Qnom(displayUnit = "var") = 205000.000, Vnom(displayUnit = "V") = 20000.000)
annotation (Placement(visible = true, transformation(extent = {{-8.0,-8.0},{8.0,8.0}}, rotation = 0, origin = {88.0,-123.8})));
ModPowerSystems.PhasorSinglePhase.Transformers.Transformer CIM_TR0(Vnom1 = 110000.000, Vnom2 = 20000.000, Sr(displayUnit = "W") = 40000000.000, URr = 0.63000, Ukr = 12.04000)
annotation (Placement(visible = true, transformation(extent = {{-8.0,-8.0},{8.0,8.0}}, rotation = -90, origin = {88.0,-94.0})));
equation
 connect(CIM_N0.Pin1,CIM_TR0.Pin1)
annotation(Line(points={{88.00,-70.00},{88.00,-102.00}},color = {0,0,0}, smooth = Smooth.None));
 connect(CIM_N0.Pin1,CIM_SL.Pin1)
annotation(Line(points={{88.00,-70.00},{88.00,-55.20}},color = {0,0,0}, smooth = Smooth.None));
 connect(CIM_N1.Pin1,CIM_TR0.Pin2)
annotation(Line(points={{88.00,-118.00},{88.00,-86.00}},color = {0,0,0}, smooth = Smooth.None));
 connect(CIM_N1.Pin1,CIM_PQ0.Pin1)
annotation(Line(points={{88.00,-118.00},{88.00,-115.80}},color = {0,0,0}, smooth = Smooth.None));
annotation(Diagram(coordinateSystem(extent = {{0.00,0.00},{400.00,-400.00}})), Icon(coordinateSystem(extent = {{160.0,-160.0},{180.0,260.0}})));  
end modpowersystems_slack_trafo_load_sample_v1; 