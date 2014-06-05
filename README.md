EdGen Event Generator
==================

This code is for a common Event Generator for the HASPECT collaboration.
It uses the ROOT (root.cern.ch) PhaseSpace generator has basis and 
See http://www2.ph.ed.ac.uk/~lzana/Documents/zana_haspect_genova2014.pdf for a quick presentation on this code.
This version respect to the common version it supports the BOS output format (for CLAS6 analysis) if the system has it.

Prerequisites
-------------
* CERN ROOT  (tested at now with version ROOT 5.34/09
* git 
* cmake
* Tested on ifarm.jlab.org on June 5 2014. Needs CLAS software (and OLD CERN LIBS) 
* Environment variables on ifarm.jlab.org
setenv CERNLIB /apps/cernlib/x86_64_rhel4/2005/lib
setenv CVSROOT /group/clas/clas_cvs
setup cernlib tcl
source /group/clas/builds/environment.csh

Install
-------
This version is running correctly on ifarm.jlab.org. The version of cmake there is too old, so, just use /work/halla/parity/disk2/zana/Cmake/cmake-2.8.8/bin/cmake rather than the default cmake.
* cd EdGen (go to the EdGen directory)
* git checkout Development (switch to this version).
* mkdir build
* cd build
* if you want to install BOS output support you will need to have correctly setup in your environment variables CLAS6LIB CLAS6INC and CERNLIB (the environment show before has been tested)
* if you don't want BOS support, just unset those environment variables (CLAS6LIB CLAS6INC and CERNLIB). If you will request a BOS output the code will not create any bos file (strangely enough)
* cmake ../ ( at jlab /work/halla/parity/disk2/zana/Cmake/cmake-2.8.8/bin/cmake ../ )
* make 

Running
-------
* cd EdGen/output (go to the output directory)
* A table with particle properties is in this directory (from PDG) eg_pdg_table.txt :Modify it if you need it. 
* A template is in input.dat (input_test.dat it is just for my developments at now), and modify the file to fit your reaction
* ./EdGen -h will give you the options
* ./EdGen -i input.dat -o output.root        (Change input.dat or output.root (need to be a *.root) to your desired input and output file format 
  

