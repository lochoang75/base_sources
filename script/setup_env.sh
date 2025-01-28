#/bin/bash
DEPENDANCIES=()
# libreadline-dev
DEPENDANCIES+=( "libreadline-dev" )
# libncurses
DEPENDANCIES+=( "libncurses-dev" )

echo "Will install: ${DEPENDANCIES[@]}"
sudo apt-get install ${DEPENDANCIES[@]} -y