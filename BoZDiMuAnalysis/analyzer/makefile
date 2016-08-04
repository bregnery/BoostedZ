# MakeFile

# Set the Compiler
CC = g++

# Include the root libraries
LIBFLAGS = `root-config --libs` -O3 -lXMLIO -lMLP -lMinuit

# the directory for the base library that enables the analysis
LIBDIR = ../src/

# the directory for the cut selection objects specific to the analysis
SDIR = ../selection/

# include the libdir and sdir and the root libraries
CFLAGS = -I${LIBDIR} -c -g `root-config --cflags`

# The name of the .cxx file you want to compile into an executable
MAIN = BoostedZAnalyzer

# link all of the objects to the main program
${MAIN}: ${LIBDIR}Sample.o ${SDIR}Cuts.o ${LIBDIR}SampleHistos.o ${LIBDIR}Plots.o ${MAIN}.o
	$(CC) $(LIBFLAGS) ${LIBDIR}Sample.o ${SDIR}Cuts.o ${LIBDIR}SampleHistos.o ${LIBDIR}Plots.o ${MAIN}.o -o ${MAIN}

${MAIN}.o: ${MAIN}.cxx ${LIBDIR}DataFormats.h ${LIBDIR}Plots.h 
	$(CC) $(CFLAGS) ${MAIN}.cxx -o ${MAIN}.o

# compile the dependencies
${LIBDIR}Sample.o: ${LIBDIR}Sample.cxx ${LIBDIR}Sample.h ${LIBDIR}VarSet.h ${LIBDIR}DataFormats.h
	$(CC) $(CFLAGS) ${LIBDIR}Sample.cxx -o ${LIBDIR}Sample.o

${SDIR}Cuts.o: ${SDIR}Cuts.cxx ${SDIR}Cuts.h ${LIBDIR}Sample.h
	$(CC) $(CFLAGS) ${SDIR}Cuts.cxx -o ${SDIR}Cuts.o

${LIBDIR}SampleHistos.o: ${LIBDIR}SampleHistos.cxx ${LIBDIR}SampleHistos.h ${LIBDIR}Sample.h ${SDIR}Cuts.h
	$(CC) $(CFLAGS) ${LIBDIR}SampleHistos.cxx -o ${LIBDIR}SampleHistos.o

${LIBDIR}Plots.o: ${LIBDIR}Plots.cxx ${LIBDIR}Plots.h ${LIBDIR}SampleHistos.h ${LIBDIR}Sample.h ${SDIR}Cuts.h
	$(CC) $(CFLAGS) ${LIBDIR}Plots.cxx -o ${LIBDIR}Plots.o

clean:
	rm *.o

cleanall:
	rm *.o
	rm ${LIBDIR}*.o
	rm ${SDIR}*.o
