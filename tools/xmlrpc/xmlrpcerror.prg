
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

#ifdef NOT_DEFINED
apperror -> xmlrpcerror
apperror -> xmlrpcerror -> xmlrpctimeouterror
apperror -> xmlrpcerror -> xmlrpcsessionerror
apperror -> xmlrpcerror -> xmlrpcsessionerror -> xmlrpcinvalidsiderror
apperror -> xmlrpcerror -> xmlrpcsessionerror -> xmlrpcaccessdeniederror
#endif


******************************************************************************
class xmlrpcerror(apperror)
    method initialize

static function xmlrpcerror.initialize(this,op)
    this:(apperror)initialize(op)
    this:description:="xmlrpc error"
    this:subsystem:="XMLRPC"
    return this

******************************************************************************
class xmlrpctimeouterror(xmlrpcerror)
    method initialize

static function xmlrpctimeouterror.initialize(this,op)
    this:(xmlrpcerror)initialize(op)
    this:description:="timeout error"
    return this

******************************************************************************
class xmlrpcsessionerror(xmlrpcerror)
    method initialize

static function xmlrpcsessionerror.initialize(this,op)
    this:(xmlrpcerror)initialize(op)
    this:description:="session error"
    return this

******************************************************************************
class xmlrpcinvalidsiderror(xmlrpcsessionerror)
    method initialize

static function xmlrpcinvalidsiderror.initialize(this,op)
    this:(xmlrpcsessionerror)initialize(op)
    this:description:="invalid sid"
    return this

******************************************************************************
class xmlrpcaccessdeniederror(xmlrpcsessionerror)
    method initialize

static function xmlrpcaccessdeniederror.initialize(this,op)
    this:(xmlrpcsessionerror)initialize(op)
    this:description:="access denied"
    return this

******************************************************************************

