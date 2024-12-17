.PHONY: all build run clean test

OUTPUTDIRECTORY = out
BUILDDIRECTORY = build
EXECUTABLEFILE = main

ATOMTEST = atomtests
NEGATIONTEST = negationtests

all: build run

build: src/main.cpp
	@echo "\n===BUILDING==="
	@mkdir -p $(BUILDDIRECTORY)
	@mkdir -p $(OUTPUTDIRECTORY)
	@cd ${BUILDDIRECTORY} && cmake .. && make --no-print-directory

run:
	@echo "\n===RUNNING==="
	@./$(OUTPUTDIRECTORY)/$(EXECUTABLEFILE)
	@echo "\n"

test:
	@echo "\n=====TEST====="
	@./$(OUTPUTDIRECTORY)/$(ATOMTEST)
	
clean:
	@echo "\n=====CLEAN====="
	@rm -rf $(BUILDDIRECTORY)
	@rm -rf $(OUTPUTDIRECTORY)