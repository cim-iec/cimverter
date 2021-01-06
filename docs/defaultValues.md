# Exception Handlers
| Object        | Attribute           | Default Value  | Warning |
| -------- |:-------------:| -----:| ----------:|
| Busbar      | annotation.placement.transformation.rotation | 0 | Missing rotation for diagram obj "name"|
| Slack | sequenceNumber | 0 | Some Warning|
| Slack | connected | 1	 | Missing connected property for terminal "terminalName"|
| PiLine | r | length | Missing r value "ACLineName"|
| PiLine | x | length | Missing x value "ACLineName"|
| PiLine | b | length | Missing bch value "ACLineName"|
| PiLine | g | 0 | Missing gch value "ACLineName"|
| PiLine | bus1 | busbar | Missing terminal seqNR "terminalName"|
| PiLine | VNom | -1 | No Base Voltage at corresponding TPNode for PiLine "PILineName"|
| PiLine | connected | 1 | Missing connection info in terminal "TerminalName"|
| PiLine      | annotation.placement.transformation.rotation | 0 | Missing rotation for diagram obj "name"|
| ModTransformer | bus1 | busbar | Missing sequence number in terminal sequence number "TerminalName"|
| ModTransformer | connected | 1 | Missing connected property in terminal "TerminalName"|
| ModTransformer      | annotation.placement.transformation.rotation | 0 | Missing rotation for diagram obj "name"|
| PQLoad | PNom | 1 | Missing entry in PowerFlow Map for terminal: "terminalName"|
| PQLoad | QNom | 1 | Missing entry in PowerFlow Map for terminal: "terminalName"|
| PQLoad | sequenceNumber | 0 | Missing sequence number in terminal sequence number "TerminalName"|
| PQLoad | connected | 0 | Missing connection info in terminal "TerminalName"|
| PQLoad      | annotation.placement.transformation.rotation | 0 | Missing rotation for diagram obj "name"|
| SolarGenerator | sequenceNumber | 0 | Missing sequence number in terminal sequence number "TerminalName"|
| WindGenerator | sequenceNumber | 0 | Missing sequence number in terminal sequence number "TerminalName"|
| Breaker | connected | 0 | Missing connection info in terminal "TerminalName"|
| Breaker | bus1 | busbar | Missing sequence number in terminal sequence number "TerminalName"|
| Breaker | annotation.placement.transformation.rotation | 0 | Missing rotation for diagram obj "name"|
| SynMachineDyn | sequenceNumber | 0 | Missing sequence number in terminal sequence number "TerminalName"|
| SynMachineDyn | UPhaseStart | - | No SVVoltage at TPNode for SynMachineDyn "SynMachineName"|
| SynMachineDyn | UStart | - | No SVVoltage at TPNode for SynMachineDyn "SynMachineName"|
| SynMachineDyn | QStart | - | No SVPowerFlow at terminal for SynMachineDyn "SynMachineName"|
| SynMachineDyn | PStart | - | No SVPowerFlow at terminal for SynMachineDyn "SynMachineName"|
| SynMachineDyn | annotation.placement.transformation.rotation | 0 | Missing rotation for diagram obj "name"|
| PVNode | sequenceNumber | 0 | Missing sequence number in terminal sequence number "TerminalName"|
| PVNode | connected | 1 | Missing connection info in terminal "TerminalName"|
| PVNode | ratedU | TPNode.BaseVoltage| Unitialized ratedU for Synchronous Machine taking TopologicalNode BaseVoltage "SynMachineName"|
| PVNode | annotation.placement.transformation.rotation | 0 | Missing rotation for diagram obj "name"|
