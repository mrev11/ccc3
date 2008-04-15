#!/bin/bash

cat >x.bak <<EOF
#!/bin/bash
# sudo-val kell indítani
# minimális CCC környezet a rootnak

export CCCDIR=/opt/ccc3
export CCCUNAME=linux
export CCCBIN=lin
export PATH=$CCCDIR/usr/bin/$CCCUNAME:$PATH
export LD_LIBRARY_PATH=$CCCDIR/usr/lib/$CCCBIN:$LD_LIBRARY_PATH

rm -f webcon.log
webcon.exe -l  80 -p 8080  >>webcon.log &
webcon.exe -l 443 -p 4433  -k cert/localhost.pem  -cp cert >>webcon.log &
EOF

chmod 755 x.bak
sudo ./x.bak &
rm x.bak

less webcon.log 

