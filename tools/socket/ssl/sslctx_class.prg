
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

******************************************************************************
class sslctx(object)
    attrib  handle
    attrib  handshake_timeout

    method  initialize  
    method  free  
    method  use_certificate_file
    method  use_certificate_chain_file
    method  use_privatekey_file
    method  check_private_key
    method  set_verify
    method  verify_mode                 //set-get
    method  set_verify_depth
    method  verify_depth                //set-get
    method  load_verify_locations
    method  load_client_ca_file

    //session cache handling
    method  set_session_id_context
    method  quiet_shutdown              //set-get
    method  session_cache_mode          //set-get
    method  session_cache_timeout       //set-get
    method  session_cache_size          //set-get  (0=unlimited!)
    method  flush_sessions
    method  session_number

******************************************************************************
static function sslctx.initialize(this,met)
local err
    this:handle:=sslctx_new(met)
    if( this:handle==NIL )
        err:=sslctxerrorNew("sslctx.initialize")
        break(err)
    end

    //vagy meg kell adni a session_id_context-et
    //vagy ki kell kapcsolni a session cache-t
    this:set_session_id_context("SESSIONID"+alltrim(str(getpid())))

    this:handshake_timeout:=10000  //10 sec
   
    return this

******************************************************************************
static function sslctx.free(this)
    if( this:handle!=NIL )
        sslctx_free(this:handle)
        this:handle:=NIL
    end

******************************************************************************
static function sslctx.use_certificate_file(this,fspec)
local retcode,err
    retcode:=sslctx_use_certificate_file(this:handle,fspec)
    if( retcode==0 )
        err:=sslctxerrorNew("sslctx.use_certificate_file")
        err:filename:=fspec
        break(err)
    end

******************************************************************************
static function sslctx.use_certificate_chain_file(this,fspec)
local retcode,err
    retcode:=sslctx_use_certificate_chain_file(this:handle,fspec)
    if( retcode==0 )
        err:=sslctxerrorNew("sslctx.use_certificate_chain_file")
        err:filename:=fspec
        break(err)
    end

******************************************************************************
static function sslctx.use_privatekey_file(this,fspec)
local retcode,err
    retcode:=sslctx_use_privatekey_file(this:handle,fspec)
    if( retcode==0 )
        err:=sslctxerrorNew("sslctx.use_privatekey_file")
        err:filename:=fspec
        break(err)
    end

******************************************************************************
static function sslctx.check_private_key(this)
local retcode,err
    retcode:=sslctx_check_private_key(this:handle)
    if( retcode==0 )
        err:=sslctxerrorNew("sslctx.check_private_key")
        break(err)
    end

******************************************************************************
static function sslctx.set_verify(this,mode)
    sslctx_set_verify(this:handle,mode)

******************************************************************************
static function sslctx.verify_mode(this,mode) //set-get
    if( mode==NIL )
        mode:=sslctx_get_verify_mode(this:handle)
    else
        sslctx_set_verify(this:handle,mode)
    end
    return mode

******************************************************************************
static function sslctx.set_verify_depth(this,depth)
    sslctx_set_verify_depth(this:handle,depth)

******************************************************************************
static function sslctx.verify_depth(this,depth) //set-get
    if( depth==NIL )
        depth:=sslctx_get_verify_depth(this:handle)
    else
        sslctx_set_verify_depth(this:handle,depth)
    end
    return depth

******************************************************************************
static function sslctx.load_verify_locations(this,cafile,capath)
local retcode,err
    retcode:=sslctx_load_verify_locations(this:handle,cafile,capath)
    if( retcode!=1 )
        err:=sslctxerrorNew("sslctx.load_verify_locations")
        break(err)
    end

******************************************************************************
static function sslctx.load_client_ca_file(this,cafile)
local retcode,err
    retcode:=sslctx_load_client_ca_file(this:handle,cafile)
    if( retcode!=1 )
        err:=sslctxerrorNew("sslctx.load_client_ca_file")
        break(err)
    end
    
******************************************************************************
//session cache handling
******************************************************************************
static function sslctx.set_session_id_context(this,sidctx)
local err,retcode
    retcode:=sslctx_set_session_id_context(this:handle,sidctx)
    if( retcode!=1 )
        err:=sslctxerrorNew("sslctx.set_session_id_context")
        break(err)
    end

// ha ez nincs megadva, es a session cache sincs kikapcsolva,
// akkor cache-ben levo session-okre nem mukodik a connect,
// ezt elkerulendo, az initialize beallit egy nemures defaultot

******************************************************************************
static function sslctx.quiet_shutdown(this,flag) //set-get
    if( flag==NIL )
        flag:=sslctx_get_quiet_shutdown(this:handle)
    else
        sslctx_set_quiet_shutdown(this:handle,flag)
    end
    return flag

// ezt beallitva shutdown nem kuldi a "close notify" uzenetet

******************************************************************************
static function sslctx.session_cache_mode(this,mode) //set-get
    if( mode==NIL )
        mode:=sslctx_get_session_cache_mode(this:handle)
    else
        sslctx_set_session_cache_mode(this:handle,mode)
    end
    return mode
    
// mode=SSL_SESS_CACHE_OFF     session cache kikapcsolva
// mode=SSL_SESS_CACHE_SERVER  szerver oldali cache bekapcsolva (default)   

******************************************************************************
static function sslctx.session_cache_timeout(this,timeout) //set-get
    if( timeout==NIL )
        timeout:=sslctx_get_timeout(this:handle)
    else
        sslctx_set_timeout(this:handle,timeout) //prev
    end
    return timeout

// ennyi masodperc alatt jar le egy session ervenyessege

******************************************************************************
static function sslctx.session_cache_size(this,size) //set-get
    if( size==NIL )
        size:=sslctx_sess_get_cache_size(this:handle)
    else
        sslctx_sess_set_cache_size(this:handle,size) //prev
    end
    return size

// ennyi darab session fer bele a cache-be

******************************************************************************
static function sslctx.flush_sessions(this)
    sslctx_flush_sessions(this:handle)

// torli a cache-bol a lejart sesssion-oket
// magatol csak minden 256-dik alkalommal takarit

******************************************************************************
static function sslctx.session_number(this)
    return sslctx_sess_number(this:handle)

// pillanatnyilag ennyi session van a cache-ben

******************************************************************************
    
