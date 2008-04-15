
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

#include <hashtable.h>

void hashtable_fill(hashtable *t){
t->add(L"Some like hot",L"\u041d\u0435\u0441\u043a\u043e\u043b\u044c\u043a\u043e \u043c\u0443\u0436\u0447\u0438\u043d \u043b\u044e\u0431\u044f\u0442 \u0433\u043e\u0440\u044f\u0447\u043e");
t->add(L"Gentlemen prefer blondes",L"\u0413\u043e\u0441\u043f\u043e\u0434\u0430 \u043b\u044e\u0431\u044f\u0442 \u043b\u0443\u0447\u0448\u0435 \u0431\u043b\u043e\u043d\u0434\u0438\u043d\u043e\u043a");
t->add(L"Star war",L"\u0412\u043e\u0439\u043d\u0430 \u044d\u0432\u0451\u044d\u0434");
}
