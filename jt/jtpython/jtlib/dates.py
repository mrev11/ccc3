##! /usr/bin/env python
# _*_ coding: latin-1 _*_
 

_MONTH_NAMES = [ 
'January', 'February', 'March'     , 'April'   , 'May'      , 'June'      , 
'July'   , 'August'  , 'September' , 'October' , 'November' , 'December'  ]

_DAY_NAMES=['Sunday','Monday','Tuesday','Wednesday','Thursday','Friday','Saturday']

_DAYS_IN_MONTH = [ 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 ]

_DAYS_BEFORE_MONTH = []
dbm = 0
for dim in _DAYS_IN_MONTH:
    _DAYS_BEFORE_MONTH.append(dbm)
    dbm = dbm + dim
del dbm, dim

_INT_TYPES = type(1), type(1L)


def _is_leap( year ): # 1 if leap year, else 0
    if year % 4 != 0: return 0
    if year % 400 == 0: return 1
    return year % 100 != 0


def _days_in_year( year ): # number of days in year
    return 365 + _is_leap(year)


def _days_before_year( year ): # number of days before year
    return year*365L + (year+3)/4 - (year+99)/100 + (year+399)/400


def _days_in_month( month, year ): # number of days in month of year
    if month == 2 and _is_leap(year): return 29
    return _DAYS_IN_MONTH[month-1]


def _days_before_month( month, year ): # number of days in year before month
    return _DAYS_BEFORE_MONTH[month-1] + (month > 2 and _is_leap(year))


def _date2num( date ): # compute ordinal of date.month,day,year
    return _days_before_year( date.year ) + \
           _days_before_month( date.month, date.year ) + \
           date.day


_DI400Y = _days_before_year( 400 )  # number of days in 400 years


def _num2date( n ): # return date with ordinal n

    ans=date()
    del ans.ord
    ans.ord=n

    n400=(n-1)/_DI400Y  # 400-year blocks preceding
    year, n = 400*n400, n-_DI400Y*n400 

    more=n/365
    dby=_days_before_year(more)
    if dby >= n:
        more = more - 1
        dby = dby - _days_in_year( more )
    year, n = year + more, int(n - dby)

    try: year = int(year)
    except (ValueError, OverflowError): pass

    month = min( n/29 + 1, 12 )
    dbm = _days_before_month( month, year )
    if dbm >= n:
        month = month - 1
        dbm = dbm - _days_in_month( month, year )

    ans.month, ans.day, ans.year = month, n-dbm, year
    return ans


class date:

    def __init__( self, year=None, month=None, day=None ):

        if year==None and month==None and day==None:
            self.ord=0 # empty date

        else:
            if not 1 <= month <= 12:
                raise ValueError, ('month must be in 1..12',month)
            dim = _days_in_month( month, year )
            if not 1 <= day <= dim:
                raise ValueError, ('day must be in 1..'+str(dim),day)
            self.month, self.day, self.year = month, day, year
            self.ord = _date2num( self )

    
    def __setattr__( self, name, value ):
        if self.__dict__.has_key(name):
            raise AttributeError, ('read-only attribute ',name)
        self.__dict__[name] = value


    def __cmp__( self, other ):
        if type(self)!=type(other):
            return cmp(type(self),type(other))
        return cmp( self.ord, other.ord )

    
    def __hash__( self ): # for dictionary keys 
        return hash( self.ord )


    def __repr__( self ):
        return dtoc(self)


    def __add__( self, n ):
        if type(n) not in _INT_TYPES:
            raise TypeError, ('can\'t add ' + `type(n)` + ' to date')
        return _num2date( self.ord + n )
 
    __radd__=__add__ # handle int+date


    def __sub__( self, other ):
        if type(other) in _INT_TYPES:  # date-int
            return _num2date( self.ord - other )
        else:
            return self.ord - other.ord  # date-date

    
    def __rsub__( self, other ): # complain about int-date 
        raise TypeError, ('Can\'t subtract date from integer')


    def weekday( self ):
        return int((5+self.ord)%7)


    def cweekday( self ):
        return _DAY_NAMES[self.weekday()]
 


def today():
    import time
    local = time.localtime(time.time())
    return date( local[0], local[1], local[2] )


def emptydate():
    return date() # ord==0


def dtos(d):
    if d.ord==0: 
        return "        "
    return "%04d%02d%02d" % (d.year,d.month,d.day)


def stod(s):
    if not s.strip():
        return emptydate()    
    return date(int(s[0:4]),int(s[4:6]),int(s[6:8]))


def dtoc(d,format="%04d-%02d-%02d"):
    if d.ord==0:
        return (format % (0,0,0)).replace("0"," ")
    return format % (d.year,d.month,d.day)
    
    