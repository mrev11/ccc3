#!/bin/bash

#set -x

#heredoc
cat << 'EOF' > ./clean.bak
#!/bin/bash
for DIR in "$@"; do
    rm -rf $DIR
done
EOF
chmod +x ./clean.bak


#symlinkeket kihagyja

find . -type d \
       -name ppo -o \
       -name objfre -o \
       -name objlin | xargs  ./clean.bak


find . -type f \
       -name outerr -o \
       -name outcpp -o \
       -name outlnk -o \
       -name outpre -o \
       -name outlemon -o \
       -name outflex -o \
       -name compopt -o \
       -name rsplink -o \
       -name rsplink -o \
       -name 'log-*' -o \
       -name 'err-*' -o \
       -name '*.lib' -o \
       -name '*.a' -o \
       -name '*.exe' -o \
       -name '*.class' -o \
       -name '*.jar' -o \
       -name '*.bak' -o \
       -name '*~' -o \
       -name dectext -o \
       -name enctext -o \
       -name signature -o \
       -name error | xargs  rm -f


rm -f clean.bak
