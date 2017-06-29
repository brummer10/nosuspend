
    #@defines
	PREFIX = /usr
	BIN_DIR = $(PREFIX)/bin
	BASH_CDIR = /etc/bash_completion.d
	POLICY_DIR = $(PREFIX)/share/polkit-1/actions
	# set name
	NAME = nosuspend
	VER = 0.01
	# invoke build files
	OBJECTS = $(NAME).c
	BASHCOM = no_suspend
	POLICY = com.ubuntu.pkexec.inhibit.policy
	POLICY_SECURE = com.ubuntu.pkexec.inhibit.policy.secure
	POLICY_RELAXED = com.ubuntu.pkexec.inhibit.policy.relaxed

.PHONY : all clean install uninstall 

all : config.h $(NAME)
ifeq (,$(wildcard $(POLICY)))
	@cp $(POLICY_SECURE) $(POLICY)
endif

relaxed : all
	@cp $(POLICY_RELAXED) $(POLICY)

secure : all
	@cp $(POLICY_SECURE) $(POLICY)

config.h : 
	@echo '#define VERSION  "$(VER)"' > config.h 

clean :
	@rm -f $(NAME)
	@rm -f $(POLICY)
	@echo ". ., clean"

install : all 
	@mkdir -p $(DESTDIR)$(BIN_DIR)
	@mkdir -p $(DESTDIR)$(BASH_CDIR)
	@cp $(NAME) $(DESTDIR)$(BIN_DIR)
	@cp $(BASHCOM) $(BASH_CDIR)
	@cp $(POLICY) $(POLICY_DIR)
	@echo ". ., installed"

uninstall :
	@rm -rf $(BIN_DIR)/$(NAME)
	@rm -rf $(BASH_CDIR)/$(BASHCOM)
	@rm -rf $(POLICY_DIR)/$(POLICY)
	@echo ". ., uninstalled"

$(NAME) : $(OBJECTS)
	gcc $(OBJECTS) -o $(NAME)
