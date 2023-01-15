# Setting up the NIOSII/e

After cloning the repository from github, make sure you include the NIOSII processor qip file (which is named top_level.qip) and set top_level.v as the top level entity.

# Writing C code for the NIOSII processor

You can use Tools / NIOS II Software Build Tools for Eclipse. You will probably have to install this if you have Quartus version 19.1 or onwards. Instructions for downloading can be found <a href=https://www.intel.com/content/www/us/en/support/programmable/articles/000086893.html>here</a>. Create a new file using New / NIOS II Application and BSP from Template. You will have to select the SOPC file in the main directory of the project. I had to downgrade my Quartus to version 17 to get the Eclipse tool to work.

