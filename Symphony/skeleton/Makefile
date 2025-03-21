# Variables
SSH_DIR=$(PWD)/.ssh
GIT_DIR=$(PWD)/.git
SSH_KEY=$(SSH_DIR)/it_akademy_rsa
GIT_CONFIG=$(GIT_DIR)/config

include .env

# Recettes
.PHONY: install ssh_dir git_dir ssh_key git_config

install: ssh_dir git_dir ssh_key git_config

ssh_dir:
	mkdir -p $(SSH_DIR)

git_dir:
	mkdir -p $(GIT_DIR)

ssh_key: ssh_dir
	ssh-keygen -q -f $(SSH_KEY) -N ""

git_config: git_dir
	echo -e "[user]\n\tname = $(USER_NAME)\n\temail = $(USER_EMAIL)\n[core]\n\tsshCommand = \"ssh -i $(SSH_KEY)\"" > $(GIT_CONFIG)