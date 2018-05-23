within ;
model Slack_Trafo_Load_Sample

  PowerSystems.AC3ph.Sources.InfBus infBus(V_nom=110000)
    annotation (Placement(transformation(extent={{-50,-10},{-30,10}})));
  PowerSystems.AC3ph.Loads.PQload pqLoad(             pq0={330000,205000}, V_nom=
        20000)
    annotation (Placement(transformation(extent={{28,-10},{48,10}})));
  inner PowerSystems.System system(dynType=PowerSystems.Types.Dynamics.SteadyState)
    annotation (Placement(transformation(extent={{-78,50},{-58,70}})));
  PowerSystems.AC3ph.Nodes.BusBar bus1
    annotation (Placement(transformation(extent={{-30,-10},{-10,10}})));
  PowerSystems.AC3ph.Nodes.BusBar bus2
    annotation (Placement(transformation(extent={{10,-10},{30,10}})));
  PowerSystems.AC3ph.Transformers.TrafoStray trafo(redeclare record Data =
        PowerSystems.AC3ph.Transformers.Parameters.TrafoStray (
        r={1.905750,0},
        x={36.371106,0},
        puUnits=false,
        V_nom={110000,20000}))
    annotation (Placement(transformation(extent={{-8,-10},{12,10}})));
equation
  connect(infBus.term, bus1.term)
    annotation (Line(points={{-30,0},{-25,0},{-20,0}}, color={0,120,120}));
  connect(pqLoad.term, bus2.term)
    annotation (Line(points={{28,0},{24,0},{20,0}}, color={0,120,120}));
  connect(trafo.term_n, bus2.term)
    annotation (Line(points={{12,0},{16,0},{20,0}}, color={0,120,120}));
  connect(trafo.term_p, bus1.term)
    annotation (Line(points={{-8,0},{-20,0}}, color={0,120,120}));
  annotation (
    uses(PowerSystems(version = "0.7 dev")));
end Slack_Trafo_Load_Sample;
