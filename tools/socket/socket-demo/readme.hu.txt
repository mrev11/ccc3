
1. Teszt (s1)

  elinditjuk recv0-et
  elinditjuk send0-et

  Recv0 letrehoz egy socketet, es amit ebbol olvas, azt echozza.
  Send0 kapcsolodik a socket-hez es kuldi a "Proba szerencse!" stringet.


2. Teszt (s2) 

  elinditjuk listener-t: listener.exe 45000 recv.exe
  elinditjuk send-et   : send.exe
  
  Listener letrehoz egy socketet, es ezen figyel (listen),
  ha egy kliens kapcsolodik a sockethez, akkor elindit egy 
  child processt (recv), ami orokli a kliens socketet,
  es a tovabbiakban a kliens a recv-vel all kapcsolatban,
  a listener lezarja a kliens socketet es uj kliensre var.
  
  Send a listener altal inditott recv-vel van kapcsolatban,
  ez nagybeture konvertalva visszakuldi a send altal kuldott 
  "Proba szerencse!" stringeket.


