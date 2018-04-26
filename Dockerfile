# define on which img our img should be based
FROM debian:latest

LABEL \
	org.label-schema.schema-version = "2.1.0" \
	org.label-schema.name = "CIM2Mod" \
	org.label-schema.license = "MPL" \
	org.label-schema.vendor = "Institute for Automation of Complex Power Systems, RWTH Aachen University" \
	org.label-schema.author.name = "Lukas Razik" \
	org.label-schema.author.email = "lrazik@eonerc.rwth-aachen.org" \
	org.label-schema.vcs-url = "https://git.rwth-aachen.de/acs/core/cim/CIM2Mod"

RUN apt-get update

# Define which libaries should be included in the dockerimg
RUN apt-get install -y git cmake clang build-essential g++ python-dev autotools-dev libicu-dev build-essential libbz2-dev libboost-all-dev libctemplate-dev libconfig++-dev doxygen libxml2 libxml2-dev
