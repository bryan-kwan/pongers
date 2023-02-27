# Setting up the NIOSII

After cloning the repository from github, make sure you include the NIOSII processor qip file (which is named top_level.qip) and set top_level.v as the top level entity. You may choose to recreate or customize the design using Tools / Platform Designer.

# Writing C code for the NIOSII processor

You can use Tools / NIOS II Software Build Tools for Eclipse (It's safer to use the nios 2 terminal and launching using eclipse-nios2.exe). You will probably have to install this if you have Quartus version 19.1 or onwards. Instructions for downloading can be found <a href=https://www.intel.com/content/www/us/en/support/programmable/articles/000086893.html>here</a>. Create a new file using New / NIOS II Application and BSP from Template. You will have to select the SOPC file in the main directory of the project. I had to downgrade my Quartus to version 17 to get the Eclipse tool to work.

Once you have written your C program, go to Project / Build Project. If it is your first time running this, you may see a settings screen pop up. Afterwards, you will see an .elf file was generated. After you program the hardware onto the board in Quartus Tools / Programmer, you can load the .elf file code into the NIOS core by right clicking the .elf file and selecting Run As / NIOS II Hardware.

To permanently load your C program onto the board (ie. runs on power up), right click the .elf file and select Make Targets -> Build -> mem_init_generate. This will create the mem init hex file as well as the .qip file. You can include the .qip file in your quartus project or select the hex file in platform designer for on-chip memory. *IMPORTANT NOTE: You must disable (ie. select None in the BSP editor) stdin, stdout, stderr before generating the mem_init file or else the program will hang upon reaching a printf() statement.

# Pin assignments on the DE10-Lite After Using Generate

Note that after generating the verilog files from platform designer, you must change the names of the VGA signals from the VGA driver component. Eg. Change vga_conduit_HS to VGA_HS in order to match the default pin naming. 

You should make sure the following signals are connected in pin planner after using generate:

VGA_HS, VGA_VS, VGA_R, VGA_G, VGA_B

clk_clk (NIOS II clock)

DRAM_CLK (Connect this to the -3ns phase shifted 100MHz clock from the PLL)

You may also hook up the GPIO, LEDR, SW, buttons, etc. if you want.

# VGA Display Setup

The overall setup followed <a href="https://faculty-web.msoe.edu/johnsontimoj/EE3921/files3921/nios_pixel_sw.pdf">this reference</a>.

# Setup of the SDRAM Controller

Setup of the SDRAM Controller was taken from <a href="https://github.com/hildebrandmw/de10lite-hdl/tree/master/components/dram">this guide</a>. 

A copy of the instructions are provided below.

### Memory Profile

| Parameter      | Value     |
|----------------|-----------|
| Bits           | 16        |
| Chip select    | 1         |
| Banks          | 4         |
| Rows           | 13        |
| Columns        | 10        |

### Timing

| Parameter                       | Setting   |
|---------------------------------|-----------|
| CAS Latency                     | 2         |
| Initialization refresh cycles   | 8         |
| Issue one refresh every         | 7.8125 ns |
| Delay after powerup             | 100 us    |
| `t_rfc`                         | 55 ns     |
| `t_rp`                          | 15 ns     |
| `t_rcd`                         | 15 ns     |
| `t_ac`                          | 6 ns      |
| `t_wr`                          | 14 ns     |

## Clocking
The SDRAM controller (and SDRAM itself ... wouldn't really make much
sense to clock the two at different frequencies ... ) should be clocked with a 
```
100 MHz
```
clock. What is a little less obvious is that the external clock should be
phase shifted by
```
-3 ns
```
to accomodate for signal propogation delay. Both of these signals can be
generated from the available `50 MHz` clock using a PLL. An overview
of this scheme is summarized in the figure below.

## IO Timing Constraints
To ensure the DRAM control signals more or less arrive at the same time,
the DRAM IO pins should be timing constrained.
