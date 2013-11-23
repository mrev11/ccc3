
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

#ifndef _CCCEXT2_H_
#define _CCCEXT2_H_

//base64.obj:
extern void _clp_base64_encode(int);
extern void _clp_base64_decode(int);

//chmod.obj:
extern void _clp_chmod(int);
extern void _clp_fchmod(int);

//power.obj:
extern void _clp_exp(int);
extern void _clp_log(int);
extern void _clp_sqrt(int);

//day.obj:
extern void _clp_month(int);
extern void _clp_cmonth(int);
extern void _clp__date_emptycharvalue(int);
extern void _clp__date_templatestring(int);
extern void _clp_day(int);
extern void _clp_dow(int);
extern void _clp_cdow(int);
extern void _clp_ctod(int);
extern void _clp_dtoc(int);
extern void _clp_year(int);

//o_error.obj:
extern void _clp_errorini(int);
extern void _clp_errornew(int);
extern void _clp_errorclass(int);

//gettick.obj:
extern void _clp_gettickcount(int);

//arr2bin.obj:
extern void _clp_any2str(int);
extern void _clp_arr2bin(int);
extern void _clp_arr2str(int);
extern void _clp_bin2arr(int);

//qout.obj:
//extern void _clp_print(int);
extern void _clp_qqout(int);
extern void _clp_fflush(int);
extern void _clp_outerr(int);
extern void _clp_outstd(int);
extern void _clp___eject(int);
extern void _clp___extra(int);
extern void _clp_setextra(int);
extern void _clp___printer(int);
extern void _clp_setconsole(int);
extern void _clp_setprinter(int);
extern void _clp___alternate(int);
extern void _clp_setalternate(int);
extern void _clp_qout(int);

//rat.obj:
extern void _clp_rat(int);

//color.obj:
extern void _clp___clr2num(int);

//o_object.obj:
extern void _clp_objectini(int);
extern void _clp_objectclass(int);

//random.obj:
extern void _clp_random(int);

//month.obj:
extern void _clp_addmonth(int);
extern void _clp_lastdayom(int);

//transform.obj:
extern void _clp_transform(int);

//trim.obj:
extern void _clp_ltrim(int);
extern void _clp_rtrim(int);
extern void _clp_alltrim(int);
extern void _clp_trim(int);

//evalarr.obj:
extern void _clp_evalarray(int);

//break.obj:
extern void _clp_break0(int);
extern void _clp_break(int);

//binary.obj:
extern void _clp___maxbinlen(int);

//doy.obj:
extern void _clp_bom(int);
extern void _clp_boy(int);
extern void _clp_doy(int);
extern void _clp_eom(int);
extern void _clp_eoy(int);

//tempfile.obj:
extern void _clp_tempfile(int);

//i2bin.obj:
extern void _clp_bin2f(int);
extern void _clp_bin2i(int);
extern void _clp_bin2l(int);
extern void _clp_bin2w(int);
extern void _clp_f2bin(int);
extern void _clp_hex2l(int);
extern void _clp_i2bin(int);
extern void _clp_l2bin(int);
extern void _clp_l2hex(int);
extern void _clp_l2oct(int);
extern void _clp_oct2l(int);

//timeval.obj:
extern void _clp_timevalid(int);

//set.obj:
extern void _clp_setcolor(int);
extern void _clp_setinsert(int);
extern void _clp_setaltfile(int);
extern void _clp_setconfirm(int);
extern void _clp_setdosconv(int);
extern void _clp___setcentury(int);
extern void _clp_setextrafile(int);
extern void _clp_setprintfile(int);
extern void _clp_setdateformat(int);
extern void _clp_set(int);

//ascpos.obj:
extern void _clp_ascpos(int);

//sleep.obj:
extern void _clp_sleep(int);

//run.obj:
extern void _clp___run(int);
extern void _clp_run(int);

//max.obj:
extern void _clp_max(int);
extern void _clp_min(int);

//hashcode.obj:
extern void _clp_hashcode(int);

//file.obj:
extern void _clp_ferase(int);
extern void _clp_frename(int);
extern void _clp_filemove(int);
extern void _clp_deletefile(int);
extern void _clp_file(int);

//isalpha.obj:
extern void _clp_isalnum(int);
extern void _clp_isalpha(int);
extern void _clp_iscntrl(int);
extern void _clp_isdigit(int);
extern void _clp_islower(int);
extern void _clp_isupper(int);
extern void _clp_isxdigit(int);

//string.obj:
extern void _clp___maxstrlen(int);

//object.obj:
extern void _clp_objectnew(int);
extern void _clp_getclassid(int);
extern void _clp_setclassid(int);
extern void _clp_getobjectasarray(int);
extern void _clp_iniobjectfromarray(int);

//fileio.obj:
extern void _clp_fread(int);
extern void _clp_fclose(int);
extern void _clp_ferror(int);
extern void _clp_fwrite(int);

//at.obj:
extern void _clp_at(int);

//str.obj:
extern void _clp_str(int);

//deferror.obj:
extern void _clp_quitblock(int);
extern void _clp_errorblock(int);
extern void _clp_breakblock(int);
extern void _clp_signalblock(int);

//rand.obj:
extern void _clp_rand(int);

//replicate.obj:
extern void _clp_space(int);
extern void _clp_replicate(int);

//stuff.obj:
extern void _clp_stuff(int);

//array.obj:
extern void _clp_array(int);
extern void _clp_asize(int);
extern void _clp_asort(int);
extern void _clp_aclone(int);
extern void _clp_aadd(int);
extern void _clp_adel(int);
extern void _clp_ains(int);

//eval.obj:
extern void _clp_eval(int);

//upper.obj:
extern void _clp_lower(int);
extern void _clp_upper(int);

//direct.obj:
extern void _clp_curdir(int);
extern void _clp_dirmake(int);
extern void _clp_dirname(int);
extern void _clp_diskname(int);
extern void _clp_dirchange(int);
extern void _clp_dirremove(int);
extern void _clp_diskchange(int);

//errorcode.obj:
extern void _clp_errorcode(int);

//setsignal.obj:
extern void _clp_setsignal(int);

//syserror.obj:
extern void _clp_ioerrornew(int);
extern void _clp_apperrornew(int);
extern void _clp_eoferrornew(int);
extern void _clp_fnferrornew(int);
extern void _clp_ioerrorclass(int);
extern void _clp_memoerrornew(int);
extern void _clp_readerrornew(int);
extern void _clp_apperrorclass(int);
extern void _clp_eoferrorclass(int);
extern void _clp_fnferrorclass(int);
extern void _clp_writeerrornew(int);
extern void _clp_memoerrorclass(int);
extern void _clp_readerrorclass(int);
extern void _clp_socketerrornew(int);
extern void _clp_tabobjerrornew(int);
extern void _clp_xmltagerrornew(int);
extern void _clp_tranlogerrornew(int);
extern void _clp_writeerrorclass(int);
extern void _clp_socketerrorclass(int);
extern void _clp_tabindexerrornew(int);
extern void _clp_tabobjerrorclass(int);
extern void _clp_xmltagerrorclass(int);
extern void _clp_tabstructerrornew(int);
extern void _clp_tranlogerrorclass(int);
extern void _clp_xmlsyntaxerrornew(int);
extern void _clp_tabindexerrorclass(int);
extern void _clp_tabstructerrorclass(int);
extern void _clp_xmlsyntaxerrorclass(int);
extern void _clp_invalidformaterrornew(int);
extern void _clp_invalidoptionerrornew(int);
extern void _clp_invalidstructerrornew(int);
extern void _clp_invalidformaterrorclass(int);
extern void _clp_invalidoptionerrorclass(int);
extern void _clp_invalidstructerrorclass(int);

//add.obj:
extern void _clp_abs(int);
extern void _clp_mod(int);

//dirsep.obj:
extern void _clp_dirsep(int);
extern void _clp_pathsep(int);
extern void _clp_fullmask(int);
extern void _clp_endofline(int);
extern void _clp_crlf(int);

//stvar.obj:

//val.obj:
extern void _clp_val(int);

//argv.obj:
extern void _clp_argc(int);
extern void _clp_argv(int);

//fileconv.obj:
extern void _clp_get_dosconv(int);
extern void _clp_set_dosconv(int);
extern void _clp_reset_dosconv(int);
extern void _clp_convertfspec2nativeformat(int);

//empty.obj:
extern void _clp_empty(int);
extern void _clp_len(int);

//ctime.obj:
extern void _clp_ctime(int);

//str2bin.obj:
extern void _clp_bin2str(int);
extern void _clp_str2bin(int);

//strtran.obj:
extern void _clp_strtran(int);

//stat.obj:
extern void _clp_fstat(int);
extern void _clp_lstat(int);
extern void _clp_s_isblk(int);
extern void _clp_s_ischr(int);
extern void _clp_s_isdir(int);
extern void _clp_s_islnk(int);
extern void _clp_s_isreg(int);
extern void _clp_s_isfifo(int);
extern void _clp_s_issock(int);
extern void _clp_stat_st_mode(int);
extern void _clp_fstat_st_mode(int);
extern void _clp_lstat_st_mode(int);
extern void _clp_stat(int);

//fileseek.obj:
extern void _clp_fileattr(int);
extern void _clp_filedate(int);
extern void _clp_fileseek(int);
extern void _clp_filesize(int);
extern void _clp_filetime(int);
extern void _clp_restfseek(int);
extern void _clp_savefseek(int);
extern void _clp_filedelete(int);

//class.obj:
extern void _clp_classname(int);
extern void _clp_getmethod(int);
extern void _clp___findslot(int);
extern void _clp_classattrib(int);
extern void _clp_classbaseid(int);
extern void _clp_classmethod(int);
extern void _clp_classlistall(int);
extern void _clp___findslot_c(int);
extern void _clp___findslot_p(int);
extern void _clp___findslot_s(int);
extern void _clp___findslot3_c(int);
extern void _clp___findslot3_p(int);
extern void _clp___findslot3_s(int);
extern void _clp_classidbyname(int);
extern void _clp_classregister(int);
extern void _clp_classattrnames(int);
extern void _clp_classmethnames(int);
extern void _clp_classobjectlength(int);
extern void _clp_classinheritstruct(int);

//variable.obj:
extern void _clp_gc(int);

//xmethod2.obj:

//pad.obj:
extern void _clp_pad(int);
extern void _clp_padc(int);
extern void _clp_padl(int);
extern void _clp_padr(int);

//quit.obj:
extern void _clp___quit(int);
extern void _clp_errorlevel(int);
extern void _clp_quit(int);

//trigon.obj:
extern void _clp_pi(int);
extern void _clp_cos(int);
extern void _clp_cot(int);
extern void _clp_sin(int);
extern void _clp_tan(int);
extern void _clp_acos(int);
extern void _clp_asin(int);
extern void _clp_atan(int);
extern void _clp_atn2(int);
extern void _clp_dtor(int);
extern void _clp_rtod(int);

//vmm.obj:
extern void _clp_xvread(int);
extern void _clp_xvclear(int);
extern void _clp_xvwrite(int);
extern void _clp_xvgetint(int);
extern void _clp_xvputbin(int);
extern void _clp_xvputint(int);
extern void _clp_xvgetbyte(int);
extern void _clp_xvgetchar(int);
extern void _clp_xvgetflag(int);
extern void _clp_xvgetlong(int);
extern void _clp_xvisequal(int);
extern void _clp_xvputbyte(int);
extern void _clp_xvputchar(int);
extern void _clp_xvputfill(int);
extern void _clp_xvputflag(int);
extern void _clp_xvputlong(int);
extern void _clp_xvgetbig16(int);
extern void _clp_xvgetbig32(int);
extern void _clp_xvgetlit16(int);
extern void _clp_xvgetlit32(int);
extern void _clp_xvputbig16(int);
extern void _clp_xvputbig32(int);
extern void _clp_xvputlit16(int);
extern void _clp_xvputlit32(int);
extern void _clp_xvgetdouble(int);
extern void _clp_xvputdouble(int);

//asc.obj:
extern void _clp_asc(int);
extern void _clp_chr(int);
extern void _clp_bin(int);

//valtype.obj:
extern void _clp_valtype(int);

//procline.obj:
extern void _clp_procline(int);
extern void _clp_procname(int);
extern void _clp_varstack(int);
extern void _clp_callstack(int);
extern void _clp_localstack(int);
extern void _clp___varprint(int);

//bit.obj:
extern void _clp_isbit(int);
extern void _clp_numor(int);
extern void _clp_numand(int);
extern void _clp_numnot(int);
extern void _clp_numxor(int);
extern void _clp_setbit(int);
extern void _clp_clearbit(int);

//time2sec.obj:
extern void _clp_sectotime(int);
extern void _clp_timetosec(int);

//dtos.obj:
extern void _clp___dat2num(int);
extern void _clp___num2dat(int);
extern void _clp_dtos(int);
extern void _clp_stod(int);

//time.obj:
extern void _clp_ostime(int);
extern void _clp_seconds(int);
extern void _clp_dati2ostime(int);
extern void _clp_ostime2dati(int);
extern void _clp_date(int);
extern void _clp_time(int);

//memoread.obj:
extern void _clp_memoread(int);
extern void _clp_memowrit(int);

//xtoc.obj:
extern void _clp_ctof(int);
extern void _clp_ftoc(int);
extern void _clp_xtoc(int);

//exec.obj:
extern void _clp_exec(int);

//split.obj:
extern void _clp_split(int);

//getpid.obj:
extern void _clp_getpid(int);

//substr.obj:
extern void _clp_right(int);
extern void _clp_substr(int);
extern void _clp_left(int);

//setfdati.obj:
extern void _clp_setfdati(int);

//ascan.obj:
extern void _clp_acopy(int);
extern void _clp_aeval(int);
extern void _clp_afill(int);
extern void _clp_ascan(int);
extern void _clp_atail(int);
extern void _clp__asort_ascendblock(int);

//like.obj:
extern void _clp_like(int);

//round.obj:
extern void _clp_round(int);
extern void _clp_int(int);

//fsetlock.obj:
extern void _clp_funlock(int);
extern void _clp_fsetlock(int);

//exename.obj:
extern void _clp_exename(int);

//nlstext.obj:
extern void _clp_nls_load_translation(int);

//fseek.obj:
extern void _clp_fseek(int);

//closeonexec.obj:
extern void _clp_getcloexecflag(int);
extern void _clp_setcloexecflag(int);

//chsize.obj:
extern void _clp_chsize(int);

//directory.obj:
extern void _clp_directory(int);

//fork.obj:
extern void _clp_fork(int);

//chown.obj:
extern void _clp_chown(int);
extern void _clp_fchown(int);
extern void _clp_lchown(int);

//wait.obj:
extern void _clp_waitpid(int);
extern void _clp_wait(int);

//spawn.obj:
extern void _clp_spawn(int);

//pipe.obj:
extern void _clp_pipe(int);

//filecreat.obj:
extern void _clp_fopen(int);
extern void _clp_fcreate(int);
extern void _clp_getshare(int);
extern void _clp_setshare(int);

//signals.obj:
extern void _clp_signal_lock(int);
extern void _clp_signal_mask(int);
extern void _clp_signal_send(int);
extern void _clp_signal_clear(int);
extern void _clp_signal_raise(int);
extern void _clp_signal_unlock(int);
extern void _clp_signal_unmask(int);
extern void _clp_signal_pending(int);
extern void _clp_signal_setmask(int);
extern void _clp_signal_description(int);

//filecopy.obj:
extern void _clp_filecopy(int);

//diskfree.obj:
extern void _clp_diskfree(int);

//fdup.obj:
extern void _clp_fdup(int);
extern void _clp_hdup(int);

//readdir.obj:
extern void _clp___opendir(int);
extern void _clp___readdir(int);
extern void _clp___closedir(int);

//findnext.obj:
extern void _clp_findnext(int);
extern void _clp_findrest(int);
extern void _clp_findsave(int);
extern void _clp_findclose(int);
extern void _clp_findfirst(int);

//direxist.obj:
extern void _clp_direxist(int);
extern void _clp_fileexist(int);
extern void _clp_fileisexecutable(int);

//envir.obj:
extern void _clp_getenv(int);
extern void _clp_putenv(int);
extern void _clp_environment(int);

//thread.obj:
extern void _clp_thread_exit(int);
extern void _clp_thread_join(int);
extern void _clp_thread_self(int);
extern void _clp_thread_create(int);
extern void _clp_thread_detach(int);
extern void _clp_thread_cond_init(int);
extern void _clp_thread_cond_wait(int);
extern void _clp_thread_mutex_init(int);
extern void _clp_thread_mutex_lock(int);
extern void _clp_thread_cond_signal(int);
extern void _clp_thread_cond_destroy(int);
extern void _clp_thread_mutex_unlock(int);
extern void _clp_thread_create_detach(int);
extern void _clp_thread_mutex_destroy(int);
extern void _clp_thread_mutex_trylock(int);

//utime.obj:
extern void _clp_touch(int);
extern void _clp_utime(int);

//filetime.obj:
extern void _clp_getfiletime(int);
extern void _clp_setfiletime(int);


//setcursor.obj:
extern void _clp_maxcol(int);
extern void _clp_maxrow(int);
extern void _clp_setcursor(int);
extern void _clp_col(int);
extern void _clp_row(int);

//achoice.obj:
extern void _clp_achoice(int);

//alert.obj:
extern void _clp_alert(int);
extern void _clp_alertblock(int);

//drawbox.obj:
extern void _clp_dispbox(int);
extern void _clp_drawbox(int);
extern void _clp_message(int);
extern void _clp_choicebox(int);
extern void _clp_botmessage(int);
extern void _clp_topmessage(int);

//listbox.obj:
extern void _clp_listboxini(int);
extern void _clp_listboxnew(int);
extern void _clp_listboxclass(int);

//devout.obj:
extern void _clp_devout(int);
extern void _clp_devpos(int);
extern void _clp_setpos(int);
extern void _clp_devoutpict(int);
extern void _clp_devoutbuffer(int);
extern void _clp_devoutvertical(int);

//main.obj:

//o_get.obj:
extern void _clp_getini(int);
extern void _clp_getnew(int);
extern void _clp_getclass(int);

//mask.obj:
extern void _clp_mskget(int);
extern void _clp_msksay(int);
extern void _clp_mskhide(int);
extern void _clp_msklist(int);
extern void _clp_mskloop(int);
extern void _clp_mskshow(int);
extern void _clp_mskcheck(int);
extern void _clp_mskradio(int);
extern void _clp_mskcreate(int);

//scroll.obj:
extern void _clp_scroll(int);
extern void _clp_inverserect(int);

//savescreen.obj:
extern void _clp_screeninv(int);
extern void _clp_restscreen(int);
extern void _clp_savescreen(int);

//getsys.obj:
extern void _clp_updated(int);
extern void _clp_readexit(int);
extern void _clp_getactive(int);
extern void _clp_getreader(int);
extern void _clp_readmodal(int);
extern void _clp_readinsert(int);
extern void _clp_getapplykey(int);
extern void _clp_getprevalidate(int);
extern void _clp_getpostvalidate(int);

//inkey.obj:
extern void _clp_inkey(int);
extern void _clp_lastkey(int);
extern void _clp_nextkey(int);
extern void _clp___keyboard(int);

//checkbox.obj:
extern void _clp_checkboxini(int);
extern void _clp_checkboxnew(int);
extern void _clp_checkboxclass(int);
extern void _clp_radiobuttonini(int);
extern void _clp_radiobuttonnew(int);
extern void _clp_radiobuttonclass(int);

//colorutil.obj:
extern void _clp_logcolor(int);
extern void _clp_revcolor(int);

//setcaption.obj:
extern void _clp_setcaption(int);

//screenchr.obj:
extern void _clp_screenchar(int);
extern void _clp_screenattr(int);
extern void _clp_screencompose(int);

//ialert.obj:
extern void _clp_interactive_alert(int);

//dispbegin.obj:
extern void _clp_dispend(int);
extern void _clp_dispbegin(int);

//memoedit.obj:
extern void _clp_memoedit(int);

//getmethod.obj:
extern void _clp__get_end(int);
extern void _clp__get_home(int);
extern void _clp__get_left(int);
extern void _clp__get_type(int);
extern void _clp__get_undo(int);
extern void _clp__get_reset(int);
extern void _clp__get_right(int);
extern void _clp__get_assign(int);
extern void _clp__get_delend(int);
extern void _clp__get_delete(int);
extern void _clp__get_insert(int);
extern void _clp__get_varget(int);
extern void _clp__get_varput(int);
extern void _clp__get_baddate(int);
extern void _clp__get_delleft(int);
extern void _clp__get_display(int);
extern void _clp__get_delright(int);
extern void _clp__get_setfocus(int);
extern void _clp__get_todecpos(int);
extern void _clp__get_wordleft(int);
extern void _clp__get_backspace(int);
extern void _clp__get_colordisp(int);
extern void _clp__get_killfocus(int);
extern void _clp__get_wordright(int);
extern void _clp__get_overstrike(int);
extern void _clp__get_delwordleft(int);
extern void _clp__get_untransform(int);
extern void _clp__get_createwindow(int);
extern void _clp__get_delwordright(int);
extern void _clp__get_updatebuffer(int);

//truename.obj
extern void _clp_truename(int);

#endif // _CCCEXT2_H_
