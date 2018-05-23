model Slack_Load_Line_Ground_Sample
  PowerSystems.AC3ph.Sources.InfBus infBus(V_nom = 20000) annotation(
    Placement(transformation(extent = {{-50, -10}, {-30, 10}})));
  PowerSystems.AC3ph.Loads.PQload pqLoad(V_nom = 20000, pq0 = {330000, 205000}) annotation(
    Placement(transformation(extent = {{28, -10}, {48, 10}})));
  inner PowerSystems.System system(dynType = PowerSystems.Types.Dynamics.SteadyState) annotation(
    Placement(transformation(extent = {{-78, 50}, {-58, 70}})));
  PowerSystems.AC3ph.Nodes.BusBar bus1 annotation(
    Placement(transformation(extent = {{-30, -10}, {-10, 10}})));
  PowerSystems.AC3ph.Nodes.BusBar bus2 annotation(
    Placement(transformation(extent = {{10, -10}, {30, 10}})));
  PowerSystems.AC3ph.Lines.PIline line1(len = 4890, redeclare record Data = PowerSystems.AC3ph.Lines.Parameters.Line(puUnits = false, r = 0.337, x = 0.358, g_pg = 0, b_pg = 51.17e-6, g_pp = 0, b_pp = 0)) annotation(
    Placement(transformation(extent = {{-10, -10}, {10, 10}})));
  PowerSystems.AC3ph.Nodes.GroundOne grd1 annotation(
    Placement(visible = true, transformation(origin = {-68, 0}, extent = {{-10, -10}, {10, 10}}, rotation = 180)));
equation
  connect(infBus.neutral, grd1.term) annotation(
    Line(points = {{-50, 0}, {-58, 0}, {-58, 0}, {-58, 0}}, color = {0, 0, 255}));
  connect(infBus.term, bus1.term) annotation(
    Line(points = {{-30, 0}, {-25, 0}, {-20, 0}}, color = {0, 120, 120}));
  connect(pqLoad.term, bus2.term) annotation(
    Line(points = {{28, 0}, {24, 0}, {20, 0}}, color = {0, 120, 120}));
  connect(line1.term_n, bus2.term) annotation(
    Line(points = {{10, 0}, {15, 0}, {20, 0}}, color = {0, 120, 120}));
  connect(line1.term_p, bus1.term) annotation(
    Line(points = {{-10, 0}, {-16, 0}, {-20, 0}}, color = {0, 120, 120}));
  annotation(
    uses(PowerSystems(version = "0.7 dev")));
end Slack_Load_Line_Ground_Sample;
