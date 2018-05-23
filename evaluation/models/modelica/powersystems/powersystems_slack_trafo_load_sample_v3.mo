model powersystems_slack_trafo_load_sample_v3 
inner PowerSystems.System System(dynType = PowerSystems.Types.Dynamics.SteadyState) 
annotation(Placement(visible = true, transformation(extent = {{0.0,-30.0},{30.0,0.0}}, rotation = 0)));
PowerSystems.AC3ph.Nodes.BusBar CIM_N0
annotation (Placement(visible = true, transformation(extent = {{-8.0,-8.0},{8.0,8.0}}, rotation = 0, origin = {88.0,-70.0})));
PowerSystems.AC3ph.Nodes.BusBar CIM_N1
annotation (Placement(visible = true, transformation(extent = {{-8.0,-8.0},{8.0,8.0}}, rotation = 0, origin = {88.0,-118.0})));
PowerSystems.AC3ph.Sources.InfBus CIM_SL(V_nom = 110000.000)
annotation (Placement(visible = true, transformation(extent = {{-5.0,-5.0},{5.0,5.0}}, rotation = -180, origin = {88.0,-55.2})));
PowerSystems.AC3ph.Loads.PQload CIM_PQ0(V_nom = 20000.000, pq0 = {330000.000,205000.000})
annotation (Placement(visible = true, transformation(extent = {{-8.0,-8.0},{8.0,8.0}}, rotation = 0, origin = {88.0,-123.8})));
PowerSystems.AC3ph.Transformers.TrafoStray CIM_TR0(redeclare record Data = PowerSystems.AC3ph.Transformers.Parameters.TrafoStray (puUnits=false,V_nom={110000.000,20000.000},r={1.905750,0},x={36.371106,0},S_nom=40000000.000))
annotation (Placement(visible = true, transformation(extent = {{-8.0,-8.0},{8.0,8.0}}, rotation = -90, origin = {88.0,-94.0})));
equation
 connect(CIM_N0.term,CIM_TR0.term_p)
annotation(Line(points={{88.00,-70.00},{88.00,-102.00}},color = {0,0,0}, smooth = Smooth.None));
 connect(CIM_N0.term,CIM_SL.term)
annotation(Line(points={{88.00,-70.00},{88.00,-55.20}},color = {0,0,0}, smooth = Smooth.None));
 connect(CIM_N1.term,CIM_TR0.term_n)
annotation(Line(points={{88.00,-118.00},{88.00,-86.00}},color = {0,0,0}, smooth = Smooth.None));
 connect(CIM_N1.term,CIM_PQ0.term)
annotation(Line(points={{88.00,-118.00},{88.00,-115.80}},color = {0,0,0}, smooth = Smooth.None));
annotation(Diagram(coordinateSystem(extent = {{0.00,0.00},{400.00,-400.00}})), Icon(coordinateSystem(extent = {{160.0,-160.0},{180.0,260.0}})));  
end powersystems_slack_trafo_load_sample_v3; 