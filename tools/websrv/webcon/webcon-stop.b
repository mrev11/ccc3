#!/bin/bash

cat >x.bak <<EOF
#!/bin/bash
ps -A | grep webcon.exe | awk '{print \$1}' | while read PID; do
    #echo \$PID
    kill \$PID
done
EOF

chmod 755 x.bak
sudo ./x.bak
rm x.bak

./webcon-list.b
