{{#HEADER_FOOTER_SECTION}}model {{GRID_NAME}} {{/HEADER_FOOTER_SECTION}}

{{!-----Global Grid Settings-------}}

{{#SYSTEM_SETTINGS_SECTION}}
annotation(Diagram(coordinateSystem(extent = {{{{DIAGRAM_EXTENT_X1}},{{DIAGRAM_EXTENT_Y1}}},{{{DIAGRAM_EXTENT_X2}},{{DIAGRAM_EXTENT_Y2}}}})), Icon(coordinateSystem(extent = {{{{ICON_EXTENT_X1}}, {{ICON_EXTENT_Y1}}}, {{{ICON_EXTENT_X2}}, {{ICON_EXTENT_Y2}}}})));  

inner ModPowerSystems.System {{NAME}}(f_nom(displayUnit = "{{FNOM_DISPLAYUNIT}}") = {{FNOM}}, init = "{{INIT}}", simMode = "{{SIMMODE}}") 
annotation(Placement(visible = {{VISIBLE}}, transformation(extent = {{{{TRANS_EXTENT_X1}},{{TRANS_EXTENT_Y1}}},{{{TRANS_EXTENT_X2}},{{TRANS_EXTENT_Y2}}}}, rotation = {{ROTATION}})));

{{/SYSTEM_SETTINGS_SECTION}}

{{!----ModPowerSystems Components-------}}

{{>BUSBAR_DICT}}

{{>SLACK_DICT}}

{{>WINDGENERATOR_DICT}}

{{>PQLOAD_DICT}}

{{>ZLOAD_DICT}}

{{>PILINE_DICT}}

{{>RXLINE_DICT}}

{{>TRANSFORMER_DICT}}

equation

{{!----Connections-------}}

{{>CONNECTIONS_DICT}}

{{#HEADER_FOOTER_SECTION}}end {{GRID_NAME}}; {{/HEADER_FOOTER_SECTION}}
