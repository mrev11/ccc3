set -x

db2 uncatalog database i3x_samp
db2 catalog database sample as  i3x_samp  at node db2p1 authentication client
db2 list db directory


