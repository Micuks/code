#! python
# -*- coding: UTF-8 -*-

import os
import subprocess
import sys

# configure the version number
from shutil import copyfile
copyfile('VERSION', 'version.py')
from version import *
with open("osi_version.proto.in", "rt") as fin:
    with open("osi_version.proto", "wt") as fout:
        for line in fin:
            lineConfigured = line.replace('@VERSION_MAJOR@',str(VERSION_MAJOR))
            lineConfigured = lineConfigured.replace('@VERSION_MINOR@',str(VERSION_MINOR))
            lineConfigured = lineConfigured.replace('@VERSION_PATCH@',str(VERSION_PATCH))
            fout.write(lineConfigured)

package_name = 'osi3'
package_path = os.path.join(os.getcwd(), package_name)
try:
    os.mkdir(package_path)
except Exception:
    pass

osi_files = (
        'osi_version.proto',
        'osi_common.proto',
        'osi_datarecording.proto',
        'osi_detectedtrafficsign.proto',
        'osi_detectedtrafficlight.proto',
        'osi_detectedroadmarking.proto',
        'osi_detectedobject.proto',
        'osi_detectedoccupant.proto',
        'osi_detectedlane.proto',
        'osi_environment.proto',
        'osi_groundtruth.proto',
        'osi_hostvehicledata.proto',
        'osi_trafficsign.proto',
        'osi_trafficlight.proto',
        'osi_roadmarking.proto',
        'osi_featuredata.proto',
        'osi_object.proto',
        'osi_occupant.proto',
        'osi_lane.proto',
        'osi_sensordata.proto',
        'osi_sensorviewconfiguration.proto',
        'osi_sensorspecific.proto',
        'osi_sensorview.proto')

def generatecpp():
    protoc = os.path.join(os.getcwd(), "../artifactory/protoc/protoc")
    for source in osi_files:
        source_path = os.path.join(package_path, source)
        file_handle_source_path = open(source_path,'wt')
        subprocess.check_call(['sed',
                                '-e', 's/syntax *= *"proto2";/syntax = "proto3";/',
                                '-e', 's/^\([ \t]*\)optional /\\1/',
                                os.path.join(os.getcwd(), source)
                                ], stdout=file_handle_source_path)
        file_handle_source_path.close()
        print("copy done for: " + source_path)
    for source in osi_files:
        sys.stdout.write('Protobuf-compiling ' + source + '\n')
        source_path = os.path.join(package_path, source)     
        subprocess.check_call([protoc,
                                '--proto_path='+os.path.join(os.getcwd(), "../"),
                                '--proto_path='+package_path,
                                '--cpp_out='+package_path,
                                source_path])
generatecpp()
print("generate protobuf3 cpp done in: " + package_path)
