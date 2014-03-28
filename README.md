EdGen Event Generator
==================

This code is for a common Event Generator for the HASPECT collaboration.
It uses the ROOT (root.cern.ch) PhaseSpace generator has basis and 
See http://www2.ph.ed.ac.uk/~lzana/Documents/zana_haspect_camogli2013.pdf for a quick presentation on this code.

Prerequisites
-------------
* CERN ROOT  (tested at now with version ROOT 5.34/09
* git 

Running
-------
* cd output (go to the output directory)
* A table with particle properties is in this directory (from PDG) eg_pdg_table.txt :Modify it if you need it. 
* A template is in input.dat (input_test.dat it is just for my developments at now), and modify the file to fit your reaction
* ./EdGen -h will give you the options
* ./EdGen -i input.dat -o output.root        (Change input.dat or output.root (need to be a *.root) to your desired input and output file format 
  

