Updated 08/06/2016 14:09 
Version 1:00:00 

Install Linux Mint 
Then run the following items into the build 
    sudo apt-get update 
    sudo apt-get upgrade
    sudo apt-get install g++ -y 
    sudo apt-get install mysql-server -y
    sudo apt-get install git -y
    sudo apt-get install libsdl2-dev -y
    sudo apt-get install libsdl2-gfx-dev -y 
    sudo apt-get install libsdl2-image-dev -y 
    sudo apt-get install libsdl2-mixer-dev -y 
    sudo apt-get install libsdl2-net-dev -y 
    sudo apt-get install libsdl2-ttf-dev -y     
    sudo apt-get install libcppunit-dev -y
    sudo apt-get install libmysqlcppconn-dev -y
    sudo apt-get install libncurses5-dev -y
    sudo apt-get install libmysqlclient-dev -y 
    sudo apt-get install libboost-all-dev -y
    sudo apt-get install cmake -y
    sudo apt-get install flex -y
    sudo apt-get install bison -y 
    sudo apt-get build-essential  -y 

configure the set up using 
    git config --global user.name "Denis Jackman"
    git config --global user.email "Denis_jackman@hotmail.com"
    git config --global push.default simple
    git config --global http.sslVerify false

set up a development folder 
    mkdir development 
    cd development 
    git clone https://github.com/angband/angband.git
    git clone https://github.com/denisjackman/game.git
    git clone https://gitlab.com/0ad/0ad.git
    git clone https://github.com/CleverRaven/Cataclysm-DDA
    git clone http://git.code.sf.net/p/nethack/NetHack
    
    
Mac Setup:
    This is slightly different and needs more documentation
    for each of the libraries needed download the source 
        libsdl2-dev
        libsdl2-image-dev 
        libsdl2-mixer-dev 
        libsdl2-ttf-dev         
        libsdl2-gfx-dev 
        libsdl2-net-dev 
    Download the source for each of them.
    Unpack the source 
    Navigate to the directory you unzipped it into 
        ./configure 
        make 
        make install 
    
CPATH
C_INCLUDE_PATH
CPLUS_INCLUDE_PATH
OBJC_INCLUDE_PATH
    
    Once this is done the headers and libraries will be in the standard Linux locations 
    and can be picked up 