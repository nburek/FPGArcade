
# PlanAhead Launch Script for Pre-Synthesis Floorplanning, created by Project Navigator

create_project -name VGA_Driver -dir "C:/Documents and Settings/nb418308/Desktop/FPGArcade/VGA_Driver/planAhead_run_1" -part xc3s500efg320-4
set_param project.pinAheadLayout yes
set srcset [get_property srcset [current_run -impl]]
set_property top top $srcset
set_param project.paUcfFile  "top.ucf"
set hdlfile [add_files [list {clk25MHz.vhd}]]
set_property file_type VHDL $hdlfile
set_property library work $hdlfile
set hdlfile [add_files [list {top.vhdl}]]
set_property file_type VHDL $hdlfile
set_property library work $hdlfile
add_files "top.ucf" -fileset [get_property constrset [current_run]]
open_rtl_design -part xc3s500efg320-4
