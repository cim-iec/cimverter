{{#CONNECTED_SECTION}}
 connect({{PORT1}},{{PORT2}})
annotation({{CONNECTION_TYPE}}(points={{POINTS}},color = {{COLOR}}, smooth = Smooth.None));
{{/CONNECTED_SECTION}}
{{#UNCONNECTED_SECTION}}
 connect({{PORT1}},{{PORT2}});
{{/UNCONNECTED_SECTION}}

 

