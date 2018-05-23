import re
from dataprocessing.readtools import *

file = r"..\results\neplan\Slack_Load_Line_Sample.rlf"

result_neplan = read_timeseries_NEPLAN_loadflow(file, '^.*\.U$', True)
for i in range(len(result_neplan)):
    print('%s is %s' % (result_neplan[i].name, result_neplan[i].values))
