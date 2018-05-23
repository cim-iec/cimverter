model powersystems_slack_trafo_load_sample_v3_with_ground
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
PowerSystems.AC3ph.Transformers.TrafoStray CIM_TR0(redeclare record Data =
        PowerSystems.AC3ph.Transformers.Parameters.TrafoStray (                                                                   puUnits=false,V_nom={110000.000,20000.000},r={1.905750,0},x={36.371106,0},S_nom=40000000.000))
annotation (Placement(visible = true, transformation(extent = {{-8.0,-8.0},{8.0,8.0}}, rotation = -90, origin = {88.0,-94.0})));
  PowerSystems.AC3ph.Nodes.GroundOne grd1
    annotation (Placement(transformation(extent={{106,-60},{118,-48}})));
equation
 connect(CIM_N0.term,CIM_TR0.term_p)
annotation(Line(points={{88,-70},{88,-86}},             color = {0,0,0}, smooth = Smooth.None));
 connect(CIM_N0.term,CIM_SL.term)
annotation(Line(points={{88,-70},{88,-62},{88,-55.2},{83,-55.2}},
                                                       color = {0,0,0}, smooth = Smooth.None));
 connect(CIM_N1.term,CIM_TR0.term_n)
annotation(Line(points={{88,-118},{88,-102}},           color = {0,0,0}, smooth = Smooth.None));
 connect(CIM_N1.term,CIM_PQ0.term)
annotation(Line(points={{88,-118},{88,-120},{88,-123.8},{80,-123.8}},
                                                         color = {0,0,0}, smooth = Smooth.None));
  connect(CIM_SL.neutral, grd1.term) annotation (Line(points={{93,-55.2},{102,
          -55.2},{102,-54},{106,-54}}, color={0,0,255}));
annotation(Diagram(coordinateSystem(extent = {{0.00,0.00},{400.00,-400.00}})), Icon(coordinateSystem(extent = {{160.0,-160.0},{180.0,260.0}})),
    uses(PowerSystems(version="0.7 dev")));
end powersystems_slack_trafo_load_sample_v3_with_ground;
