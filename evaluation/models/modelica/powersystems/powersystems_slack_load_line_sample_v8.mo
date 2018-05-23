model powersystems_slack_load_line_sample_v8 
inner PowerSystems.System System(dynType = PowerSystems.Types.Dynamics.SteadyState) 
annotation(Placement(visible = true, transformation(extent = {{0.0,-30.0},{30.0,0.0}}, rotation = 0)));
PowerSystems.AC3ph.Nodes.BusBar CIM_N0
annotation (Placement(visible = true, transformation(extent = {{-8.0,-8.0},{8.0,8.0}}, rotation = 0, origin = {87.0,-70.0})));
PowerSystems.AC3ph.Nodes.BusBar CIM_N1
annotation (Placement(visible = true, transformation(extent = {{-8.0,-8.0},{8.0,8.0}}, rotation = 0, origin = {88.0,-86.0})));
PowerSystems.AC3ph.Sources.InfBus CIM_SL(V_nom = 20000.000)
annotation (Placement(visible = true, transformation(extent = {{-5.0,-5.0},{5.0,5.0}}, rotation = -180, origin = {88.0,-55.2})));
PowerSystems.AC3ph.Loads.PQload CIM_PQ0(V_nom = 20000.000, pq0 = {330000.000,205000.000})
annotation (Placement(visible = true, transformation(extent = {{-8.0,-8.0},{8.0,8.0}}, rotation = 0, origin = {88.0,-93.8})));
PowerSystems.AC3ph.Lines.PIline CIM_L0(len=4890.000000, redeclare record Data = PowerSystems.AC3ph.Lines.Parameters.Line (puUnits=false, r=0.337000, x=0.358000, b_pg=0.0000511699,  g_pg=0.000000, g_pp=0, b_pp=0))
annotation (Placement(visible = true, transformation(extent = {{-8.0,-8.0},{8.0,8.0}}, rotation = -90, origin = {88.0,-78.0})));
equation
 connect(CIM_N0.term,CIM_L0.term_p)
annotation(Line(points={{87.00,-70.00},{87.00,-86.00},{88.00,-86.00}},color = {0,0,0}, smooth = Smooth.None));
 connect(CIM_N0.term,CIM_SL.term)
annotation(Line(points={{87.00,-70.00},{87.00,-55.20},{88.00,-55.20}},color = {0,0,0}, smooth = Smooth.None));
 connect(CIM_N1.term,CIM_L0.term_n)
annotation(Line(points={{88.00,-86.00},{88.00,-70.00}},color = {0,0,0}, smooth = Smooth.None));
 connect(CIM_N1.term,CIM_PQ0.term)
annotation(Line(points={{88.00,-86.00},{88.00,-85.80}},color = {0,0,0}, smooth = Smooth.None));
annotation(Diagram(coordinateSystem(extent = {{0.00,0.00},{400.00,-400.00}})), Icon(coordinateSystem(extent = {{160.0,-160.0},{180.0,260.0}})));  
end powersystems_slack_load_line_sample_v8; 