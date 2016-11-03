
    #@defines
	PREFIX = /usr
	BIN_DIR = $(PREFIX)/bin
	BASH_CDIR = /etc/bash_completion.d
	# set name
	NAME = nosuspend
	VER = 0.01
	# invoke build files
	OBJECTS = $(NAME).c
	BASHCOM = no_suspend

.PHONY : all clean install uninstall 

all : $(NAME)

clean :
	@rm -f $(NAME)
	@echo ". ., clean"

install : all 
	@mkdir -p $(DESTDIR)$(BIN_DIR)
	@mkdir -p $(DESTDIR)$(BASH_CDIR)
	@cp $(NAME) $(DESTDIR)$(BIN_DIR)
	@chmod  4755 $(DESTDIR)$(BIN_DIR)/$(NAME)
	@cp $(BASHCOM) $(BASH_CDIR)
	@echo ". ., installed"

uninstall :
	@rm -rf $(BIN_DIR)/$(NAME) 
	@rm -rf $(BASH_CDIR)/$(BASHCOM) 
	@echo ". ., uninstalled"

$(NAME) : $(OBJECTS)
	gcc $(OBJECTS) -o $(NAME)
