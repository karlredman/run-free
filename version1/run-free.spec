#
# Spec file for Veraserv product
#
Name: run-free
Summary: GUI (gtk) commandline style program launcher
Version: 1.0.0
Release: 1
Copyright: GNU Public License
Group: Applications/GUI
Source: run-free-1.0.0.tar.gz

Vendor: Parasyte of Knowledge
Packager: parasyte@enteract.com

%description
GUI (gtk) commandline style program launcher

arch_compat: i386: i486: i586
os_compat: Linux

##########################
%prep
%setup

%build
./configure
make

%install
make install

#####################
%ifos linux

%files 
/usr/local/bin/run-free
/usr/local/bin/run-free-kbhit
%endif
