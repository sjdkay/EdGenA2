include Makefile.arch

#------------------------------------------------------------------------------

EDGENS  := $(wildcard *.$(SrcSuf))
EDGENH  := $(wildcard *.h)
EDGENO  := $(EDGENS:.$(SrcSuf)=.$(ObjSuf)) 
EDGEN    = EdGen$(ExeSuf)

OBJS          = $(EDGENO)

PROGRAMS      = $(EDGEN)

FC=gfortran
FFLAGS= -O2

#------------------------------------------------------------------------------

.SUFFIXES: .$(SrcSuf) .$(ObjSuf) .$(DllSuf)

all:            $(PROGRAMS)

$(EDGEN):  $(EDGENO)
		@echo "this: $@, $(EDGENO)"
		$(LD) $(LDFLAGS) $^ $(GLIBS) -ggdb -O2 -lEG -lGed -lHtml -lThread -lGeom  $(OutPutOpt)$@
		cp EdGen output/
		@echo "$@ done"

EdGen.$(SrcSuf): 
		@echo "Generating dictionary $@..."
		@rootcint -f $@ -c $^


clean:
		@rm -f $(OBJS) *.res core 

distclean:      clean
		@rm -f $(PROGRAMS) *Dict.* *.def *.exp \
		   *.geom *.root *.ps *.so .def so_locations
		@rm -rf cxx_repository

###

.$(SrcSuf).$(ObjSuf): 
		$(CXX) $(CXXFLAGS) -c -g $<



