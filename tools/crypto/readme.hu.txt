Windowson installálni kell a Win32OpenSSL csomagot,
az installálásból keletkezik egy C:\OpenSSL directory.

Innen - a szokásos módon - az include\openssh directoryt, és 
a lib\MinGW és/vagy lib\VC directoryk tartalmát át kell másolni 
a compiler megfelelő helyére. 

MinGW:

    Az .a kiterjesztésű könyvtárakat .lib kiterjesztéssel is 
    létre kell hozni.

VC:
    A libeay32MT.lib és ssleay32MT.lib filéket az MT toldalék
    nélkül kell átmásolni.
