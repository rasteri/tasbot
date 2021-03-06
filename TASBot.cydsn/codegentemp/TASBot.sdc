# THIS FILE IS AUTOMATICALLY GENERATED
# Project: C:\Users\Thomas\Documents\PSoC Creator\TASBot\TASBot.cydsn\TASBot.cyprj
# Date: Sun, 25 Dec 2016 01:08:13 GMT
#set_units -time ns
create_clock -name {VisClock(routed)} -period 100000 -waveform {0 50000} [list [get_pins {ClockBlock/dclk_4}]]
create_clock -name {CyILO} -period 10000 -waveform {0 5000} [list [get_pins {ClockBlock/ilo}] [get_pins {ClockBlock/clk_100k}] [get_pins {ClockBlock/clk_1k}] [get_pins {ClockBlock/clk_32k}]]
create_clock -name {CyIMO} -period 41.666666666666664 -waveform {0 20.8333333333333} [list [get_pins {ClockBlock/imo}]]
create_clock -name {CyPLL_OUT} -period 13.888888888888888 -waveform {0 6.94444444444444} [list [get_pins {ClockBlock/pllout}]]
create_clock -name {CyMASTER_CLK} -period 13.888888888888888 -waveform {0 6.94444444444444} [list [get_pins {ClockBlock/clk_sync}]]
create_generated_clock -name {CyBUS_CLK} -source [get_pins {ClockBlock/clk_sync}] -edges {1 2 3} [list [get_pins {ClockBlock/clk_bus_glb}]]
create_generated_clock -name {ConsolePort_2_Clock_1} -source [get_pins {ClockBlock/clk_sync}] -edges {1 3 7} [list [get_pins {ClockBlock/dclk_glb_0}]]
create_generated_clock -name {Clock_2} -source [get_pins {ClockBlock/clk_sync}] -edges {1 3 7} [list [get_pins {ClockBlock/dclk_glb_1}]]
create_generated_clock -name {Clock_1} -source [get_pins {ClockBlock/clk_sync}] -edges {1 3 7} [list [get_pins {ClockBlock/dclk_glb_2}]]
create_generated_clock -name {ConsolePort_1_Clock_1} -source [get_pins {ClockBlock/clk_sync}] -edges {1 3 7} [list [get_pins {ClockBlock/dclk_glb_3}]]
create_generated_clock -name {VisClock} -source [get_pins {ClockBlock/clk_sync}] -edges {1 7201 14401} [list [get_pins {ClockBlock/dclk_glb_4}]]


# Component constraints for C:\Users\Thomas\Documents\PSoC Creator\TASBot\TASBot.cydsn\TopDesign\TopDesign.cysch
# Project: C:\Users\Thomas\Documents\PSoC Creator\TASBot\TASBot.cydsn\TASBot.cyprj
# Date: Sun, 25 Dec 2016 01:07:58 GMT
