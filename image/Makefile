# Definir el compilador
CXX = g++

# Opciones de compilación, incluyendo banderas de depuración y advertencias
CXXFLAGS = -Wall -Wextra -g

# Incluir y enlazar las cabeceras y librerías de OpenCV
OPENCV = `pkg-config --cflags --libs opencv4`

# Nombre del archivo ejecutable resultante
TARGET = main

# Regla por defecto
all: $(TARGET)

# Regla para construir el ejecutable
$(TARGET): main.cpp
	$(CXX) $(CXXFLAGS) -o $(TARGET) main.cpp $(OPENCV)

# Regla para limpiar archivos generados durante la compilación
clean:
	rm -f $(TARGET)

