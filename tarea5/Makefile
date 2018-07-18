
# --------------------------------------------------------------------
#  Makefile de tarea 5.

#  Laboratorio de Programación 2.
#  InCo-FIng-UDELAR

# Define un conjunto de reglas.
# Cada regla tiene un objetivo, dependencias y comandos.
#objetivo: dependencia1 dependencia2...
#	comando1
#	comando2
#	comando3
# (antes de cada comando hay un tabulador, no espacios en blanco).
# Se invoca con
#make objetivo
# para que se ejecuten los comandos.
#
# Si `objetivo' es un archivo los comandos se ejecutan solo si no está
# actualizado (esto es, si su fecha de actualización es anterior a la de alguna
# de sus dependencias.
# Previamente se aplica la regla de cada dependencia.


# --------------------------------------------------------------------

# Objetivo predeterminado (no se necesita especificarlo al invocar `make').
all: principal

# Objetivos que no son archivos.
.PHONY: all clean_bin clean_test clean testing entrega uso_memoria


# directorios
HDIR    = include
CPPDIR  = src
ODIR    = obj

TESTDIR = test

MODULOS = info cadena binario pila cola_binarios conjunto iterador cola_prioridad tabla uso_tads

# cadena de archivos, con directorio y extensión
HS   = $(MODULOS:%=$(HDIR)/%.h)
CPPS = $(MODULOS:%=$(CPPDIR)/%.cpp)
OS   = $(MODULOS:%=$(ODIR)/%.o)

PRINCIPAL=principal
EJECUTABLE=principal

# compilador
CC = g++
# opciones de compilación
CCFLAGS = -Wall -Werror -I$(HDIR) -g -DNDEBUG
# -DNDEBUG
# se agrega esta opción para que las llamadas a assert no hagan nada.

$(ODIR)/$(PRINCIPAL).o:$(PRINCIPAL).cpp
	$(CC) $(CCFLAGS) -c $< -o $@

# cada .o depende de su .cpp
# $@ se expande para tranformarse en el objetivo
# $< se expande para tranformarse en la primera dependencia
$(ODIR)/%.o: $(CPPDIR)/%.cpp $(HDIR)/%.h
	$(CC) $(CCFLAGS) -c $< -o $@

# $^ se expande para tranformarse en todas las dependencias
$(EJECUTABLE): $(ODIR)/$(PRINCIPAL).o $(OS)
	$(CC) $(CCFLAGS) $^ -o $@


# casos de prueba de memoria
CASOS_MEM = 001 002 003 004

# cadena de archivos, con directorio y extensión
INS_MEM=$(CASOS_MEM:%=$(TESTDIR)/%-mem.in)
OUTS_MEM=$(CASOS_MEM:%=$(TESTDIR)/%-mem.out)
SALS_MEM=$(CASOS_MEM:%=$(TESTDIR)/%-mem.sal)
DIFFS_MEM=$(CASOS_MEM:%=$(TESTDIR)/%-mem.diff)

$(SALS_MEM):$(EJECUTABLE)
# el guión antes del comando es para que si hay error no se detenga la
# ejecución de los otros casos
$(TESTDIR)/%-mem.sal:$(TESTDIR)/%-mem.in
	-timeout 10 valgrind -q --leak-check=full ./$(EJECUTABLE) < $< > $@ 2>&1
	@if [ $$(stat -L -c %s $@) -ge 10000 ]; then \
		echo "tamaño excedido" > $@;\
	fi



# casos de prueba
CASOS = 00t-b 00t-c 00t-k 00t-avl 00t-cp 00t-t 00t-mayores 01 02 03 04 05 06 07 08

# cadena de archivos, con directorio y extensión
INS=$(CASOS:%=$(TESTDIR)/%.in)
OUTS=$(CASOS:%=$(TESTDIR)/%.out)
SALS=$(CASOS:%=$(TESTDIR)/%.sal)
DIFFS=$(CASOS:%=$(TESTDIR)/%.diff)

$(SALS):$(EJECUTABLE)
# el guión antes del comando es para que si hay error no se detenga la
# ejecución de los otros casos
$(TESTDIR)/%.sal:$(TESTDIR)/%.in
	-timeout 2 valgrind -q --leak-check=full ./$(EJECUTABLE) < $< > $@ 2>&1
#	-timeout 2 ./$(EJECUTABLE) < $< > $@ 2>&1
	@if [ $$(stat -L -c %s $@) -ge 10000 ]; then \
		echo "tamaño excedido" > $@;\
	fi

# test de tiempo
$(TESTDIR)/00t-b.sal:$(TESTDIR)/00t-b.in
	-timeout 8 ./$(EJECUTABLE) < $< > $@ 2>&1
$(TESTDIR)/00t-c.sal:$(TESTDIR)/00t-c.in
	-timeout 8 ./$(EJECUTABLE) < $< > $@ 2>&1
$(TESTDIR)/00t-k.sal:$(TESTDIR)/00t-k.in
	-timeout 8 ./$(EJECUTABLE) < $< > $@ 2>&1
$(TESTDIR)/00t-avl.sal:$(TESTDIR)/00t-avl.in
	-timeout 8 ./$(EJECUTABLE) < $< > $@ 2>&1
$(TESTDIR)/00t-cp.sal:$(TESTDIR)/00t-cp.in
	-timeout 8 ./$(EJECUTABLE) < $< > $@ 2>&1
$(TESTDIR)/00t-t.sal:$(TESTDIR)/00t-t.in
	-timeout 4 ./$(EJECUTABLE) < $< > $@ 2>&1
$(TESTDIR)/00t-mayores.sal:$(TESTDIR)/00t-mayores.in
	-timeout 4 ./$(EJECUTABLE) < $< > $@ 2>&1




%.diff:Makefile
# cada .diff depende de su .out y de su .sal
%.diff: %.out %.sal
	@diff $^ > $@;                                            \
	if [ $$? -ne 0 ];                                         \
	then                                                      \
		echo ---- ERROR en caso $@ ----;                  \
	fi
# Con $$? se obtiene el estado de salida del comando anterior.
# En el caso de `diff', si los dos archivos comparados no son iguales,
# el estado de la salida no es 0 y en ese caso se imprime el mensaje.




print_casos:
	@echo Ejecutando casos de prueba

print_casos_memoria:
	@echo Ejecutando casos de prueba de memoria


# Test general. Las dependencias son los .diff.
# Con `find` se encuentran los .diff de tamaño > 0 que están en el directorio
# $(TESTDIR) y lo asigna a $(LST_ERR).
# Si el tamaño de $(LST_ERR) no es cero imprime los casos con error.
# Con `sed` se elimina el nombre de directorio y la extensión.
testing:all print_casos_memoria $(DIFFS_MEM) print_casos $(DIFFS)
	@LST_ERR=$$(find $(TESTDIR) -name *.diff* -size +0c -print);             \
	if [ -n "$${LST_ERR}" ];                                                \
	then                                                                    \
		echo -- CASOS CON ERRORES --;                                   \
		echo "$${LST_ERR}" | sed -e 's/$(TESTDIR)\///g' -e 's/.diff//g';\
	fi


# Genera el entregable.
ENTREGA=Entrega5.tar.gz
CPPS_ENTREGA = $(MODULOS:%=%.cpp)
entrega:
	@rm -f $(ENTREGA)
	tar zcvf $(ENTREGA) -C src $(CPPS_ENTREGA)
	@echo --        El directorio y archivo a entregar es:
	@echo $$(pwd)/$(ENTREGA)


# borra binarios
clean_bin:
	@rm -f $(EJECUTABLE) $(ODIR)/$(PRINCIPAL).o $(OS) ejemplos_letra

# borra resultados de ejecución y comparación
clean_test:
	@rm -f $(TESTDIR)/*.sal $(TESTDIR)/*.diff $(TESTDIR)/*.sal_mem $(TESTDIR)/*.diff_mem

# borra binarios, resultados de ejecución y comparación, y copias de respaldo
clean:clean_test clean_bin
	@rm -f *~ $(HDIR)/*~ $(CPPDIR)/*~ $(TESTDIR)/*~



check-syntax:
	gcc -o nul -S ${CHK_SOURCES}
