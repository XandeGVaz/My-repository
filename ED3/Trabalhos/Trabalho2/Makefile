APPS = ./apps
BIN = ./bin
INCLUDE = ./include
OBJ = ./obj
SRC = ./src

all: clean libed myapps



libed:\
	$(OBJ)/funcoes_fornecidas.o\
	$(OBJ)/funcionalidades.o\
	$(OBJ)/busca.o\
	$(OBJ)/entrada.o\
	$(OBJ)/impressao.o\
	$(OBJ)/manipCab.o\
	$(OBJ)/manipBin.o\
	$(OBJ)/manipArvB.o\
	$(OBJ)/leitura.o\



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

