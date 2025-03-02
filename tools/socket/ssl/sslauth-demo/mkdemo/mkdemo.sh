#!/bin/bash

rm -f *.pem
rm -f ../pem_client/*.pem
rm -f ../pem_server/*.pem

sscert server1 ca       # onalairt CA cert
sscert server2          # onalairt cert
sscert clientss         # onalairt cert
sscert client           # onalairt cert

sign client server1     # client-cert-et alairja server1.pem-mel (felulirodik a korabbi)

mv  server*.pem  ../pem_server/
mv  client*.pem  ../pem_client/

cp  ../pem_server/server2-cert.pem   ../pem_client/  # szerver hitelesiteshez
cp  ../pem_client/clientss-cert.pem  ../pem_server/  # kliens  hitelesiteshez




# server-nek van 2 cert-je
#   server1.pem: a kliens certek alairasara es hitelesitesere (CA extension)
#   server2.pem: titkositashoz, onmaga hitelesitesehez
# plusz
#   clientss-cert.pem, amivel ellenorzi client-et


# client-nek van 2 cert-je
#   client.pem   : server1.pem-mel alairt cert
#   clientss.pem : self-signed cert
# plusz
#   server2-cert.pem, amivel ellenorzi server-t

