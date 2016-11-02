
    #@defines
	PREFIX = /usr
	BIN_DIR = $(PREFIX)/bin
	# set name
	NAME = nosuspend
	VER = 0.01
	# invoke build files
	OBJECTS = $(NAME).c

.PHONY : all clean install uninstall 

all : $(NAME)

clean :
	@rm -f $(NAME)
	@echo ". ., clean"

install : all 
	@mkdir -p $(DESTDIR)$(BIN_DIR)
	@cp $(NAME) $(DESTDIR)$(BIN_DIR)
	@chmod  4755 $(DESTDIR)$(BIN_DIR)/$(NAME)
	@echo ". ., installed"

uninstall :
	rm -rf $(BIN_DIR)/$(NAME) 
	@echo ". ., uninstalled"

$(NAME) : 
	gcc $(OBJECTS) -o $(NAME)
