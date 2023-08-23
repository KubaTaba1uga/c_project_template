#!/bin/bash
OS=$(hostnamectl | grep "Operating System")

case "$OS" in
    *"Debian GNU/Linux"*)
	sudo apt-get install valgrind
	;;
    *)
	echo "OS not supported"
	;;
    esac

