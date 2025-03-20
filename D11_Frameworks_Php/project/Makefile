# env vars
include .env
-include .env.local   # don't crash if not defined

# variables
WALLET_DIR = .wallet
SSH_KEY = $(WALLET_DIR)/id_rsa

# mandatory installed packages
GLOBAL_PACKAGES := git docker ssh-keygen

# commands
docker := ./bin/docker

# check mandatory packages
check-packages:
	@for cmd in $(GLOBAL_PACKAGES); do \
		if ! command -v $$cmd >/dev/null 2>&1; then \
			echo "ERREUR : La commande '$$cmd' n'est pas installée ou introuvable dans le PATH."; \
			exit 1; \
		else \
			echo "OK : '$$cmd' est installé."; \
		fi; \
	done

# prepare git local scripts
local_git:
	@LOCAL_EMAIL="$$(git config --local user.email 2>/dev/null || true)"; \
	if [ -z "$$LOCAL_EMAIL" ]; then \
	  CURRENT_GIT_EMAIL="$$(git config --global user.email 2>/dev/null || true)"; \
	  read -p "Entrez votre email pour ce projet [$$CURRENT_GIT_EMAIL]: " EMAIL; \
	  EMAIL="$${EMAIL:-$$CURRENT_GIT_EMAIL}"; \
	  git config --local user.email "$$EMAIL"; \
	  LOCAL_EMAIL="$$EMAIL"; \
	fi; \
	echo "OK : email Git : $$LOCAL_EMAIL."


.wallet:
	mkdir .wallet
	ssh-keygen -t rsa -b 4096 -f .wallet/id_rsa

.env.local:
	-cp .env.local.dist .env.local
	touch .env.local

build:
	$(docker) build

install: check-packages local_git .wallet .env.local build
	$(docker) exec php composer install
	$(docker) exec php bin/console ca:cl

run:
	$(docker) up -d


# create-wallet:
# 	@if [ ! -d "$(WALLET_DIR)" ]; then \
# 		mkdir -p $(WALLET_DIR); \
# 		echo "Dossier .wallet créé."; \
# 	else \
# 		echo "Le dossier .wallet existe déjà."; \
# 	fi
# 	@if [ ! -f "$(SSH_KEY)" ]; then \
# 		ssh-keygen -t rsa -b 4096 -f $(SSH_KEY) -N "" -q; \
# 		echo "Clé SSH créée dans $(SSH_KEY)."; \
# 	else \
# 		echo "La clé SSH existe déjà dans $(SSH_KEY)."; \
# 	fi

# generate-ssh-key:
# 	mkdir -p ~/.ssh
# 	ssh-keygen -t rsa -b 4096 -f ~/.ssh/id_rsa_deploy -N "" -C "deploy_key"
# 	@echo "Clé SSH générée à ~/.ssh/id_rsa_deploy"

# setup-env:
# 	cp .env.example .env.local
# 	@echo "Modifiez .env.local avec vos configurations."

# deploy:
# 	./scripts/deploy.sh $(ENV) $(DOMAIN)

# test:
# 	@echo "test"

# compile:
# 	php bin/console asset-map:compile
