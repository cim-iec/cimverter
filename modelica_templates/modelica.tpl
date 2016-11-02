{{#HEADER_FOOTER_SECTION}}model {{GRID_NAME}} {{/HEADER_FOOTER_SECTION}}

{{!-----Global Grid Settings-------}}

{{#SYSTEM_SETTINGS_SECTION}}
annotation(Diagram(coordinateSystem(extent = {{DIAGRAM_EXTENT_POINTS}})), Icon(coordinateSystem(extent = {{ICON_EXTENT_POINTS}})));  

inner ModPowerSystems.System {{NAME}}(f_nom(displayUnit = "{{FNOM_DISPLAYUNIT}}") = {{FNOM}}, init = "{{INIT}}", simMode = "{{SIMMODE}}") 
annotation(Placement(visible = {{VISIBLE}}, transformation(extent = {{TRANS_EXTENT_POINTS}}, rotation = {{ROTATION}})));

{{/SYSTEM_SETTINGS_SECTION}}

{{!----ModPowerSystems Components-------}}

{{>BUSBAR_DICT}}

{{>CONNECTIVITYNODE_DICT}}

{{>SLACK_DICT}}

{{>WINDGENERATOR_DICT}}

{{>PQLOAD_DICT}}

{{>ZLOAD_DICT}}

{{>PILINE_DICT}}

{{>RXLINE_DICT}}

{{>TRANSFORMER_DICT}}

{{>GENERICGENERATOR_DICT}}

equation

{{!----Connections-------}}

{{>CONNECTIONS_DICT}}

{{#HEADER_FOOTER_SECTION}}end {{GRID_NAME}}; {{/HEADER_FOOTER_SECTION}}
