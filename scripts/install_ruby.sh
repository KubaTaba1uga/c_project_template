#!/bin/bash
OS=$(hostnamectl | grep "Operating System")

case "$OS" in
    *"Debian GNU/Linux"*)
	sudo apt update
	sudo apt install ruby-full
	echo "alias bundle='bundle3.1'" > ~/.bashrc
	;;
    *)
	echo "OS not supported"
	;;
    esac

