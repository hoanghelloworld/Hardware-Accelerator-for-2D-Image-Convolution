############################################################
## This file is generated automatically by Vivado HLS.
## Please DO NOT edit it.
## Copyright (C) 1986-2018 Xilinx, Inc. All Rights Reserved.
############################################################
open_project final_conv2d
set_top do_convolution
add_files conv.cpp
add_files conv.h
add_files define.h
add_files -tb test_conv.cpp
add_files -tb testutils.cpp
add_files -tb testutils.h
open_solution "solution1"
set_part {xc7z020clg484-1} -tool vivado
create_clock -period 10 -name default
#source "./final_conv2d/solution1/directives.tcl"
csim_design
csynth_design
cosim_design
export_design -format ip_catalog
