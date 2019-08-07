
XCODE.xlib.datepicker={};


XCODE.xlib.datepicker.show=function(input_id) //input-onclick
{
    //console.log("show",input_id);
    var datepicker_id=input_id+"-datepicker";
    var input=document.getElementById(input_id);
    var datepicker=document.getElementById(datepicker_id);
    datepicker.innerHTML=XCODE.xlib.datepicker.table(input.value);
    if( datepicker.style.display=="none" )
    {
        datepicker.style.display="block";
    }
    else
    {
        datepicker.style.display="none";
    }
    event.stopPropagation();
}


XCODE.xlib.datepicker.clear=function(datepicker_id) //input-onblur
{
    //console.log("clear",datepicker_id);
    var datepicker=document.getElementById(datepicker_id)
    datepicker.style.display="none";
}


XCODE.xlib.datepicker.pick=function(ctrl,n_date,otherpage) //td-onmousedown
{
    //console.log("pick",ctrl.textContent);
    var input=XCODE.xlib.datepicker.getinput(ctrl);
    var picker=XCODE.xlib.datepicker.getpicker(ctrl);

    if( otherpage ) 
    {
        picker.innerHTML=XCODE.xlib.datepicker.table(input.value,n_date);
        event.preventDefault();
    }
    else 
    {
        var d_date=new Date(n_date);
        input.value=XCODE.dat2str(d_date);
        //input.dispatchEvent(new Event('change'));
        //console.log('datepicker_pick: dispatch-change');
    }
}

XCODE.xlib.datepicker.getpicker=function(ctrl)
{
    while( ctrl!=null )
    {
        //console.log(ctrl.nodeName,ctrl.className);
        if( ctrl.className=="datepicker" )
        {
            var input_id=ctrl.id.replace("-datepicker","");
            var input=document.getElementById(input_id);
            return ctrl;
        }
        ctrl=ctrl.parentNode;
    }
}

XCODE.xlib.datepicker.getinput=function(ctrl)
{
    while( ctrl!=null )
    {
        //console.log(ctrl.nodeName,ctrl.className);
        if( ctrl.className=="datepicker" )
        {
            var input_id=ctrl.id.replace("-datepicker","");
            var input=document.getElementById(input_id);
            return input;
        }
        ctrl=ctrl.parentNode;
    }
}


XCODE.xlib.datepicker.table=function(inputvalue,n_date) 
{
    //-----------------------
    var DATEPICKER_CONFIG = {
    'cssprefix'  : 'dp',
    'months'     : ['Január','Február','Március','Április','Május','Június','Július','Augusztus','Szeptember','Október','November','December'],
    'weekdays'   : ['Vas','Hét','Ked','Sze','Csü','Pén','Szo'],
    'longwdays'  : ['Vasárnap','Hétfő','Kedd','Szerda','Csütörtök','Péntek','Szombat'],
    'weekstart'  : 1, // first day of week: 0-Su or 1-Mo
    'prevyear'   : 'Előző év',
    'nextyear'   : 'Következő év',
    'prevmonth'  : 'Előző hónap',
    'nextmonth'  : 'Következő hónap',
    };

    //-----------------------
    function datepicker_resettime(d_date) 
    {
        d_date.setMilliseconds(0);
        d_date.setSeconds(0);
        d_date.setMinutes(0);
        d_date.setHours(12);
        return d_date;
    }

    //-----------------------
    function datepicker_makehandler(d_date,d_diff,s_units) 
    {
        var s_units=(s_units=='y'?'FullYear':'Month');
        var d_result=new Date(d_date);
        if(d_diff) 
        {
            d_result['set'+s_units](d_date['get'+s_units]()+d_diff); //interesting   
            if(d_result.getDate() != d_date.getDate())
            {
                d_result.setDate(0); //last day of previous month
            }
        }
        return ' onmousedown="XCODE.xlib.datepicker.pick(this,'+ d_result.valueOf() + (d_diff?',1':'')  +')"';
    }
    //-----------------------

    var s_pfx = DATEPICKER_CONFIG.cssprefix;

    var d_today = datepicker_resettime(new Date());

    var d_selected;
    var n_millisec=Date.parse(inputvalue);
    if( !isNaN(n_millisec) )
    {
        d_selected=datepicker_resettime(new Date(n_millisec));
    }
    else
    {
        d_selected=new Date(d_today);
    }

    var d_date;   
    if( n_date==null )
    {
        d_date=new Date(d_selected);
    }
    else
    {
        d_date=new Date(n_date);
    }

    //console.log(inputvalue,d_selected, d_date);

    var s_html;

    s_html='<table class="'+s_pfx+'Controls">';
    s_html+='<tbody>';
    s_html+='<tr>'
        + '<td class="'+s_pfx+'PrevYear" ' + datepicker_makehandler(d_date, -1, 'y') + ' title="' + DATEPICKER_CONFIG.prevyear  + '">«</td>'
        + '<td class="'+s_pfx+'PrevMonth"' + datepicker_makehandler(d_date, -1, 'm') + ' title="' + DATEPICKER_CONFIG.prevmonth + '">‹</td>'
        + '<th>' + d_date.getFullYear() + ' ' + DATEPICKER_CONFIG.months[d_date.getMonth()]+'</th>'
        + '<td class="'+s_pfx+'NextMonth"' + datepicker_makehandler(d_date,  1, 'm') + ' title="' + DATEPICKER_CONFIG.nextmonth + '">›</td>'
        + '<td class="'+s_pfx +'NextYear"' + datepicker_makehandler(d_date,  1, 'y') + ' title="' + DATEPICKER_CONFIG.nextyear  + '">»</td>'
        + '</tr>';
    s_html+='</tbody>';
    s_html+='</table>';
    
    
    s_html+='<table class="'+s_pfx+'Grid">';
    s_html+='<tbody>';

    // print weekdays titles
    s_html+='<tr>';
    for( var i=0; i<7; i++ )
    {
        s_html+='<th>' + DATEPICKER_CONFIG.weekdays[(DATEPICKER_CONFIG.weekstart+i)%7] + '</th>';
    }
    s_html+='</tr>';

    // print calendar table

    var d_firstDay = new Date(d_date);
    d_firstDay.setDate(1);
    d_firstDay.setDate(1-(7+d_firstDay.getDay()-DATEPICKER_CONFIG.weekstart)%7);
    var d_current = new Date(d_firstDay);

    while( d_current.getMonth()==d_date.getMonth() || d_current.getMonth()==d_firstDay.getMonth()) 
    {
        s_html+='<tr>';
        for( var n_wday=0; n_wday<7; n_wday++ ) 
        {
            var a_class = [];
            var n_date  = d_current.getDate();
            var n_month = d_current.getMonth();

            if( d_current.getMonth() != d_date.getMonth() )
            {
                a_class[a_class.length] = s_pfx+'OtherMonth';
            }
            if( d_current.getDay() == 0 || d_current.getDay() == 6 )
            {
                a_class[a_class.length] = s_pfx+'Weekend';
            }
            if( d_current.valueOf() == d_today.valueOf() )
            {
                a_class[a_class.length]=s_pfx+'Today';
            }
            if( d_current.valueOf() == d_selected.valueOf() )
            {
                a_class[a_class.length] = s_pfx + 'Selected';
            }

            s_html+='<td'+datepicker_makehandler(d_current)+(a_class.length?'class="'+ a_class.join(' ')+'">':'>')+n_date+'</td>';

            d_current.setDate(++n_date);
        }
        s_html+='</tr>';
    }
    s_html+='</tbody>';
    s_html+='</table>';

    return s_html;
}

