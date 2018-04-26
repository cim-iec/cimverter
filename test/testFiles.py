#!/usr/bin/python
import subprocess
import filecmp
import os
from os import listdir
from os.path import isfile, join
rootdir = '/home/achim/acs/CIM2Mod/test/xml'

diffs = 0
errors = 0
testedFiles = []
dirs = [f for f in os.listdir(rootdir) if not isfile(join(rootdir, f))]
files = [f for f in listdir(rootdir) if isfile(join(rootdir, f))]

for dir in dirs:
    bashCommand = "./create_output.bash a " + dir + " " + dir
    process = subprocess.Popen(bashCommand.split(), stdout=subprocess.PIPE)
    output, error = process.communicate()
    testedFiles.append(dir + ".mo")
for file in files:
    bashCommand = "./create_output.bash f " + file[0:len(file) - 4] + " " + file[0:len(file) - 4]
    process = subprocess.Popen(bashCommand.split(), stdout=subprocess.PIPE)
    output, error = process.communicate()
    testedFiles.append(file[0:len(file) - 4] + ".mo")


for file in testedFiles:
    bashCommand = "diff --suppress-common-lines --side-by-side " + "outputs/" + file + " modelica/" + file
    process = subprocess.Popen(bashCommand.split(), stdout=subprocess.PIPE, stderr=subprocess.PIPE)
    out, err = process.communicate()

    if out and not out.isspace():
        print out
        diffs += 1
    elif err and not err.isspace():
        errors += 1
        print err

if diffs == 0 and errors == 0:
    print "Everything fine"
    exit(0)
else:
    print "Some errors occured"
    exit(1)


