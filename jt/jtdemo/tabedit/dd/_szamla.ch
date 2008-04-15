
/*
 *  CCC - The Clipper to C++ Compiler
 *  Copyright (C) 2005 ComFirm BT.
 *
 *  This library is free software; you can redistribute it and/or
 *  modify it under the terms of the GNU Lesser General Public
 *  License as published by the Free Software Foundation; either
 *  version 2 of the License, or (at your option) any later version.
 *
 *  This library is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 *  Lesser General Public License for more details.
 *
 *  You should have received a copy of the GNU Lesser General Public
 *  License along with this library; if not, write to the Free Software
 *  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */

#define SZAMLA             (TABLE:_szamla)

#ifdef ARROW
#define SZAMLA_SZAMLASZAM  szamla->szamlaszam  
#define SZAMLA_SZAMLAKOD   szamla->szamlakod   
#define SZAMLA_DEVNEM      szamla->devnem      
#define SZAMLA_NEV         szamla->nev         
#define SZAMLA_EGYENLEG    szamla->egyenleg    
#define SZAMLA_NYHITKERET  szamla->nyhitkeret  
#define SZAMLA_FHITKERET   szamla->fhitkeret   
#define SZAMLA_NAPITARTOZ  szamla->napitartoz  
#define SZAMLA_NAPIKOVET   szamla->napikovet   
#define SZAMLA_NYITDATUM   szamla->nyitdatum   
#define SZAMLA_EVNYITEGY   szamla->evnyitegy   
#define SZAMLA_YTMTART     szamla->ytmtart     
#define SZAMLA_YTMKOV      szamla->ytmkov      
#define SZAMLA_MTDTART     szamla->mtdtart     
#define SZAMLA_MTDKOV      szamla->mtdkov      
#define SZAMLA_FORWTART    szamla->forwtart    
#define SZAMLA_FORWKOV     szamla->forwkov     
#define SZAMLA_BLOKKEGYNL  szamla->blokkegynl  
#define SZAMLA_SORBEGYNL   szamla->sorbegynl   
#define SZAMLA_EVITETEL    szamla->evitetel    
#define SZAMLA_HAVITETEL   szamla->havitetel   
#define SZAMLA_TOROLTFLAG  szamla->toroltflag  
#define SZAMLA_ZAROLTFLAG  szamla->zaroltflag  
#define SZAMLA_TULMENFLAG  szamla->tulmenflag  
#define SZAMLA_TULMENDAT   szamla->tulmendat   
#define SZAMLA_ESZLAKAT    szamla->eszlakat    
#define SZAMLA_SZLAKAT     szamla->szlakat     
#define SZAMLA_EFOKSZAM    szamla->efokszam    
#define SZAMLA_FOKSZAM     szamla->fokszam     
#define SZAMLA_SZLATIPUS   szamla->szlatipus   
#define SZAMLA_KIVONAT     szamla->kivonat     
#define SZAMLA_BIZNYELV    szamla->biznyelv    
#define SZAMLA_KIVGYAK     szamla->kivgyak     
#define SZAMLA_KIVNAP      szamla->kivnap      
#define SZAMLA_KIVDATUM    szamla->kivdatum    
#define SZAMLA_HFSZINT     szamla->hfszint     
#define SZAMLA_LEKSZINT    szamla->lekszint    
#define SZAMLA_USER        szamla->user        
#define SZAMLA_CSOPORT     szamla->csoport     
#define SZAMLA_KONYVKELT   szamla->konyvkelt   
#define SZAMLA_UPDATE      szamla->update      
#define SZAMLA_ALCIM       szamla->alcim       
#else
#define SZAMLA_SZAMLASZAM  (FIELD:_szamla:1)
#define SZAMLA_SZAMLAKOD   (FIELD:_szamla:2)
#define SZAMLA_DEVNEM      (FIELD:_szamla:3)
#define SZAMLA_NEV         (FIELD:_szamla:4)
#define SZAMLA_EGYENLEG    (FIELD:_szamla:5)
#define SZAMLA_NYHITKERET  (FIELD:_szamla:6)
#define SZAMLA_FHITKERET   (FIELD:_szamla:7)
#define SZAMLA_NAPITARTOZ  (FIELD:_szamla:8)
#define SZAMLA_NAPIKOVET   (FIELD:_szamla:9)
#define SZAMLA_NYITDATUM   (FIELD:_szamla:10)
#define SZAMLA_EVNYITEGY   (FIELD:_szamla:11)
#define SZAMLA_YTMTART     (FIELD:_szamla:12)
#define SZAMLA_YTMKOV      (FIELD:_szamla:13)
#define SZAMLA_MTDTART     (FIELD:_szamla:14)
#define SZAMLA_MTDKOV      (FIELD:_szamla:15)
#define SZAMLA_FORWTART    (FIELD:_szamla:16)
#define SZAMLA_FORWKOV     (FIELD:_szamla:17)
#define SZAMLA_BLOKKEGYNL  (FIELD:_szamla:18)
#define SZAMLA_SORBEGYNL   (FIELD:_szamla:19)
#define SZAMLA_EVITETEL    (FIELD:_szamla:20)
#define SZAMLA_HAVITETEL   (FIELD:_szamla:21)
#define SZAMLA_TOROLTFLAG  (FIELD:_szamla:22)
#define SZAMLA_ZAROLTFLAG  (FIELD:_szamla:23)
#define SZAMLA_TULMENFLAG  (FIELD:_szamla:24)
#define SZAMLA_TULMENDAT   (FIELD:_szamla:25)
#define SZAMLA_ESZLAKAT    (FIELD:_szamla:26)
#define SZAMLA_SZLAKAT     (FIELD:_szamla:27)
#define SZAMLA_EFOKSZAM    (FIELD:_szamla:28)
#define SZAMLA_FOKSZAM     (FIELD:_szamla:29)
#define SZAMLA_SZLATIPUS   (FIELD:_szamla:30)
#define SZAMLA_KIVONAT     (FIELD:_szamla:31)
#define SZAMLA_BIZNYELV    (FIELD:_szamla:32)
#define SZAMLA_KIVGYAK     (FIELD:_szamla:33)
#define SZAMLA_KIVNAP      (FIELD:_szamla:34)
#define SZAMLA_KIVDATUM    (FIELD:_szamla:35)
#define SZAMLA_HFSZINT     (FIELD:_szamla:36)
#define SZAMLA_LEKSZINT    (FIELD:_szamla:37)
#define SZAMLA_USER        (FIELD:_szamla:38)
#define SZAMLA_CSOPORT     (FIELD:_szamla:39)
#define SZAMLA_KONYVKELT   (FIELD:_szamla:40)
#define SZAMLA_UPDATE      (FIELD:_szamla:41)
#define SZAMLA_ALCIM       (FIELD:_szamla:42)
#endif

