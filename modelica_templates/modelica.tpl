{{#HEADER_FOOTER_SECTION}}model {{GRID_NAME}} {{/HEADER_FOOTER_SECTION}}

{{!-----Global Grid Settings-------}}

{{#GLOBAL_SETTINGS_SECTION}}

annotation(Diagram(coordinateSystem(extent = {{{{DIAGRAM_EXTENT_X1}},{{DIAGRAM_EXTENT_Y1}}},{{{DIAGRAM_EXTENT_X2}},{{DIAGRAM_EXTENT_Y2}}}},rotation={{ROTATION}},preserveAspectRatio = {{PAR}})), Icon(coordinateSystem(extent = {{{ICON_EXTENT_X1}}, {{ICON_EXTENT_Y1}}}, {{{ICON_EXTENT_X2}}, {{ICON_EXTENT_Y2}}}})));  

{{/GLOBAL_SETTINGS_SECTION}}

{{!----ModPowerSystems Components-------}}

{{>BUSBAR_DICT}}

{{>SLACK_DICT}}

{{>WINDGENERATOR_DICT}}

{{>PQLOAD_DICT}}

{{>ZLOAD_DICT}}

{{>PILINE_DICT}}

{{>RXLINE_DICT}}

{{>TRANSFORMER_DICT}}

{{!----Connections-------}}

{{>CONNECTIONS_DICT}}

{{#HEADER_FOOTER_SECTION}}end {{GRID_NAME}}; {{/HEADER_FOOTER_SECTION}}
