import re
from dataprocessing.readtools import *

# Comparison for Slack-Line-Load
print('--- Slack-Line-Load ---')
print('--- NEPLAN ---')
filename_neplan = r"..\results\neplan\Slack_Load_Line_Sample.rlf"
result_neplan = read_timeseries_NEPLAN_loadflow(filename_neplan, '^[^.]*.((Vpp)|(Vangle))', True)
for i in range(len(result_neplan)):
    print('%s is %s' % (result_neplan[i].name, result_neplan[i].values[0]))

print('--- ModPowerSystems ---')
filename_modpowersystems = r"..\results\modelica\modpowersystems\modpowersystems_slack_load_line_sample_v3.mat"
result_modpowersystems = read_timeseries_Modelica(filename_modpowersystems, timeseries_names='^[^.]*N\d+.((Vpp)|(Vangle))$', is_regex=True)
for i in range(len(result_modpowersystems)):
    print('%s is %s' % (result_modpowersystems[i].name, result_modpowersystems[i].values[0]))

print('--- PowerSystems ---')
filename_powersystems = r"..\results\modelica\powersystems\powersystems_slack_load_line_sample_v8_with_ground.mat"
result_powersystems = read_timeseries_Modelica(filename_powersystems, timeseries_names='^[^.]*N\d+.((v_norm)|(alpha_v))$', is_regex=True)
for i in range(len(result_powersystems)):
    print('%s is %s' % (result_powersystems[i].name, result_powersystems[i].values[0]))

# Comparison for Slack-Trafo-Load    
print('--- Slack-Trafo-Load ---')
print('--- NEPLAN ---')
filename_neplan2 = r"..\results\neplan\Slack_Trafo_Load_Sample.rlf"
result_neplan2 = read_timeseries_NEPLAN_loadflow(filename_neplan2, '^[^.]*.((Vpp)|(Vangle))', True)
for i in range(len(result_neplan2)):
    print('%s is %s' % (result_neplan2[i].name, result_neplan2[i].values[0]))

print('--- ModPowerSystems ---')
filename_modpowersystems2 = r"..\results\modelica\modpowersystems\modpowersystems_slack_trafo_load_sample_v1.mat"
result_modpowersystems2 = read_timeseries_Modelica(filename_modpowersystems2, timeseries_names='^[^.]*N\d+.((Vpp)|(Vangle))$', is_regex=True)
for i in range(len(result_modpowersystems2)):
    print('%s is %s' % (result_modpowersystems2[i].name, result_modpowersystems2[i].values[0]))

print('--- PowerSystems ---')
filename_powersystems2 = r"..\results\modelica\powersystems\powersystems_slack_trafo_load_sample_v3_with_ground.mat"
result_powersystems2 = read_timeseries_Modelica(filename_powersystems2, timeseries_names='^[^.]*N\d+.((v_norm)|(alpha_v))$', is_regex=True)
for i in range(len(result_powersystems2)):
    print('%s is %s' % (result_powersystems2[i].name, result_powersystems2[i].values[0]))