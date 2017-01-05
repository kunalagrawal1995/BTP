#!/bin/bash

#gcc ply_io.c ply_to_obj.c -lm -o p2o

#ply format
filename=$1
./p2o < $filename > out.obj
pcl_obj2pcd out.obj out.pcd
pcl_viewer out.pcd 