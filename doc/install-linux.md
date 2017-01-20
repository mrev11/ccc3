

# Linux Install


These steps were verified on Ubuntu Xenial 64-bit.

### Dependencies

You  have to install these packages:

    sudo apt-get install \
        git-core \
        g++ \
        libncurses5-dev \
        libncursesw5-dev \
        manpages-dev \
        glibc-doc \
        libx11-dev \
        libxft-dev \
        libssl-dev \
        libpcre3-dev \
        libreadline6-dev \
        libgtk2.0-dev \
        libpangox-1.0-dev



### CCC environment

Install this useful script into `$HOME/bin/addpath`:


     addpath()
     {
         X=$(echo :$PATH: | sed  s^:"$1":^:^)
         X="$1":$X
         X=$(echo $X | sed  s^::^:^)
         X=$(echo $X | sed  s^::^:^)
         export PATH=$X
     }
     pathadd()
     {
         X=$(echo :$PATH: | sed  s^:"$1":^:^)
         X=$X:"$1"
         X=$(echo $X | sed  s^::^:^)
         X=$(echo $X | sed  s^::^:^)
         export PATH=$X
     }
     addldpath()
     {
         X=$(echo :$LD_LIBRARY_PATH: | sed  s^:"$1":^:^)
         X="$1":$X
         X=$(echo $X | sed  s^::^:^)
         X=$(echo $X | sed  s^::^:^)
         export LD_LIBRARY_PATH=$X
     }
     
     
Add the following lines to your `.bashrc`:


    . $HOME/bin/addpath
    
    export OREF_SIZE=50000
    
    export CCCVER=3
    export CCCDIR=$HOME/ccc3
    export CCCBIN=lin
    export CCCUNAME=linux
    
    export CCCTERM_CONNECT="$CCCDIR/usr/bin/$CCCUNAME/terminal-xft.exe"
    export CCCTERM_XFTFONTSPEC=Monospace-11
    export CCCTERM_INHERIT=no
    export CCCTERM_SIZE=100x40
    
    addpath $CCCDIR/usr/bin/$CCCUNAME
    addpath ~/bin
    addpath .
    
    addldpath $CCCDIR/usr/lib/$CCCBIN
    


Now, if you start an xterm, then there will be a proper CCC environment in it.



### Cloning CCC sources

You execute this command in your home directory:

    git clone https://github.com/mrev11/ccc3.git
    
    
Now, the CCC source tree is extracted in `$HOME/ccc3`. 
This place will be referenced as `CCCDIR` (or `$CCCDIR`, if we read out the value
of the environment variable).



### Compiling CCC

Go into the `$CCCDIR` directory and execute the `i.b` script. 
This will compile the whole CCC. The process must be successful without
any error or warning. Otherwise you have to verify the 

  * fulfilment of dependencies,
    
  * the CCC environment.

From time to time, using the newer and newer C compilers, there may be new warnings,
which will be fixed during the regular maintenance of CCC.
   






