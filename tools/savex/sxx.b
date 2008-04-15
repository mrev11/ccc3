#!/bin/bash

export DIFF=~/.temp/diff_ignorespace

echo '#!/bin/bash' >$DIFF
#echo 'diff -E -b "$@"' >>$DIFF
echo 'diff -w "$@"' >>$DIFF                 #ignore all white spaces

chmod 755 $DIFF

savex.exe "$@"
