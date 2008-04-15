
1. Teszt (s1)

  elindítjuk recv0-et
  elindítjuk send0-et

  Recv0 létrehoz egy socketet, és amit ebből olvas, azt echózza.
  Send0 kapcsolódik a socket-hez és küldi a "Próba szerencse!" stringet.


2. Teszt (s2) 

  elindítjuk listener-t: listener.exe 45000 recv.exe
  elindítjuk send-et   : send.exe
  
  Listener létrehoz egy socketet, és ezen hallgatózik,
  ha egy kliens kapcsolódik a sockethez, akkor elindít egy 
  child processt (recv), ami örökli a kliens socketet,
  és a továbbiakban a kliens a recv-vel áll kapcsolatban,
  a listener lezár minden socketet és új kliensre vár.
  
  Send a listener által indított recv-vel van kapcsolatban,
  ez nagybetűre konvertálva visszaküldi a send által küldött 
  "Próba szerencse!" stringeket.


  Megjegyzés: 
  
  Ugyanez a teszt nem megy listener helyett a remstart-tal,
  ui. a remstart az indított program stdin/stdout-ját átirányítja
  a socketba, így a recv konzol kimenete belekeveredik a 
  kommunikációba, és elrontja az smessage protokollt.
  