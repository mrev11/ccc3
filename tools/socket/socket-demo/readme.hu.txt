
1. Teszt (s1)

  elindítjuk recv0-et
  elindítjuk send0-et

  Recv0 létrehoz egy socketet, és amit ebből olvas, azt echózza.
  Send0 kapcsolódik a socket-hez és küldi a "Próba szerencse!" stringet.


2. Teszt (s2) 

  elindítjuk listener-t: listener.exe 45000 recv.exe
  elindítjuk send-et   : send.exe
  
  Listener létrehoz egy socketet, és ezen figyel (listen),
  ha egy kliens kapcsolódik a sockethez, akkor elindít egy 
  child processt (recv), ami örökli a kliens socketet,
  és a továbbiakban a kliens a recv-vel áll kapcsolatban,
  a listener lezárja a kliens socketet és új kliensre vár.
  
  Send a listener által indított recv-vel van kapcsolatban,
  ez nagybetűre konvertálva visszaküldi a send által küldött 
  "Próba szerencse!" stringeket.


