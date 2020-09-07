{{#NO_PILINE_VNOM}}
ModPowerSystems.PhasorSinglePhase.Connections.PiLine {{NAME}}(Imax(displayUnit = "{{IMAX_DISPLAYUNIT}}") = {{IMAX}}, Sr(displayUnit = "{{SR_DISPLAYUNIT}}") = {{SR}}, g = {{G}}, length={{LENGTH_KM}}, r={{R}}, x={{X}}, b={{B}})
annotation (Placement(visible = {{VISIBLE}}, transformation(extent = {{TRANS_EXTENT_POINTS}}, rotation = {{ROTATION}}, origin = {{ORIGIN_POINT}})));
{{/NO_PILINE_VNOM}}
{{#PILINE_VNOM}}
ModPowerSystems.PhasorSinglePhase.Connections.PiLine {{NAME}}(Imax(displayUnit = "{{IMAX_DISPLAYUNIT}}") = {{IMAX}}, Sr(displayUnit = "{{SR_DISPLAYUNIT}}") = {{SR}}, g = {{G}}, length={{LENGTH_KM}}, r={{R}}, x={{X}}, b={{B}}, Vnom(displayUnit = "{{VNOM_DISPLAYUNIT}}") = {{VNOM}})
annotation (Placement(visible = {{VISIBLE}}, transformation(extent = {{TRANS_EXTENT_POINTS}}, rotation = {{ROTATION}}, origin = {{ORIGIN_POINT}})));
{{/PILINE_VNOM}}
