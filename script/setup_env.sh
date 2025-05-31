#/bin/bash
DEPENDANCIES=()
# libreadline-dev
DEPENDANCIES+=( "libreadline-dev" )
# libncurses
DEPENDANCIES+=( "libncurses-dev" )
# pkg-config
DEPENDANCIES+=( "pkg-config" )
# libsystemd-dev
DEPENDANCIES+=( "libsystemd-dev" )

echo "Will install: ${DEPENDANCIES[@]}"
sudo apt-get install ${DEPENDANCIES[@]} -y