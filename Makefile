include Makefile.arch

#------------------------------------------------------------------------------

EDGENS  := $(wildcard *.$(SrcSuf))
EDGENH  := $(wildcard *.h)
EDGENO  := $(EDGENS:.$(SrcSuf)=.$(ObjSuf)) 
EDGEN    = EdGen$(ExeSuf)
CLASLIBS = -lc_bos_io

OBJS          = $(EDGENO)

PROGRAMS      = $(EDGEN)

FC=gfortran
FFLAGS= -O2

#------------------------------------------------------------------------------

.SUFFIXES: .$(SrcSuf) .$(ObjSuf) .$(DllSuf)

all:            $(PROGRAMS)

$(EDGEN):  $(EDGENO)
		@echo "this: $@, $(EDGENO)"
		$(LD) $(LDFLAGS) $^ $(GLIBS) -I$(CLAS6INC) -L$(CLAS6LIB) -ggdb -O2 -lEG -lGed -lHtml -lThread -lGeom $(CLASLIBS) $(OutPutOpt)$@
		cp EdGen output/
		@echo "$@ done"

EdGen.$(SrcSuf): 
		@echo "Generating dictionary $@..."
		@rootcint -I$(CLAS6INC) -L$(CLAS6LIB)  -f $@ -c $^


clean:
		@rm -f $(OBJS) *.res core 

distclean:      clean
		@rm -f $(PROGRAMS) *Dict.* *.def *.exp \
		   *.geom *.root *.ps *.so .def so_locations
		@rm -rf cxx_repository

###

.$(SrcSuf).$(ObjSuf): 
		$(CXX) $(CXXFLAGS) -c -g $<



