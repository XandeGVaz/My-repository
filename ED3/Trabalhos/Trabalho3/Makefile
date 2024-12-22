APPS = ./apps
BIN = ./bin
INCLUDE = ./include
OBJ = ./obj
OBJPP = ./objpp
GRFPP = ./objpp
SRC = ./src

all: clean libed myapps


libed:\
	$(OBJ)/funcoes_fornecidas.o\
	$(OBJ)/impressao.o\
	$(OBJ)/leitura.o\
	$(OBJPP)/elemento.o\
	$(OBJPP)/vertice.o\
	$(OBJPP)/grafoGeral.o\
	$(OBJPP)/grafoMinCaminhos.o\
	$(OBJPP)/grafoCiclo.o\
	$(OBJPP)/grafoConec.o\
	$(OBJPP)/funcionalidades.o\

myapps: $(BIN)/main


$(OBJ)/%.o: $(SRC)/%.c $(INCLUDE)/%.h
	g++ -c $< -I $(INCLUDE) -o $@

$(OBJPP)/%.o: $(SRC)/%.cpp $(INCLUDE)/%.hpp
	g++ -c $< -I $(INCLUDE) -o $@

$(BIN)/%: $(APPS)/%.cpp $(OBJ)/*.o $(OBJPP)/*.o
	g++ $< $(OBJ)/*.o $(OBJPP)/*.o -I $(INCLUDE) -o $@

run:
	$(BIN)/main

clean:
	rm -rf $(BIN)/* $(OBJ)/* $(OBJPP)/*

clean_apps:
	rm -rf $(BIN)/*

