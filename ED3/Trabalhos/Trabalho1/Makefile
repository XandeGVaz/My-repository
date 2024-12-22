APPS = ./apps
BIN = ./bin
INCLUDE = ./include
OBJ = ./obj
SRC = ./src

all: clean_apps libed myapps



libed:\
	$(OBJ)/funcoes_fornecidas.o\
	$(OBJ)/leitura.o\
	$(OBJ)/entrada.o\
	$(OBJ)/busca.o\
	$(OBJ)/impressao.o\
	$(OBJ)/manipCab.o\
	$(OBJ)/manipBin.o\
	$(OBJ)/funcionalidades.o\



myapps: $(BIN)/main


$(OBJ)/%.o: $(SRC)/%.c $(INCLUDE)/%.h
	gcc -c $< -I $(INCLUDE) -o $@

$(BIN)/%: $(APPS)/%.c
	gcc $< $(OBJ)/*.o -I $(INCLUDE) -o $@

run:
	$(BIN)/main

clean:
	rm -rf $(BIN)/* $(OBJ)/*

clean_apps:
	rm -rf $(BIN)/*

