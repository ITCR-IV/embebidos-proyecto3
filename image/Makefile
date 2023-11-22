CXX = g++
CXXFLAGS=-fopenmp -g -I$(IDIR) -Wall -Wextra `pkg-config --cflags --libs opencv4`

IDIR=include
ODIR=obj
SRCDIR=src

LIBS=-lm

# !!!!!! AGREGAR HEADERS AQUÍ
# Headers dentro de include/
_DEPS = filtros.hpp
DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))

# !!!!! AGREGAR SOURCE OBJECT FILES AQUÍ
# Object files (.o) que haya que compilar 
_OBJ = main.o filtros.o
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))

$(ODIR)/%.o: $(SRCDIR)/%.cpp $(DEPS)
	@mkdir -p $(@D)
	$(CXX) -c -o $@ $< $(CXXFLAGS)

main: $(OBJ)
	$(CXX) -fopenmp  -o $@ $^ $(CXXFLAGS) $(LIBS)

.PHONY: clean

clean:
	rm -f $(ODIR)/*.o core *~ $(INCDIR)/*~ 
	rmdir $(ODIR)
