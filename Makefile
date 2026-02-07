# --------------------------------------------------------------------
# Makefile Genérico :: Módulo 2. Curso Experto Desarrollo Videojuegos
# Carlos González Morcillo     Escuela Superior de Informática (UCLM)
# --------------------------------------------------------------------
EXEC := example1


DIRSRC := src/
DIROBJ := obj/
DIRHEA := include/

CXX := g++

# Componentes de OGRE necesiarios ------------------------------------
OGRE_COMPONENTS := OGRE OGRE-Bites OGRE-RTShaderSystem OGRE-Overlay

# Flags de compilación -----------------------------------------------
CXXFLAGS := -I$(DIRHEA) -Wall -fPIC -std=c++17 `pkg-config --cflags $(OGRE_COMPONENTS)` 

# Flags del linker ---------------------------------------------------
LDFLAGS := `pkg-config --libs-only-L $(OGRE_COMPONENTS)` 
LDLIBS := `pkg-config --libs-only-l $(OGRE_COMPONENTS)` -lGL
# Modo de compilación (-mode=release -mode=debug) --------------------
ifeq ($(mode), release) 
	CXXFLAGS += -O2 -D_RELEASE
else 
	CXXFLAGS += -g -D_DEBUG
	mode := debug
endif

# Obtención automática de la lista de objetos a compilar -------------
OBJS := $(subst $(DIRSRC), $(DIROBJ), \
	$(patsubst %.cpp, %.o, $(wildcard $(DIRSRC)*.cpp)))

.PHONY: all clean

all: info $(EXEC)

info:
	@echo '------------------------------------------------------'
	@echo '>>> Using mode $(mode)'
	@echo '    (Please, call "make" with [mode=debug|release])  '
	@echo '------------------------------------------------------'

# Enlazado -----------------------------------------------------------
$(EXEC): $(OBJS)
	$(CXX) $(LDFLAGS) -o $@ $^ $(LDLIBS)

# Compilación --------------------------------------------------------
$(DIROBJ)%.o: $(DIRSRC)%.cpp
	@mkdir -p $(DIROBJ)
	$(CXX) $(CXXFLAGS) -c $< -o $@ 

# Limpieza de temporales ---------------------------------------------
clean:
	rm -f *.log $(EXEC) *~ $(DIROBJ)* $(DIRSRC)*~ $(DIRHEA)*~ 