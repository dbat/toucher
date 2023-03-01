#pragma warning(disable:4254)
#ifndef IDE
#pragma comment(lib, "minicrt.lib")
#endif
#undef UNICODE
#include <windows.h>
#undef UNICODE
#include <stdlib.h>
#undef UNICODE
#include <stdio.h>
#undef UNICODE
//#pragma comment(linker, "/noDefaultLib")
#pragma comment(linker, "/subSystem:Console")
//#pragma comment(linker, "/ignore:4254")
#undef UNICODE
#include <time.h>
#undef UNICODE
#include <tchar.h>
#undef UNICODE
#include "libctiny.h"

//#define ebug
#ifdef ebug
#define EBUG
//#undef DEBUG
//MPRES = 4d 50 52 45 53
#endif

#ifdef EBUG
#define DEBUG
#endif

// can not be compiled by bcc, use vc instead

#ifdef DEBUG
#define DEBUG1 1
#define DEBUG2 2
#define DEBUG3 3
#define DEBUG4 4
#define DEBUG5 5
#define DEBUG6 6
#define DEBUG7 7
#endif

#define __PRN__	printf(_T("--- line %.4d ---\n"), __LINE__);
#define __PRNX__ printf(_T("--- line %.4d --- "), __LINE__);
#define println	printf(_T("\n"));

#define TRACE(a, b) __PRNX__ printf(a, b);
#define TRACE3(a, b, c) __PRNX__ printf(a, b, c);

#define TRACES(s) __PRNX__ printf("S: %s\n", s);


#define CENTURY_SHIFT 37

//#define Err_NOARGUMENTS
//#define Err_INVALIDSWITCH -25
//#define Err_INVALIDOPT -26

#define IDCHR(id, c) TCHAR id = _T(c)
#define IDSTR(id, S) TCHAR * id = _T(S)
#define IDSTRID(id) TCHAR * id = _T(#id)
#define ID2STRID(id, idx) TCHAR * id##idx = _T(#id " " #idx)
#define ID3STRID(id, idm, idx) TCHAR * id##idm##idx = _T(#id " " #idm " " #idx)

#define IDIDSTR(id) TCHAR * id = _T(#id)

typedef enum {false, true} bool;

TCHAR *optarg;	// global argument pointer
int	optind = 0; // global argv index
int options = 0;// global options
TCHAR *StartDir; //


#define STRLEN	_tcslen
#ifdef IDE
#define ITOA(n, s, r)	_itot_s(n, s, 11, r)
#define STRCPY(dst, src)		_tcscpy_s(dst, STRLEN(src) + 1, src)
#define STRNCPY(dst, src, n)	_tcsncpy_s(dst, n + 1, src, n)
#else
#define ITOA	_itot
#define STRCPY	_tcscpy
#define STRNCPY	_tcsncpy
#endif
#define STRCMP  _tcscmp
#define STRCHR  _tcschr
#define STRRCHR	_tcsrchr
#define STRCSPN	_tcscspn
#define STRCAT	_tcscat
#define ATOI	_tstoi
//#define ATOI64	_tstoi64
#define TOLOWER	_totlower
#define ISDIGIT	_istdigit

#ifdef IDE
#else
#endif

#define I64TOA	_i64tot BAAD!


#define CO_RED      "\x1B[31m"
#define CO_GREEN    "\x1B[32m"
#define CO_YELLOW   "\x1B[33m"
#define CO_BLUE     "\x1B[34m"
#define CO_MAGENTA  "\x1B[35m"
#define CO_CYAN     "\x1B[36m"
#define CO_WHITE    "\x1B[37m"
#define CO_RESET    "\x1B[0m"

#define PRINTF(s) printf(_T(s))
#define PRINTF00(s) printf(_T(s))
#define PRINTF02(s, c) printf(_T(s), _T(c))
#define PRINTF1n(s, n) printf(_T(s), n)
#define PRINTF1p(s, p) printf(_T(s), p)
#define PRINTF2p(s, p, q) printf(_T(s), p, q)
#define PRINTF3p(s, p, q, r) printf(_T(s), p, q, r)


TCHAR * _getBasename(TCHAR * arg0) {
	TCHAR *p, *s = arg0;
	p = s;
	while((*p) && ((*p) != _T('\\'))) p++;
	while((*p)) {
		s = ++p;
		while ((*p) && ((*p) != _T('\\'))) p++;
	}
	return s;
}

IDSTR(version_number,	"1.0.4.0");
//IDSTR(version_build,	"35");
int version_build = 596;
IDSTR(version_progname,	"toucher");
IDSTR(version_created,	"2003.09.27");
//IDSTR(version_revised,	"2016.10.08");
IDSTR(version_revised,	"2018.04.10");

IDSTR(SEConvert,	"Conversion Error %s %s");
IDSTR(SCFileTime,	"Filetime");
IDSTR(SCSystemtime,	"Systemtime");
IDSTR(SCLocaltime,	"Localtime");

//#define movfttoI64(i, ft, u) \
//	u.LowPart = (ft).dwLowDateTime; u.HighPart = (ft).dwHighDateTime; i = L.QuadPart;
//
//#define movI64toft(ft, i, u) \
//	u.QuadPart = i;	(ft).dwLowDateTime = u.LowPart; (ft).dwHighDateTime = u.HighPart;

int _showLastErrNULL(_TCHAR *msg, ...) // CAUTION: the last given argument MUST BE NULL!!!
{
	_TCHAR *lem, *s;
	va_list args;
	unsigned err;
	err = GetLastError();
	FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER |
		FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
		NULL, err, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), (LPTSTR) &lem, 0, NULL);
	//----printf(_T("ERROR: %s.\nLast error code:%d\n%s"), msg, err, lem);
	//----no need to show last error string
	printf(_T("ERROR[%d]"), err);
	// error 0 = success,
	// error 183 = file already exists
	if (err != 183 && err != 0) printf(_T(" %s"), lem);
	LocalFree(lem);
	if(msg)	{ // printf(_T("ERROR[%d] %s"), err, msg);
		va_start(args, msg);
		printf(_T("%s"), msg);
		s = va_arg(args, TCHAR*);
		while(s) {
			printf(_T("%s"), s);
			s = va_arg(args, TCHAR*);
		}
		va_end(args);
		printf(_T("\n"));
	}
	return 0;
}

int _LastErr() { return _showLastErrNULL(NULL); }
int _showerr(_TCHAR *msg) { return _showLastErrNULL(msg, NULL); }
int _shower2(_TCHAR *msg1, TCHAR * msg2) { return _showLastErrNULL(msg1, msg2, NULL); }
//int _shower3(_TCHAR *msg1, TCHAR * msg2, TCHAR * msg3) { return _showLastErrNULL(msg1, msg2, msg3, NULL); }

//#define SHOWERR(s) _showerr(_T(s))
//#define SHOWER2(s1, s2) _shower2(_T(s), _T(s2))
//#define SHOWER3(s1, s2, s3) _shower3(_T(s), _T(s2), _T(s3))

//#define SHOWER1p(s, p) _shower2(_T(s), p)
//#define SHOWER2p(s, p) _shower3(_T(s), p1, p2)

//#define SHOWER1n(s, n) _SHOWER1n(_T(s), n)
//#define SHOWER2n(s, n1, n2) _SHOWER2n(_T(s), n1, n2)

//#define PRINTF(s) printf(_T(s))
//#define PRINTF1(s, n) printf(_T(s), n)
//#define PRINTF2(s, n1, n2) printf(_T(s), n1, n2)


//int _SHOWER2n(_TCHAR *msg, int n1, int n2) {
//	TCHAR *s1 = _T("-4294967296"), *s2 = _T("-4294967296");
//	s1 = (TCHAR*)ITOA(n1, s1, 10);
//	s2 = (TCHAR*)ITOA(n2, s2, 10);
//	return _showLastErrNULL(msg, s1, s2, NULL);
//}
//
//int _SHOWER1n(_TCHAR *msg, int n) {
//	TCHAR * sn = _T("-4294967296"); // "18446744073709551616"; // "-4294967296";
//	sn = (TCHAR*)ITOA(n, sn, 10);
//	return _showLastErrNULL(msg, sn, NULL);
//}

#define OPTERR_UNKNOWN       -1

#define DTERR_INV_PATHNAME   -3
#define DTERR_OUTRANGECHAR   -5

#define DTERR_INV_DATETIME   -10
#define DTERR_INV_DATE       -11
#define DTERR_INV_TIME       -12
#define DTERR_INV_LENGTH     -13
#define DTERR_INV_LENGTHODD  -14
#define DTERR_INV_LENGTHEVEN -15

#define DTERR_INV_CENTURY    -21
#define DTERR_INV_YEAR       -22
#define DTERR_INV_MONTH      -23
#define DTERR_INV_DAY        -24
#define DTERR_INV_HOUR       -25
#define DTERR_INV_MINUTE     -26
#define DTERR_INV_SECOND     -27
#define DTERR_INV_MSEC       -28
#define DTERR_INV_DOM        -29
#define DTERR_INV_DOW        -30


#define CVTERR_SYS2FTIME     -31
#define CVTERR_FTIME2SYS     -32
#define CVTERR_FTIME2LOC     -33
#define CVTERR_LOC2FTIME     -34

#define FTERR_ZEROFILETIME   -35
#define FTERR_ZEROSYSTIME    -36

#define CVTERR_LOC2UTIME     -37

#define sBlank	_T("")

int __showERR(DWORD err, TCHAR* msg, int n) {
	IDSTRID(System);
	IDSTRID(Systime);
	IDSTRID(Localtime);
	IDSTRID(Filetime);

	IDSTRID(Invalid);
	IDSTRID(Datetime);
	IDSTRID(Date);
	IDSTRID(Time);
	IDSTRID(Century);
	IDSTRID(Year);
	IDSTRID(Month);
	IDSTRID(Day);
	IDSTRID(Hour);
	IDSTRID(Minute);
	IDSTRID(Second);
	IDSTRID(mSec);

	//IDSTR(OREO, "ERROR");
	IDSTRID(OREO);
	IDSTRID(Warning);

	IDSTRID(Zero);

	IDSTRID(Length);
	IDSTRID(OddLength);
	IDSTRID(EvenLength);
	IDSTRID(Path);

	IDSTR(OutrChar, "outrange char");
	IDSTR(LocalFtime, "Local filetime");
	IDSTR(CantConvert, "Can not convert");
	IDSTR(UnknownError, "Unknown error %s");
	IDSTR(DayOfMonth, "day of the month");
	IDSTR(DayOfWeek, "day of week");

	IDSTR(tpl_SS, "%s! %s: %s\n");
	IDSTR(tpl_Date1, "%s! %s %s: \"%s\"\n");
	IDSTR(tpl_Date2, "%s! %s %s: %d\n");
	IDSTR(tpl_Convert, "%s! %s %s to %s\n");


	//TCHAR Str[512];
	TCHAR * empty = sBlank;
	TCHAR *pre, *p, *p1, *p2;
	TCHAR *e = OREO;
	//if (msg) S = msg;

	p = NULL; pre = Invalid;
	switch (err) {
			case DTERR_INV_PATHNAME   : p = Path       ; break;
			case DTERR_OUTRANGECHAR   : p = OutrChar   ; break;
			case DTERR_INV_DATETIME   : p = Datetime   ; break;
			case DTERR_INV_DATE       : p = Date       ; break;
			case DTERR_INV_TIME       : p = Time       ; break;
			case DTERR_INV_LENGTH     : p = Length     ; break;
			case DTERR_INV_LENGTHODD  : p = OddLength  ; break;
			case DTERR_INV_LENGTHEVEN : p = EvenLength ; break;
			case DTERR_INV_CENTURY    : p = Century    ; break;
			case DTERR_INV_YEAR       : p = Year       ; break;
			case DTERR_INV_MONTH      : p = Month      ; break;
			case DTERR_INV_DAY        : p = Day        ; break;
			case DTERR_INV_HOUR       : p = Hour       ; break;
			case DTERR_INV_MINUTE     : p = Minute     ; break;
			case DTERR_INV_SECOND     : p = Second     ; break;
			case DTERR_INV_MSEC       : p = mSec       ; break;
			case DTERR_INV_DOW        : p = DayOfWeek  ; break;
			case DTERR_INV_DOM        : p = DayOfMonth ; break;
			case FTERR_ZEROFILETIME   : p = Filetime   ; break;
			case FTERR_ZEROSYSTIME    : p = Systime    ; break;
	}
	if (p) {
		if (msg)
			printf(tpl_Date1, e, pre, p, msg);
		else printf(tpl_Date2, e, pre, p, n);
	}
	else {
		switch (err) {
			case CVTERR_FTIME2SYS: p1 = Filetime  , p2 = Systime; break;
			case CVTERR_FTIME2LOC: p1 = Filetime  , p2 = LocalFtime; break;
			case CVTERR_SYS2FTIME: p1 = Systime   , p2 = Filetime; break;
			case CVTERR_LOC2FTIME: p1 = LocalFtime, p2 = Filetime; break;
			case CVTERR_LOC2UTIME: p1 = Localtime,  p2 = Systime; break;
			default: { printf(UnknownError, "\n"); return 0; }
		}
		printf(tpl_Convert, e, CantConvert, p1, p2);
	}
	return 0;
}

int CVTERR(DWORD err) { return __showERR(err, 0, 0); }
int DTERR(DWORD err) { return __showERR(err, 0, 0); }
int DTERR1p(DWORD err, TCHAR * msg) { return __showERR(err, msg, 0); }
int DTERR1n(DWORD err, int n) { return __showERR(err, 0, n); }
int OUTRCHAR(TCHAR * msg) { return __showERR(DTERR_OUTRANGECHAR, msg, 0); }

//#define return_CVTERR(err, opts) { if (opts & OPT_VERYQUIET) return 0; else return __showERR(err, 0, 0); }
#define DEBUG_return_CVTERR(err) return __showERR(err, 0, 0)


#ifdef DEBUG
int _printime_st(SYSTEMTIME *st, bool CR) {
	TCHAR * ords[] = {"th","st","nd","rd"};
	unsigned int dow, ordn;
	if (!st) DEBUG_return_CVTERR(FTERR_ZEROSYSTIME);//{ PRINTF("zero system time!"); return 0; }
	dow = st->wDayOfWeek; // 0-based day of week (0 = sunday, 1 = monday)
	ordn = dow % 100;
	if (ordn > 20) ordn %= 10;
	if (ordn > 3) ordn = 0;
	if (CR) {
		printf("\t wYear: %d\n", st->wYear);
		printf("\t wMonth: %d\n", st->wMonth);
		printf("\t wDay: %d\n", st->wDay);
		printf("\t wHour: %d\n", st->wHour);
		printf("\t wMinute: %d\n", st->wMinute);
		printf("\t wSecond: %d\n", st->wSecond);
		printf("\t wMilliseconds: %d\n", st->wMilliseconds);
		printf("\t wDayOfWeek: %d%s day\n", dow, ords[ordn]);
	}
	else {
		printf("%.02d/%.02d/%.04d %.02d:%.02d:%.02d.%.03d (%d%s)\n",
			st->wDay, st->wMonth, st->wYear, st->wHour,st->wMinute,
			st->wSecond, st->wMilliseconds, (dow - 1) % 7 + 1, ords[ordn]);
		//printf("\n");
	}
	return 0;
}

int _printime_ft(FILETIME * ft, bool CR) {
	SYSTEMTIME st;
	if (!ft) DEBUG_return_CVTERR(FTERR_ZEROFILETIME);//{ PRINTF("zero file time!"); return 0; }
	printf("file: %.08x:%.08x, ", (*ft).dwHighDateTime, (*ft).dwLowDateTime);
	if(!FileTimeToSystemTime(ft, &st)) DEBUG_return_CVTERR(CVTERR_FTIME2SYS);
	//return SHOWERR("Failed to convert FileTime to SystemTime");
	//if(!FileTimeToLocalTime(ft, &st))  return_CVTERR(CVTERR_FTIME2LOC);
	//	return SHOWERR("Failed to convert FileTime to LocalTime");
	printf("sys: "); _printime_st(&st, CR);
	return 0;
}

void _printimei64(__int64 n, bool CR) {
	FILETIME ft;
	ULARGE_INTEGER L;
	L.QuadPart = n;
	ft.dwLowDateTime = L.LowPart;
	ft.dwHighDateTime = L.HighPart;
	_printime_ft(&ft, CR);
}

#define PRINTxST(st)	_printime_st((st), 0);
#define PRINTxFT(ft)	_printime_ft((ft), 0);
#define PRINTxMI(n)	_printimei64(n, 0);

#define PRDBGxFT(n) printf("ft"#n" -\t"); PRINTxFT(&ft##n);
#define PRDBGxST(n) printf("st"#n"\t"); PRINTxST(&st##n);

#define PRDBGxFT0 printf("ft_ -\t"); PRINTxFT(&ft);
#define PRDBGxST0 printf("st_\t"); PRINTxST(&st);

#endif //DEBUG

//#define fttoi64(ft, L, ret) \
//	{ L.LowPart = ft.dwLowDateTime; L.HighPart = ft.dwHighDateTime; ret = L.QuadPart; }

#define int64ToFT(i64, ft) \
	{ ft.dwLowDateTime = i64; ft.dwHighDateTime = i64 >> 32; }

#define int64OfFT(ft) (((__int64)ft.dwHighDateTime << 32) | ft.dwLowDateTime)

#define DAYTICKS 864000000000

void __ft1setOnlyTime(FILETIME *ft1, FILETIME *ft2) { ULARGE_INTEGER u; \
u.LowPart = (*ft1).dwLowDateTime; u.HighPart = (*ft1).dwHighDateTime; \
u.QuadPart = u.QuadPart / DAYTICKS * DAYTICKS + \
(((__int64)(*ft2).dwHighDateTime << 32) | (*ft2).dwLowDateTime) % DAYTICKS; \
(*ft1).dwLowDateTime = u.LowPart; (*ft1).dwHighDateTime = u.HighPart; }

void __ft1setOnlyDate(FILETIME *ft1, FILETIME *ft2) { ULARGE_INTEGER u; \
u.LowPart = (*ft2).dwLowDateTime; u.HighPart = (*ft2).dwHighDateTime; \
u.QuadPart = u.QuadPart / DAYTICKS * DAYTICKS + \
(((__int64)(*ft1).dwHighDateTime << 32) | (*ft1).dwLowDateTime) % DAYTICKS; \
(*ft1).dwLowDateTime = u.LowPart; (*ft1).dwHighDateTime = u.HighPart; }

#define cvt_sttoft(st, ft, n) \
	if(!SystemTimeToFileTime((&st##n), (&ft##n))) \
	return CVTERR(CVTERR_SYS2FTIME); // SHOWERR("can not convert systemtime"#n" to filetime"#n);

#define cvt_fttost(ft, st, n) \
	if(!FileTimeToSystemTime((&ft##n), (&st##n))) \
	return CVTERR(CVTERR_FTIME2SYS); //SHOWERR("can not convert filetime"#n" to systemtime"#n);

__int64 _getLocalDiff() {
	FILETIME ft, ftL;
	SYSTEMTIME st;
	ULARGE_INTEGER u, uL;
	__int64 ret;
	GetSystemTime(&st);
	SystemTimeToFileTime(&st, &ft);
	FileTimeToLocalFileTime(&ft, &ftL);
	u.LowPart = (ft).dwLowDateTime; u.HighPart = (ft).dwHighDateTime;
	uL.LowPart = ftL.dwLowDateTime; uL.HighPart = ftL.dwHighDateTime;
	ret = uL.QuadPart - u.QuadPart;

#ifdef DEBUG7
	__PRN__
		printf("SysTime| "); PRINTxFT(&ft)
		printf("LocTime| "); PRINTxFT(&ftL)
		printf("differs| %0.16I64x (%I64d)\n", ret, ret);
#endif
	return ret; // local - system
}

//use uncommon acronyms (except the obvious like cNul cDot), as we can
#define _cNuL	'\0'
#define _cDoT	'.'
#define _cDcL	':'
#define _cHyP	'-'
#define _cPlS	'+'
#define _cEqU	'='
#define _cSlS	'/'
#define _cBsL	'\\'
#define _cBsP	'\8'
#define _cQoT	'"'
#define _cGrT	'>'
#define _cLeS	'<'
#define _cAsT	'*'
#define _cTlD	'~'
#define _cQsT	'?'
#define _cZrO	'0'
#define _cOnE	'1'
#define _cSiX	'6'
#define _cNiN	'9'
#define _cVeE	'v'

//@me wants uppercase! ok, sure- nobody denied your privileges
#define cTAB	'\t'
#define cSPC	'\x20'


#define tNul	_T(_cNuL)
#define tDot	_T(_cDoT)
#define tDcl	_T(_cDcL)
#define tHyp	_T(_cHyP)
#define tPls	_T(_cPlS)
#define tEqu	_T(_cEqU)
#define tSls	_T(_cSlS)
#define tBsl	_T(_cBsL)
#define tBsp	_T(_cBsP)
#define tQot	_T(_cQoT)
#define tGrt	_T(_cGrT)
#define tLes	_T(_cLsS)
#define tAst	_T(_cAsT)
#define tTld	_T(_cTlD)
#define tQst	_T(_cQsT)
#define tZro	_T(_cZrO)
#define tOne	_T(_cOnE)
#define tSix	_T(_cSiX)
#define tNin	_T(_cNiN)
#define tVee	_T(_cVeE)

#define tTAB	_T(cTAB)
#define tSPC	_T(cSPC)


#define ctOutrangeOfInt(A, i) ((A[i] < tZro) || (A[i] > tNin))
#define toIntCheck2sav(A, i, var, tmp) \
	if ctOutrangeOfInt(A, i) return OUTRCHAR(&A[i]); \
	if ctOutrangeOfInt(A, (i+1)) return OUTRCHAR(&A[i+1]); \
	tmp[0] = A[i]; tmp[1] = A[i + 1]; var = ATOI(tmp);

#define toIntCheckDot(var, i) toIntCheck2sav(dot, i, var, dx)

__int64 ATOI64(const char *s) {
    __int64 ret = 0;
	int n, c = 0;

	while ((c = *s++) != '\0') {
		if (c >= '0' && c <= '9') n = (c - '0');
		else break;
		ret *= 10;
		ret += (__int64)n;
    }
    return ret;
}

//#define isdghex(k) (((k >= '0') && (k <= '9')) || ((k >= 'a') && (k <= 'f')))
//#define isnotdghex(k) (((k < '0') || (k > '9')) && ((k < 'a') || (k > 'f')))
__int64 STRTOI64(const char *digits, char **endptr) { // , int base) {
	const char *s;
 	__int64 N, ret;
	int neg, flag, base = 0;
	char c;

	s = digits;
	do { c = *s++; } while (c == ' ' || c == '\t');
	if (c == '-')
		{ neg = 1; c = *s++; }
	else
		{ neg = 0; if (c == '+') c = *s++; }

	if (c == '0' && (*s == 'x' || *s == 'X'))
		{ c = s[1]; s += 2; base = 16; }
	else base = c == '0' ? 8 : 10;
	ret = flag = 0;

	N = 0;
	for (;;c = *s++) {
		c |= 0x20; //if isnotdghex(c) break;
		c -= '0';
		if (c < 0) break;
		if (c > 9) c -= '0' - 9;
		if (c < 0 || c >= base) break;
		N *= base;
		if(
			(flag < 0)
				|| (neg && (N > ret || (N -= c) > ret)) /* underflow */
				|| (N < ret || (N += c) < ret)          /* overflow */
			)
			{ flag = -1; break; }
		else
			{ ret = N; flag = 1; }
	}

	if (flag < 0)
		ret = neg ? 0x80000000LL : 0x7fffffffLL;

	if (endptr != NULL)
		*endptr = (char *)(flag ? s - 1 : digits);

	return (ret);
}

__int64 parseTimeEpoch(TCHAR * ts, int c) {
#define MAX_USTAMP (0x7fffffffffffffffULL / 10000000ULL)
#define MAX_XSTAMP (0x7fffffffffffffffULL / 10000000ULL - 11644473600ULL)
//9223372036854775807/10000000-11644473600 // 1year = 31,536,000 seconds
	__int64 ret = 0; //__time64_t stamp;
	FILETIME ft; SYSTEMTIME lt, ut; //ULARGE_INTEGER u;
	TIME_ZONE_INFORMATION tz;

	if (!(ts && c)) return ret;
	if ((*ts==tHyp) /* || (*ts==tZro)*/ ) return 0;

	//ret = ATOI64(ts);
	//test 0x5EC1C965
	ret = STRTOI64(ts, NULL);
	//printf("ret = %I64d %I64X\n", ret, ret);
	if ((ret <= 0) || (ret > MAX_USTAMP)) return 0;

	if (c == _T('u')) {
		if (ret > MAX_XSTAMP) return 0;
		ret += 11644473600ULL;
	}

	ret *= (__int64)10000000ULL;
	int64ToFT(ret, ft)

	GetTimeZoneInformation(&tz);
	if(!FileTimeToSystemTime(&ft, &lt)) return CVTERR(CVTERR_FTIME2SYS);
	if(!TzSpecificLocalTimeToSystemTime(&tz, &lt, &ut)) return CVTERR(CVTERR_LOC2UTIME);
	if(!SystemTimeToFileTime(&ut, &ft)) return CVTERR(CVTERR_SYS2FTIME);

	ret = int64OfFT(ft);
	return ret;
}

//============================================================
// FILETIME Contains a 64-bit value representing the number
// of 100-nanosecond intervals since January 1, 1601 (UTC).

__int64 parseTimeStamp(TCHAR * ts) {
	// valid format
	//   15c CCYYMMDDHHmm.ss    12c CCYYMMDDHHmm
	//   13c YYMMDDHHmm.ss      10c YYMMDDHHmm
	//   11c MMDDHHmm.ss         8c MMDDHHmm

	FILETIME ft; SYSTEMTIME lt, ut; //ULARGE_INTEGER u;
	TIME_ZONE_INFORMATION tz;
	__int64 ret = 0; //__time64_t stamp;

	TCHAR dx[] = _T("00");
	TCHAR * dot = _T(".");//, *OutrChr = _T("Outrange char");

	int i, maxmDays;
	int CY = -1, CC = -1, YY = -1, MM = -1, DD = -1, hh, mm, ss = 0;

	int olen, len = STRLEN(ts);
	if (!len) { PRINTF("Empty string"); return 0; };
	//__PRN__

#ifdef DEBUG3
	printf("\n");
	__PRN__
		printf("DBG3| Parsing timestamp: %s\n", ts);
#endif
	olen = len;
	dot = STRCHR(ts, *dot);
	if (dot) {
		if ((ts + len - dot) != 3) return OUTRCHAR(dot);
		toIntCheckDot(ss, 1)
			if (ss > 59) return DTERR1n(DTERR_INV_SECOND, ss);
		len -=3;
	}
	if (len & 1) return DTERR1n(DTERR_INV_LENGTHODD, len);

	if (len > 12) return DTERR1n(DTERR_INV_LENGTH, len);

	for (i = 0; i < len; i++)
		if ((ts[i] < tZro) || (ts[i] > tNin))
			return OUTRCHAR(&ts[i]);

	dot = ts + len - 12;
	switch (len) {
		case 12: //dot = ts + len - 12;
			toIntCheckDot(CC, 0)
				if (CC < 16) return DTERR1n(DTERR_INV_CENTURY, CC);
		case 10: //dot = ts + len - 10;
			toIntCheckDot(YY, 2)
				if (CC < 0) CC = YY > CENTURY_SHIFT ? 19 : 20;
			CY = CC * 100 + YY;
			if (CY < 1601) return DTERR1n(DTERR_INV_YEAR, CY);
		case 8:  //dot = ts + len - 8;
			toIntCheckDot(MM, 4)
				if (MM < 1 || MM > 12) return DTERR1n(DTERR_INV_MONTH, MM);
			toIntCheckDot(DD, 6)
				if (DD < 1 || DD > 31) return DTERR1n(DTERR_INV_DAY, DD);
		case 4:  //dot = ts + len - 4;
			toIntCheckDot(hh, 8)
				if (hh > 23) return DTERR1n(DTERR_INV_HOUR, hh);
			toIntCheckDot(mm, 10)
				if (mm > 59) return DTERR1n(DTERR_INV_MINUTE, mm);
			break;
		default: return DTERR1n(DTERR_INV_LENGTH, olen);
	}

	GetLocalTime(&lt);
	GetTimeZoneInformation(&tz);
	//if(!SystemTimeToFileTime(&st, &fl)) return_CVTERR(CVTERR_SYS2FTIME);
	//if(!LocalFileTimeToFileTime(&fl, &ft)) return_CVTERR(CVTERR_LOC2FTIME);
	//if(!FileTimeToSystemTime(&ft, &st)) return_CVTERR(CVTERR_FTIME2SYS);

	if (CY < 0) CY = lt.wYear;
	if (MM < 0) MM = lt.wMonth;
	if (DD < 0) DD = lt.wDay;

	maxmDays = MM == 2 ?
		28 + ((CY & 3) == 0 && (CY % 25 != 0 || (CY & 15) == 0)) :
	30 + ((MM & 1) ^ (MM > 7));

	//__PRN__
	//printf("year:%d month:%d day:%d maxday:%d", YY, MM, DD, maxmDays);
	//__PRN__


	if (DD > maxmDays)
		return DTERR1n(DTERR_INV_DOM, DD); //SHOWER1n("Day of the month = ", DD);

	//__PRN__ //CY= 1601;
	lt.wYear = CY; lt.wMonth = MM; lt.wDay = DD;
	lt.wDayOfWeek = 19968; //19969;
	lt.wHour = hh; lt.wMinute = mm;
	lt.wSecond = ss; lt.wMilliseconds = 0;//199;


#ifdef DEBUG3
	__PRN__
		printf("STAMP| CY = %d ~\t", CY); PRINTxST(&lt);
#endif

	// if(!SystemTimeToFileTime(&lt, &fl)) return CVTERR(CVTERR_SYS2FTIME);
	// if(!LocalFileTimeToFileTime(&fl, &ft)) return CVTERR(CVTERR_LOC2FTIME);
	// //memset(&ft,0,sizeof(ft));
	// if(!FileTimeToSystemTime(&ft, &lt)) return CVTERR(CVTERR_FTIME2SYS);

	if(!TzSpecificLocalTimeToSystemTime(&tz, &lt, &ut)) return CVTERR(CVTERR_LOC2UTIME);
	if(!SystemTimeToFileTime(&ut, &ft)) return CVTERR(CVTERR_SYS2FTIME);

#ifdef DEBUG3
	__PRN__
		printf("STAMP| CY = %d ~\t", CY); PRINTxST(&ut);
#endif

	//OK: ret = ((__int64)ft.dwHighDateTime << 32) | ft.dwLowDateTime;
	//u.LowPart = (ft).dwLowDateTime; u.HighPart = (ft).dwHighDateTime; ret = u.QuadPart;
	ret = int64OfFT(ft);

#ifdef DEBUG3
	__PRN__
		//printf("STAMP| filetime: %.08x:%.08x\n", ft.dwHighDateTime, ft.dwLowDateTime); // 0167c8c0:96e52080
		printf("STAMP| -- done parsing timestamp: %s\n", ts);
	printf("STAMP| -- "); PRINTxFT(&ft)
		printf("STAMP| -- return value: %.016I64x (%I64d)\n", ret, ret);
	//printf("\n");
#endif

	return ret;
}


__int64 parseDateTime(TCHAR * date) {
	TCHAR dx[] = _T("00\0");
	TCHAR * dot;// = _T(":");
	TCHAR * delims = _T("-./");
	TCHAR * blanks = _T("\"\t ");
	//TCHAR * errStr = _T("Invalid date ");
	//TCHAR * errLen = _T("Length=");
	TCHAR DA[] = _T("1900.01.01\0");
	TCHAR DB[] = _T("00:00:00\0");
	__int64 ret;

	TCHAR *cb, *cp;
	int CY = -1, CC = -1, YY = -1, MM = -1, DD = -1, hh = -1, mm = -1, ss = 0;
	//int d0, d1, d2, d3, d4, d5, d6;
	FILETIME ft; SYSTEMTIME Lt, ut; //ULARGE_INTEGER u;
	TIME_ZONE_INFORMATION tz;
	int goodtime = 0, broken = 0;
	int k, maxmDays = 30, len = STRLEN(date);

#ifdef DEBUG6
	println;
	__PRN__
		printf("DBG6| Parsing datetime: \"%s\"\n", date);
#endif

	if(len < 8) return DTERR1n(DTERR_INV_LENGTH, len);
	//memset(dta,0,sizeof(dta));
	//memset(dtb,0,sizeof(dtb));
	DA[0] = tNul; DB[0] = tNul;

	cp = DA; cb = date;

	switch (len) {
		case 8: if(date[2] == tDcl) cp = DB; break;
		case 10: break;
		case 17:
		case 19: STRNCPY(DB, &cb[len - 8], 8); len -= 9; break;
		default: return DTERR1n(DTERR_INV_LENGTH, len);
	}

	STRNCPY(cp, cb, len); cp[len] = tNul;

	GetLocalTime(&Lt);
	GetTimeZoneInformation(&tz);

#ifdef DEBUG6
	//__PRN__
	//	GetSystemTime(&St);
#endif
#ifdef DEBUG6
	__PRN__
		printf("DBG6| Lt: "); PRINTxST(&Lt)
		//printf("DBG6| st: "); PRINTxST(&St)
#endif

		if (*DA) {
			k = STRCSPN(DA, delims);
			if ((len == 10) && (DA[k] == tDot))
				broken = (k != 4);
			else broken = (k != 2);

			//printf("len=%d k=%d brk=%d\n", len, k, broken);
			broken |= (DA[k] != DA[k + 3]);
			if(broken) return DTERR1p(DTERR_INV_DATE, DA);

			dot = DA;
			if (dot[k] == tDot) {
				toIntCheckDot(DD, len-2);
				toIntCheckDot(MM, len-5);
				toIntCheckDot(YY, len-8);
				if (len > 8) {
					CC = YY;
					{ toIntCheckDot(CC, len-10) }
				}
				else CC = YY > CENTURY_SHIFT ? 19 : 20;
			}
			else {
				toIntCheckDot(DD, 0);
				toIntCheckDot(MM, 3);
				if (dot[k] == tSls)
				{ YY = MM; MM = DD; DD = YY; }
				toIntCheckDot(YY, 6);
				if (len > 8) {
					CC = YY;
					{ toIntCheckDot(YY, 8) }
				}
				else CC = YY > CENTURY_SHIFT ? 19 : 20;
			}

			if (MM < 1 || MM > 12) return DTERR1n(DTERR_INV_MONTH, MM);
			if (DD < 1 || DD > 31) return DTERR1n(DTERR_INV_DAY, DD);

			CY =  CC * 100 + YY;
			if (CY < 1601) return DTERR1n(DTERR_INV_YEAR, CY);

			maxmDays = MM == 2 ?
				28 + ((CY & 3) == 0 && (CY % 25 != 0 || (CY & 15) == 0)) :
			30 + ((MM & 1) ^ (MM > 7));

			if (DD > maxmDays) return DTERR1n(DTERR_INV_DOM, DD);

			Lt.wYear = CY;
			Lt.wMonth = MM;
			Lt.wDay = DD;
		}

		if (*DB) {
			if(DB[2] != tDcl || DB[5] != tDcl)
				return DTERR1p(DTERR_INV_TIME, DB);

			dot = DB;
			toIntCheckDot(hh, 0);
			if (hh > 23) return  DTERR1n(DTERR_INV_HOUR, hh);
			toIntCheckDot(mm, 3);
			if (mm > 59) return  DTERR1n(DTERR_INV_MINUTE, mm);
			toIntCheckDot(ss, 6);
			if (ss > 59) return  DTERR1n(DTERR_INV_SECOND, ss);

			Lt.wHour = hh;
			Lt.wMinute = mm;
			Lt.wSecond = ss;
			Lt.wMilliseconds = 0;
		}

		// if(!SystemTimeToFileTime(&Lt, &fl)) return CVTERR(CVTERR_SYS2FTIME);
		// if(!LocalFileTimeToFileTime(&fl, &ft)) return CVTERR(CVTERR_LOC2FTIME);

		if(!TzSpecificLocalTimeToSystemTime(&tz, &Lt, &ut)) return CVTERR(CVTERR_LOC2UTIME);
		if(!SystemTimeToFileTime(&ut, &ft)) return CVTERR(CVTERR_SYS2FTIME);

#ifdef DEBUG6
		__PRN__
			//if(!FileTimeToSystemTime(&ft, &St)) DEBUG_return_CVTERR(CVTERR_FTIME2SYS);
#endif

		//ret = ((__int64)ft.dwHighDateTime << 32) | ft.dwLowDateTime;
		ret = int64OfFT(ft);

#ifdef DEBUG6
		__PRN__
			printf("DBG6| -- done parsing datestamp: %s\n", date);
			printf("DBG6| Lt:  "); PRINTxST(&Lt)
			printf("DBG6| ft:  "); PRINTxFT(&ft)
			printf("DBG6| ut:  "); PRINTxST(&ut)
			printf("DBG6| ret: "); PRINTxMI(ret)
			printf("DBG6| -- return value: %.016I64x (%I64d)\n", ret, ret);
		//printf("\n");
#endif

		return ret;
}

// options ===========================================
#define OPT_RECURSIVE	0x0001
#define OPT_FILES		0x0002
#define OPT_DIRS		0x0004
#define OPT_LINKS		0x0008
#define OPT_NOEXEC		0x0010
#define OPT_FILETIME	0x0020
#define OPT_FILEDATE	0x0040
#define OPT_CREATE		0x0080
#define OPT_CTIME		0x0100
#define OPT_WTIME		0x0200
#define OPT_ATIME		0x0400
#define OPT_QUIET		0x0800
#define OPT_VERYQUIET	0x1000
#define OPT_SHOWOPTS	0x2000
#define OPT_DEPTH_FIRST	0x4000

//choice, shiftleft 16, 3 bits (0..7)
#define OPT_USE_DEFTIME 0
#define OPT_USE_CTIME	0x10000
#define OPT_USE_WTIME	0x20000
#define OPT_USE_ATIME	0x30000
#define OPTX_TIMEFIELDSMASK  0x30000

#define OPT_USE_REFTIME	0x40000
#define OPT_USE_XTIME5	0x50000
#define OPT_USE_XTIME6	0x60000
#define OPT_USE_XTIMe7	0x70000
//#define OPT_USE_CURTIME 0x00000 // always prevalent for partial date/time set??
#define OPT_USE_CURTIME 0
#define OPTX_EQTMASK    0x70000

#define OPTS_DOES(id) (opts & OPT_##id)
#define OPTS_HASNT(id) ((opts & OPT_##id) == 0)

#define NOT_QUIET ((opts & OPT_QUIET) == 0)
#define NOT_VERYQUIET ((opts & OPT_VERYQUIET) == 0)
#define NO_DIRS ((opts & OPT_DIRS) == 0)
#define NO_FILES ((opts & OPT_FILES) == 0)
#define NO_TEST ((opts & OPT_NOEXEC) == 0)
#define DO_APPLY ((opts & OPT_NOEXEC) == 0)
#define NO_EXEC (opts & OPT_NOEXEC)
#define NO_FILETIME ((opts & OPT_FILETIME) == 0)
#define NO_FILEDATE ((opts & OPT_FILEDATE) == 0)
#define NO_SHOW ((opts & OPT_SHOWOPTS) == 0)
#define NOT_RECURSIVE ((opts & OPT_RECURSIVE) == 0)
#define CAN_CREATE (opts & OPT_CREATE)
#define CANT_CREATE ((opts & OPT_CREATE) == 0)
#define NOT_DEPTHFIRST ((opts & OPT_DEPTH_FIRST) == 0)

#define USING_CTIME		((opts & OPTX_EQTMASK) == OPT_USE_CTIME)
#define USING_WTIME		((opts & OPTX_EQTMASK) == OPT_USE_WTIME)
#define USING_ATIME		((opts & OPTX_EQTMASK) == OPT_USE_ATIME)
#define USING_REFTIME	((opts & OPTX_EQTMASK) == OPT_USE_REFTIME)
#define USING_XTIME5	((opts & OPTX_EQTMASK) == OPT_USE_XTIME5)
#define USING_XTIME6	((opts & OPTX_EQTMASK) == OPT_USE_XTIME6)
#define USING_XTIMe7	((opts & OPTX_EQTMASK) == OPT_USE_XTIMe7)
#define USING_CURTIME	((opts & OPTX_EQTMASK) == 0)


#define FTIME_USED(opts)  (opts & OPTX_EQTMASK)
#define USING_TIMEFIELDS(opts) (opts & OPTX_TIMEFIELDSMASK)

#define OPT_XTIME_ALL (OPT_CTIME | OPT_ATIME | OPT_WTIME)
//#define GET_EQUTIME(opts) (opts & OPTX_EQTMASK)
//#define SET_EQUTIME(opeq, EQTIME) opeq ^= (EQTIME & OPTX_EQTMASK)
//#define SET_EQUTIME(opts, EQTIME) opts |= (EQTIME & OPTX_EQTMASK)
// options ===========================================

int _ShowOff(opts) {
	TCHAR * DELIM = _T("\n"); //_T(" "); //_T("\n");
	PRINTF1p("Options: 0x%0.4X\n", opts);
	if(opts & OPT_RECURSIVE ) PRINTF1p("\tOPT_RECURSIVE%s", DELIM);
	if(opts & OPT_FILES     ) PRINTF1p("\tOPT_FILES%s", DELIM);
	if(opts & OPT_DIRS      ) PRINTF1p("\tOPT_DIRS%s", DELIM);
	if(opts & OPT_LINKS     ) PRINTF1p("\tOPT_LINKS%s", DELIM);
	if(opts & OPT_NOEXEC    ) PRINTF1p("\tOPT_NOEXEC%s", DELIM);
	if(opts & OPT_FILETIME  ) PRINTF1p("\tOPT_FILETIME%s", DELIM);
	if(opts & OPT_FILEDATE  ) PRINTF1p("\tOPT_FILEDATE%s", DELIM);
	if(opts & OPT_CREATE    ) PRINTF1p("\tOPT_CREATE%s", DELIM);
	if(opts & OPT_CTIME     ) PRINTF1p("\tOPT_CTIME%s", DELIM);
	if(opts & OPT_ATIME     ) PRINTF1p("\tOPT_ATIME%s", DELIM);
	if(opts & OPT_WTIME     ) PRINTF1p("\tOPT_MTIME%s", DELIM);
	if(opts & OPT_QUIET     ) PRINTF1p("\tOPT_QUIET%s", DELIM);
	if(opts & OPT_VERYQUIET ) PRINTF1p("\tOPT_VERYQUIET%s", DELIM);
	if(opts & OPT_DEPTH_FIRST) PRINTF1p("\tOPT_DEPTH_FIRST%s", DELIM);
	if(opts & OPT_SHOWOPTS  ) PRINTF1p("\tOPT_SHOWOPTS%s", DELIM);

	//if((opts & OPTX_EQTMASK) == OPT_USE_CTIME) PRINTF1p("\tOPT_USE_CTIME%s", DELIM);
	//if((opts & OPTX_EQTMASK) == OPT_USE_WTIME) PRINTF1p("\tOPT_USE_WTIME%s", DELIM);
	//if((opts & OPTX_EQTMASK) == OPT_USE_ATIME) PRINTF1p("\tOPT_USE_ATIME%s", DELIM);
	//switch (opts & (7 << 16)) {
	switch (opts & OPTX_EQTMASK) {
		case 0: PRINTF1p("\tOPT_USE_CURTIME%s", DELIM); break;
		case OPT_USE_CTIME: PRINTF1p("\tOPT_USE_CTIME%s", DELIM); break;
		case OPT_USE_WTIME: PRINTF1p("\tOPT_USE_MTIME%s", DELIM); break;
		case OPT_USE_ATIME: PRINTF1p("\tOPT_USE_ATIME%s", DELIM); break;
		case OPT_USE_REFTIME: PRINTF1p("\tOPT_USE_REFTIME%s", DELIM); break;
			//case OPT_USE_CTIME5: PRINTF1p("\tOPT_USE_TIME5%s", DELIM); break;
			//case OPT_USE_CTIME6: PRINTF1p("\tOPT_USE_TIME6%s", DELIM); break;
			//case OPT_USE_CTIME7: PRINTF1p("\tOPT_USE_TIME7%s", DELIM); break;
	}
	//println;
	return opts;
}


#define MOVftLo(a, b) a.dwLowDateTime = b.dwLowDateTime
#define MOVftHi(a, b) a.dwHighDateTime = b.dwHighDateTime
#define MOVft(a, b) { MOVftLo; MOVftHi; }

int cmpft(FILETIME *ft1, FILETIME *ft2) {
	if (ft1 && ft2)
		return ((*ft1).dwLowDateTime == (*ft2).dwLowDateTime) &&
		((*ft2).dwHighDateTime == (*ft2).dwHighDateTime);
	return (ft1 == NULL) && (ft2 == NULL);
}

#define HANDLE_ISOK(h) (h != INVALID_HANDLE_VALUE)
#define HANDLE_ISBAD(h) (h == INVALID_HANDLE_VALUE)

int _procfile(TCHAR * fn, FILETIME * ftime, WIN32_FIND_DATA *data, DWORD opts) {
	HANDLE fh; //ULARGE_INTEGER u;
	DWORD ff, att, ftu = 0, openf = OPEN_EXISTING;
	FILETIME *ftc = NULL, *fta = NULL, *ftw = NULL;
	//FILETIME FC, FA, FW; //FILETIME *ft, *ftc, *pfta, *pftw;
	TCHAR * skip = _T("-skip");

	if NO_EXEC { PRINTF1p("- %s -done -n", fn); return 1; }

	ff = FILE_ATTRIBUTE_NORMAL | FILE_FLAG_NO_BUFFERING | FILE_FLAG_OVERLAPPED;
	//FILE_FLAG_BACKUP_SEMANTICS | FILE_FLAG_OPEN_REPARSE_POINT

	att = (data) ? data->dwFileAttributes : 0;

#define SKIPOUT(src)  { if NOT_QUIET PRINTF2p("%s %s"#src, fn, skip); return 0; }

#ifdef DEBUG2
	__PRNX__ PRINTxFT(ftime)
		TRACES(fn);
	//printf("DBG2.0| ft:  "); PRINTxFT(ft); //printf("DBG2.0| st:  "); PRINTxST(St); //printf("DBG2.0| ret: "); PRINTxMI(ret);
#endif

	if (att & FILE_ATTRIBUTE_DIRECTORY) {
		if NO_DIRS SKIPOUT(dir)
			ff |= FILE_FLAG_BACKUP_SEMANTICS;
	}
	else if NO_FILES SKIPOUT(file);

	fta = ftc = ftw = NULL;

	if (data) {
		if (opts & OPT_CTIME) ftc = &(data->ftCreationTime);
		if (opts & OPT_ATIME) fta = &(data->ftLastAccessTime);
		if (opts & OPT_WTIME) ftw = &(data->ftLastWriteTime);
	}
	else {
		//error?
	}

#ifdef DEBUG21
	__PRN__; printf("DBG2.1| ftime: "); PRINTxFT(ftime); printf("DBG2.1| fta: "); PRINTxFT(fta); printf("DBG2.1| ftc: "); PRINTxFT(ftc); printf("DBG2.1| ftw: "); PRINTxFT(ftw)
#endif

	if USING_TIMEFIELDS(opts)
		switch (FTIME_USED(opts)) {
			case OPT_USE_CTIME: ftc = NULL; ftime = &(data->ftCreationTime); break;
			case OPT_USE_WTIME: ftw = NULL; ftime = &(data->ftLastWriteTime); break;
			case OPT_USE_ATIME: fta = NULL; ftime = &(data->ftLastAccessTime); break;
		}

	//if ((opts & OPT_FILETIME) && (opts & OPT_FILEDATE)) {
	if (opts & (OPT_FILETIME | OPT_FILEDATE)) {
		if (ftc) ftc = ftime;
		if (fta) fta = ftime;
		if (ftw) ftw = ftime;
	}
	else {
		if (opts & OPT_FILEDATE) {
			if (fta) __ft1setOnlyDate(fta, ftime);//, u);
			if (ftc) __ft1setOnlyDate(ftc, ftime);//, u);
			if (ftw) __ft1setOnlyDate(ftw, ftime);//, u);
		}
		else
			if (opts & OPT_FILETIME) {
				if (fta) __ft1setOnlyTime(fta, ftime);//, u);
				if (ftc) __ft1setOnlyTime(ftc, ftime);//, u);
				if (ftw) __ft1setOnlyTime(ftw, ftime);//, u);
			}
			else fta = ftc = ftw = NULL;
	}

#ifdef DEBUG2
	__PRNX__; printf("DBG2.2| ftime: "); PRINTxFT(ftime); printf("DBG2.2| fta: "); PRINTxFT(fta); printf("DBG2.2| ftc: "); PRINTxFT(ftc); printf("DBG2.2| ftw: "); PRINTxFT(ftw)
#endif

		////user pick a questionable search set
		//if ((ftc || ftw || fta) == 0) { if NOT_QUIET PRINTF1p("- %s -nop\n", fn); return 1; }

		// if (opts & OPT_CREATE) openf = OPEN_ALWAYS;
		// do not do create here. dangerous. // we can't, must be done here. // yes we CAN! // NO!

		//compare first
		if (data) {
			if (cmpft(ftc, &(data->ftCreationTime))) ftc = NULL;
			if (cmpft(ftw, &(data->ftLastWriteTime))) ftw = NULL;
			if (cmpft(fta, &(data->ftLastAccessTime))) fta = NULL;
		}

		//user pick a questionable search set
		if ((ftc || ftw || fta) == 0) { if NOT_QUIET PRINTF1p("- %s -nop\n", fn); return 1; }

		// OPT_NOEXEC already trapped in findfirst
		// but its actually less relistic, timedate maybe already the same / nop
		if NO_EXEC { PRINTF1p("- %s -n\n", fn); return 1; }

		if (opts & OPT_CREATE) openf = OPEN_ALWAYS;
		if (opts & OPT_LINKS) ff |= FILE_FLAG_OPEN_REPARSE_POINT;

		fh = CreateFile(fn, FILE_WRITE_ATTRIBUTES, 7, NULL, openf, ff, NULL);
		if HANDLE_ISBAD(fh) return NOT_VERYQUIET & _showerr(fn);
		if NOT_QUIET PRINTF1p("- %s ", fn);

		if(!SetFileTime(fh, ftc, fta, ftw)) {
			CloseHandle(fh);

#ifdef DEBUG23
			__PRN__; printf("DBG2.3| ftime: "); PRINTxFT(ftime); printf("DBG2.3| fta: "); PRINTxFT(fta); printf("DBG2.3| ftc: "); PRINTxFT(ftc); printf("DBG2.3| ftw: "); PRINTxFT(ftw)
#endif
				if NOT_QUIET println;
			return NOT_VERYQUIET & _shower2(_T("Failed to set filetime of: "), fn);
		}
		CloseHandle(fh);
		if NOT_QUIET PRINTF("-done\n");
		return 1;
}

void __copyft(FILETIME * src, FILETIME *dst) {
	dst->dwLowDateTime = src->dwLowDateTime;
	dst->dwHighDateTime = src->dwHighDateTime;
}

#define W32FDATA_FTCREATE 1
#define W32FDATA_FTMODIFY 2
#define W32FDATA_FTACCESS 3

void __Win32FindDataftSet(WIN32_FIND_DATA *data, FILETIME *ft, DWORD ftFields) {
	// copy ftime to timefields based on mask
	// this is stupid. would be much simpler with asm
	if (!data || !ft) return;
	if (ftFields & W32FDATA_FTCREATE) {
		data->ftCreationTime.dwLowDateTime = ft->dwLowDateTime;
		data->ftCreationTime.dwHighDateTime = ft->dwHighDateTime;
	}
	if (ftFields & W32FDATA_FTMODIFY) {
		data->ftLastWriteTime.dwLowDateTime = ft->dwLowDateTime;
		data->ftLastWriteTime.dwHighDateTime = ft->dwHighDateTime;
	}
	if (ftFields & W32FDATA_FTACCESS) {
		data->ftLastAccessTime.dwLowDateTime = ft->dwLowDateTime;
		data->ftLastAccessTime.dwHighDateTime = ft->dwHighDateTime;
	}

}
void __Win32FindDataftSync(WIN32_FIND_DATA *data, DWORD ftField) {
	// sync timefields based on one timefield
	// this is stupid. would be much simpler with asm
	FILETIME *ft = NULL;
	switch (ftField) {
		case W32FDATA_FTCREATE: ft = &(data->ftCreationTime); break;
		case W32FDATA_FTMODIFY: ft = &(data->ftLastWriteTime); break;
		case W32FDATA_FTACCESS: ft = &(data->ftLastAccessTime); break;
	}
	if (ft) __Win32FindDataftSet(data, ft, ~ftField);
}


#define dot1dir(s) (s && (s[0]==tDot) && (s[1]==tNul))
#define dot2dir(s) (s && (s[0]==tDot) && (s[1]==tDot) && (s[2]==tNul))
#define dotdir(s) (s && (s[0]==tDot) && (s[1]==tNul || (s[1]==tDot && s[2]==tNul)))
#define ndotdir(s) (s && (s[0]!=tDot || (s[1]!=tNul && s[1]!=tDot) && s[2]!=tNul))

#define MAXPATH MAX_PATH
int _procCreateFile(TCHAR * fn, WIN32_FIND_DATA *data, DWORD opts) {
	HANDLE fh;
	DWORD ff = FILE_ATTRIBUTE_NORMAL | FILE_FLAG_NO_BUFFERING | FILE_FLAG_OVERLAPPED;

	if CANT_CREATE { PRINTF1p("+ %s -create -n\n", fn); return 1; }
	if NOT_QUIET PRINTF1p("Creating \"%s\" ", fn);

	if OPTS_DOES(FILES) {
		if NOT_QUIET PRINTF("-file ");
		fh = CreateFile(fn, GENERIC_READ|GENERIC_WRITE, 7, NULL, OPEN_ALWAYS, ff, NULL);
		if HANDLE_ISBAD(fh) return NOT_VERYQUIET & _showerr(fn);
		CloseHandle(fh);
	}
	else {
		if NO_DIRS { PRINTF("-nodirs\n"); return 0; }
		if NOT_QUIET PRINTF("-directory ");
		if (!CreateDirectory(fn, NULL)) return NOT_VERYQUIET & _showerr(fn);
	}
	if NOT_QUIET PRINTF("created\n");

	fh = FindFirstFile(fn, data);
	if HANDLE_ISBAD(fh) return 0;
	FindClose(fh);

	return 1;
}

int isValidFileName(TCHAR * fn) {
	size_t k;
	TCHAR* InvalidPathChars = _T("<>*?/\\|:\"");

	TCHAR *p = STRRCHR(fn, tBsl);
	if (!p || !*p) return 0; else p++;

	k = STRCSPN(p, InvalidPathChars);

#ifdef DEBUG3
	TRACE3("k = %d, p = \"%s\"\n", k, p);
#endif
	// check for alldots
	if (k < STRLEN(p)) return 0;
	if (*p != tDot) return 1;
	while (*p && (*p == tDot)) p++;

	return (*p);
}

//_getCurrentFiletime(FILETIME *ft)
//{	SYSTEMTIME st; GetSystemTime(&st); SystemTimeToFileTime(&st, ft); }

#define FA_ISDIR(a) (a & FILE_ATTRIBUTE_DIRECTORY)
#define FA_ISFILE(a) ((a & FILE_ATTRIBUTE_DIRECTORY) == 0)
#define FA_ISLINK(a) (a & FILE_ATTRIBUTE_REPARSE_POINT)
#define FA_ISNOTLINK(a) ((a & FILE_ATTRIBUTE_REPARSE_POINT) == 0)

int seek(TCHAR *fn, FILETIME *ftime, DWORD opts);

int recurse(TCHAR *fpn, FILETIME *ft, DWORD opts) {
	WIN32_FIND_DATA data;
	TCHAR cPATH[MAXPATH];
	HANDLE fh;
	DWORD atr;
	TCHAR *cf, *cp, *dfn, *cglob = _T("*.*");
	int len, ctr = 0, more = 1;

	if (NOT_RECURSIVE || CAN_CREATE) return 0;
	ctr = 0;

	STRCPY(cPATH, fpn);

	if(cp = STRRCHR(cPATH, tBsl)) cp++; else return 0;; // cp after last DIRSEP

	cf = fpn + (cp - cPATH); // len = cp - cPATH;
	STRCPY(cp, cglob);


	fh = FindFirstFile(cPATH, &data);
	if (fh == INVALID_HANDLE_VALUE) { return _showerr(cPATH); } //something very bad has happened
	while (more) {
		dfn = data.cFileName;
		atr = data.dwFileAttributes;
		if (FA_ISDIR(atr) && FA_ISNOTLINK(atr) && ndotdir(dfn)) {
			len = STRLEN(dfn); // get new/found data.filename length
			STRCPY(cp, dfn);   // replace glob with data.filename
			cp[len] = tNul;    // add trailing backslash
			if NOT_QUIET
				PRINTF1p("\nDIVING subdir: %s\n", cPATH);
			cp[len] = tBsl;    // add trailing backslash
			STRCPY(cp + len + 1, cf); // append original filename
			ctr += seek(cPATH, ft, opts);
		}
		more = FindNextFile(fh, &data);
	}
	FindClose(fh);
	return ctr;
}

int seek(TCHAR *fn, FILETIME *ftime, DWORD opts) {
	WIN32_FIND_DATA data;
	TCHAR cPath[MAXPATH];
	HANDLE fh;
	DWORD att;
	TCHAR *cf, *ck, *cc, *ctail = _T("\\*.*");
	int err, len, ctr = 0, more = 1, proceed = 0;;

	if OPTS_DOES(DEPTH_FIRST) ctr += recurse(fn, ftime, opts);

	fh = FindFirstFile(fn, &data);
	/*
		if OPT_DIRS specified (OPT_FILES = 0)
		and files exist with the same specified argument dirs
		its not an error. just skip the files.
	*/
	if HANDLE_ISOK(fh) {
		STRCPY(cPath, fn);
		if (cc = STRRCHR(cPath, tBsl)) cc++; // cc after last DIRSEP
		else { FindClose(fh); return _showerr(cPath); } //something very bad has happened

		while (more) {
			cf = data.cFileName;
			len = strlen(cf);
			ck = (TCHAR*)STRCPY(cc, cf) + len; // ck at the terminating \0

			att = data.dwFileAttributes;
			if ((FA_ISDIR(att) && OPTS_DOES(DIRS)) || (FA_ISFILE(att) && OPTS_DOES(FILES))) {
				if NO_EXEC
					// this actually less relistic, timedate maybe
					// doesn't have to be modified (nop)
				{ ctr++; PRINTF1p("%s -n\n", cPath); }
				else
					ctr += _procfile(cPath, ftime, &data, opts);
			}
			//else // not processed (different target: dirs or files)
			//	if NOT_QUIET PRINTF1p("%s /skip\n", cPath);
			//gimmemore:
			more = FindNextFile(fh, &data);
		}
		FindClose(fh);
	}

	else { //if (fh == INVALID_HANDLE_VALUE) {
		err = GetLastError();
		//if NOT_QUIET _showerr(fn); else
		if (err != 2) return NOT_VERYQUIET & _showerr(fn);
		//if (!isValidFileName(fn)) return NOT_VERYQUIET & DTERR1p(DTERR_INV_PATHNAME, fn);
		if (isValidFileName(fn))
			if CAN_CREATE
				if NO_EXEC
					PRINTF1p("+ %s -created -n\n", fn);
				else
					if (_procCreateFile(fn, &data, opts))
						if (USING_REFTIME)
							ctr += _procfile(fn, ftime, &data, opts);

	}

	if NOT_DEPTHFIRST ctr += recurse(fn, ftime, opts);

	return ctr;
}

//int _procFindFirst(TCHAR * fn, FILETIME * ftime, DWORD opts) {
//	WIN32_FIND_DATA data;
//	TCHAR cPath[MAXPATH];
//	HANDLE fh;
//	DWORD att;
//	TCHAR *cf, *ck, *cc, *ctail = _T("\\*.*");
//	int err, len, ctr = 0, more = 1, proceed = 0;;
//
//	if (fn) return seek(fn, ftime, opts);
//	else return 0;
//
//	fh = FindFirstFile(fn, &data);
//
//	if (fh == INVALID_HANDLE_VALUE) {
//		// file or dirs will be created here
//		err = GetLastError(); //if (err != 2) return _showerr(fn);
//		if ((err != 2) || CANT_CREATE) return _showerr(fn);
//		if (!isValidFileName(fn)) return DTERR1p(DTERR_INV_PATHNAME, fn);
//		if (opts & OPT_NOEXEC) { PRINTF1p("+ %s -created -n\n", fn); return 1; }
//		if (!_procCreateFile(fn, &data, opts)) return 0;
//		if (!USING_REFTIME) return 1;
//		return _procfile(fn, ftime, &data, opts);
//	}
//
//	STRCPY(cPath, fn);
//	cc = STRRCHR(cPath, tBsl) +1; // cc after last DIRSEP
//
//	while (more) {
//		cf = data.cFileName;
//		len = strlen(cf);
//		ck = (TCHAR*)STRCPY(cc, cf) + len; // ck at the terminating \0
//		att = data.dwFileAttributes;
//		if ((att & FILE_ATTRIBUTE_DIRECTORY) &&
//			!(att & FILE_ATTRIBUTE_REPARSE_POINT) &&
//			(opts & OPT_RECURSIVE)) {
//				if ndotdir(cf) {
//					ctail = STRRCHR(fn, tBsl);
//					if (!ctail) ctail = fn;
//					STRCPY(ck, ctail);
//					if NOT_QUIET PRINTF1p("\nDIVING subdir: %s\n", cPath);
//					ctr += _procFindFirst(cPath, ftime, opts);
//					ck[0] = tNul; // cutback
//				}
//		}
//		if dotdir(cf) {
//			// println // if we want to process also dotdirs (\. and \..)
//
//		}
//		else {
//			if (att & FILE_ATTRIBUTE_DIRECTORY)
//				proceed = opts & OPT_DIRS;
//			else proceed = opts & OPT_FILES;
//			if (proceed)
//				if NO_EXEC
//					// but its actually less relistic, timedate maybe already the same / nop
//				{ ctr++; PRINTF1p("%s -n\n", cPath); }
//				else
//					ctr += _procfile(cPath, ftime, &data, opts);
//			else // not processed (different target: dirs or files)
//				if NOT_QUIET PRINTF1p("%s /skip\n", cPath);
//		}
//		more = FindNextFile(fh, &data);
//	}
//	FindClose(fh);
//	return ctr;
//}
//

#define FULLPATH _tfullpath BAAD!

int _help(TCHAR *arg0, TCHAR *msg) {
	SYSTEMTIME st;
	int i, k = 190900, len;
	int bday = 19091969;
	TCHAR ass[] = _T("/j*-ixlnt\0\0");
	TCHAR ch = tNul, *fn, *us = sBlank;
	bool ext = false;
	bool ext2 = false;
	if (!msg) return 0;
	ch = TOLOWER(msg[1]);
	if (ch != tVee && ch != tQst) return 0;
	//char * bar = "============================================";
	fn = _getBasename(arg0);
	PRINTF00("\n");
	PRINTF00("  Copyright(C) 2003-2019, PT SOFTINDO Jakarta\n");
	PRINTF00("  email: gm.dadang _at_ gmail.com\n");
	PRINTF00("  All rights reserved.\n"); //PRINTF00("\n");
	PRINTF00("\n");
	PRINTF3p("  %s version: %s, build: %0.3d\n", version_progname, version_number, version_build);
	PRINTF2p("  created: %s, last revised: %s\n", version_created, version_revised);
	//PRINTF00("  Revised: 2001.02.01\n");
	PRINTF00("\n");
	if (ch != tQst) return 0;
	len = STRLEN(ass);
	ch = tZro + (TCHAR)len;
	ext = msg[2] == tOne && msg[3] == ch;
	ext &= msg[4] == tZro && msg[5] == ch;
	//if (ext) { k = bday/100; for (i = 1; i < len; i++) { ass[i] += bday % 10; bday /= 10; } }
	ext2 = ext && (msg[6] == tPls) && (msg[7] == tPls);
	if (ext2) { k = bday/100; for (i = 1; i < len; i++) { ass[i] -= bday % 10; bday /= 10; } us = ass; }

	PRINTF00("  Synopsys:\n\tModify date and/or time of file, directory or symlink, recursively\n\n");
	PRINTF00("  Usage:\n");
	PRINTF1p("\t%s [ options ] files...\n", fn);
	PRINTF00("\n");
	PRINTF00("  Arguments:\n");
	PRINTF00("\tfiles (mandatory) : filename/mask to be processed (eg. C:\\*.*)\n");
	PRINTF00("\toptions (optional) : similar to those of UNIX touch utility\n");
	PRINTF00("\n");
	PRINTF00("\tNote for options:\n");
	PRINTF00("\t- must be prefixed with either single HYPHEN (-) or SLASH (/)\n");
	PRINTF00("\t- (mostly) case insensitive, -a is identical with /A\n");
	PRINTF00("\t- may be a toggle (switch) or may need additional argument\n");
	PRINTF00("\t- the later argument overrides or _toggles_ the previous one\n");
	if (ext)
		PRINTF00("\t  the switch turned off the second time you typed it in as argument\n\t  thus a switch can be turned on and off, and on and off and on..\n");
	PRINTF00("\n");
	//while ((c = getoptn(argn, args, _T("?acd:efhlmnr:st:vwxyzACD:EFHLMNR:ST:VWXYZ"))) != -1) {
	PRINTF00("\tOptions/switches are:\n");
	PRINTF00("\t-a, -m\t  change a:access or m:modification time (default: both)\n");
	if (ext)
		PRINTF1p("\t-%c\t  change creation time (Not too useful as you might think,\n\t\t  all apps and file operations use m:modification time)\n", _T('x'));
	PRINTF00("\t-c\t  DO create file if not exist (disables s:recursive)\n");
	PRINTF00("\t-d DATE   translate date string (see formats below) \n");
	PRINTF00("\t-e, -f\t  process only e:DIRS or f:FILES, or both (default)\n");
	PRINTF00("\t-h or -l  process SYMLINKS/reparse points, not the real files\n");
	PRINTF00("\t-n\t  test-mode, do not do actual modification\n");
	PRINTF00("\t-o, -q\t  show o:options/arguments or q:quiet (unless error)\n");//, the last given overrides each other\n");
	if (ext)
		PRINTF00("\t-Q\t  be very quiet while processing files, don't show error\n");//, the last given overrides each other\n");
	//PRINTF00("\t-q\t  quiet\n"); //, will shut up the previous -o\n");// (better be first before other switches)\n");
	PRINTF00("\t-r FILE   get reference datetime from file/dir: FILE\n");
	if (ext && (msg[6] == tPls))
		PRINTF00("\t\t  (honestly, this switch should have meant recursive)\n");
	PRINTF00("\t-s\t  recursive. process subdirs (disables c:create)\n");
	if (ext && (msg[6] == tPls))
		PRINTF00("\t-S\t  use depth-first traversal on recursive operation\n");
	PRINTF00("\t-t CTIME  use time in format [[[CC]YY]MMDD]hhmm[.ss]\n");
	//if (ext && (msg[6] == tPls))
	//	PRINTF00("\t-u\t  UNDO the devastating incorrect result in your life\n\t\t  (not implemented yet)\n");
	PRINTF00("\t-u uSTAMP lowercase u, use UNIX timestamp (seconds since 1970)\n");
	if (ext && (msg[6] == tPls))
		PRINTF00("\t-U mSTAMP UPPERCASE U, use MS/Excel timestamp (seconds since 1600)\n");
	if (ext)
		PRINTF00("\t\t  *STAMP can be prefixed by 0x for hex digits or 0 for octal\n");
	if (ext && (msg[6] == tPls))
		PRINTF00("\t\t  tbh, I don't think anybody ever use octal anymore\n");
	PRINTF00("\t-v\t  show version\n");
	PRINTF00("\t-y, -z\t  set only y:DATE or z:TIME, or both (default)\n");
	PRINTF00("\t--	  stop parsing next remaining arguments as opts/switches\n");
	if (ext) {
		PRINTF00("\n");
		printf(_T("\t%s%s  this help\n"), msg, strlen(msg) > 7 ? _T("") : _T("\t") );
		GetLocalTime(&st);
	}
	else {
		//PRINTF00("\n");
		printf(_T("\t-?\t  %s\n"), "Help. Checkout for 1909 pp" );
	}
	if (ext2) {
		srand((unsigned int)time(NULL));
		for (i = 0; i < (rand() & 7); i++) rand();
		if (((st.wHour > 3) && (st.wHour < 23)) || (st.wMonth == 7 && st.wDay == 4)) us = sBlank;
		else if(rand() > (1 << 13)) us = sBlank; //printf("%.08X", k);

		PRINTF00("\n");
		PRINTF1p("\t-%c\t  modify all_time_fields (access, create, mod.) at once\n", tGrt);
		PRINTF1p("\t-%c a|c|m  use a:access c:creation m:modification time from the\n\t\t  target file itself (overrides -d and -t, obviously)\n", tEqu);
		//PRINTF1p("\t\t  (mutually exclussive / overrides -t and -d)\n", tEqu);
	}
	//PRINTF00("  Formats:\n");
	PRINTF00("\n");
	PRINTF00("\tDATETIME formats:\n\t(note that delimiter is _important_ for date/month/year order)\n");
	PRINTF1p("\t    mm/dd/yy OR mm/dd/yyyy AND/OR hh:mm:ss - US%s\n", us);
	PRINTF00("\t    yy.mm.dd OR yyyy.mm.dd AND/OR hh:mm:ss - ISO 8601\n");
	PRINTF00("\t    dd-mm-yy OR dd-mm-yyyy AND/OR hh:mm:ss - Europe/Aus/Asia\n");
	PRINTF2p("\t    - 2 digits year: %d - %d (32 bits UNIX last epoch)\n", 1900 + CENTURY_SHIFT + 1, 2000 + CENTURY_SHIFT);
	PRINTF00("\t    - \"DATE + TIME\" must be delimited by exactly 1 space/tab\n");
	PRINTF00("\n");
	PRINTF00("\tCTIME fields:\n");
	PRINTF00("\t   CC YY MMDD hhmm .ss\n");
	PRINTF00("\t   - required fields: hhmm\n");
	PRINTF00("\t   - unspecified fields will be set equal to current time\n");
	//PRINTF00("\t   \n");
	PRINTF00("\n");
	PRINTF00("  Return code:\n");
	PRINTF00("\tnumber of files successfully processed set in ERRORLEVEL\n");
	//PRINTF00("\n");
	//PRINTF00("Press any key to continue..\n");
	//PRINTF1p("  %s\n",bar);
	//_printerrCodes();
	//PRINTF00("\n");
	//PRINTF00("\n");
	//PRINTF00("  Copyright(C) 2003-2009, PT SOFTINDO, Jakarta\n");
	//PRINTF00("  email: aa _at_ softindo.net\n");
	//PRINTF00("  All rights reserved.\n");	//PRINTF00("\n");
	//getchar();
	//PRINTF00("\n");
	//PRINTF1p("%s\n", msg);
	return 0;
}

int getoptn(int argc, TCHAR *argv[], TCHAR *optstring)
{
	static TCHAR *next = NULL;
	TCHAR c, *cp;

	if (!optind) next = NULL;
	optarg = NULL;

	if (!next || !*next) {
		if (!optind) optind++;

#define OCNEQ(c) (argv[optind][0] != _T(c))
		if (optind >= argc || (OCNEQ('-') && OCNEQ('/')) || !argv[optind][1]) {
			optarg = NULL;
			if (optind < argc) optarg = argv[optind];
			return -1;
		}
#undef OCNEQ

		if (STRCMP(argv[optind], _T("--")) == 0) {
			optind++;
			optarg = NULL;
			if (optind < argc) optarg = argv[optind];
			return -1;
		}

		next = argv[optind];
		next++; // skip past -
		optind++;
	}

	c = *next++;
	cp = STRCHR(optstring, c);

	if (!cp || c == _T(':')) return _T('?');

	cp++;
	if (*cp == _T(':')) {
		if (*next != _T('\0'))
		{ optarg = next; next = NULL; }
		else if (optind < argc)
		{ optarg = argv[optind]; optind++; }
		else
			return _T('?');
	}

	return c;
}

// ******** used by main only **********************************
__int64 getRefFileDate(TCHAR * fn, DWORD opts) {
	__int64 ret = 0;
	FILETIME ft; //ULARGE_INTEGER L;
#ifdef DEBUG3
	FILETIME ftC, ftA;
#endif
	HANDLE fh; //BY_HANDLE_FILE_INFORMATION info;
	DWORD ff = FILE_ATTRIBUTE_NORMAL | FILE_FLAG_NO_BUFFERING | \
		FILE_FLAG_OVERLAPPED | FILE_FLAG_BACKUP_SEMANTICS;
	if (opts && OPT_LINKS) ff |= FILE_FLAG_OPEN_REPARSE_POINT;
	fh = CreateFile(fn, GENERIC_READ, 7, NULL, OPEN_EXISTING, ff, NULL);

#ifdef DEBUG3
	printf("\n");
	__PRN__
		PRINTF1p("DBG3| Getting refDate from: \"%s\"\n", fn);
#endif
	if HANDLE_ISBAD(fh)
		return NOT_VERYQUIET & _shower2(_T("Failed to get refDate from: "), fn);

	//if(GetFileInformationByHandle (fh, &info))
	//	ret = int64OfFT(info.ftLastWriteTime);
#ifdef DEBUG3
	if(!GetFileTime(fh, &ftC, &ftA, &ft))
#else
	if(!GetFileTime(fh, NULL, NULL, &ft))
#endif
		return NOT_VERYQUIET & _shower2(_T("Failed to get refDate from: "), fn);
	CloseHandle(fh);

	ret = int64OfFT(ft);

#ifdef DEBUG3
	__PRN__
	printf("refDate| -- done getting refDate from: \"%s\"\n", fn);
	printf("refDate| -- return value: %.016I64x (%I64d)\n", ret, ret); // 0167c8c0:96e52080
	printf("rCreate| "); PRINTxFT(&ftC);
	printf("rAccess| "); PRINTxFT(&ftA);
	printf("rsWrite| "); PRINTxFT(&ft);
#endif

	return ret;
}

// ******** main ***********************************************
// CAUTION: This contains a harsh word, but harmless nonetheless.
int main(int argn, TCHAR * args[]) {
	int c, i;//, clen;
	FILETIME fTime; SYSTEMTIME st;
	TCHAR ch, *cp, fPath[MAXPATH];
	int ctr;
	DWORD opts = 0;
	DWORD opfi = 0; //OPT_DIRS | OPT_FILES;
	DWORD optm = 0; //OPT_FILETIME | OPT_FILEDATE;
	DWORD opwr = 0; //OPT_WTIME;
	DWORD opeq = 0;
	TCHAR * try = _T("Try -? for more information");
	TCHAR * e = NULL;

	bool broken = false;
	__int64 got = 0, TIME2SET = 0;
	ULARGE_INTEGER u;

	GetSystemTime(&st); //GetLocalTime(&st);
	if(!SystemTimeToFileTime(&st, &fTime))
		return CVTERR(CVTERR_SYS2FTIME); // GOBLOG SIAH	return SHOWERR("Conversion error:1");

	//TIME2SET = ((__int64)fTime.dwHighDateTime << 32) | fTime.dwLowDateTime;
	u.LowPart = fTime.dwLowDateTime;
	u.HighPart = fTime.dwHighDateTime;
	TIME2SET = u.QuadPart;

	got = -1; // use current time
	while ((c = getoptn(argn, args, _T(">acd:efhlmnoqr:st:u:vxyz=:ACD:EFHLMNOQR:ST:U:VXYZ"))) != -1) {
		ch = args[optind-1][1];
		switch (TOLOWER(c)) {
			case _T('a'): opwr ^= OPT_ATIME; break;
			case _T('m'): opwr ^= OPT_WTIME; break;
			case _T('x'): opwr ^= OPT_CTIME; break;
			case _T('>'): opwr = opwr == OPT_XTIME_ALL ? 0 : OPT_XTIME_ALL; break;

			case _T('n'): opts ^= OPT_NOEXEC; break;
			case _T('c'): opts ^= OPT_CREATE;
				if (opts & OPT_CREATE) opts &= ~OPT_RECURSIVE;
				break;
			case _T('s'): opts ^= OPT_RECURSIVE;
				if (opts & OPT_RECURSIVE) {
					opts &= ~OPT_CREATE;
					if (c == _T('S')) opts |= OPT_DEPTH_FIRST;
					else opts &= ~OPT_DEPTH_FIRST;
				}
				break;
			case _T('t'): got = parseTimeStamp(optarg); break;
			case _T('u'): got = parseTimeEpoch(optarg, c); break;
			case _T('d'): got = parseDateTime(optarg); break;
			case _T('l'):
			case _T('h'): opts ^= OPT_LINKS; break;
			//case _T('x'): opts ^= OPT_DEPTH_FIRST; break;
			case _T('y'): optm ^= OPT_FILEDATE; break;
			case _T('z'): optm ^= OPT_FILETIME; break;

			case _T('e'): opfi ^= OPT_DIRS; break;
			case _T('f'): opfi ^= OPT_FILES; break;
			case _T('o'): opts ^= OPT_SHOWOPTS; break;
			case _T('q'): opts ^= OPT_QUIET;
				if (c == _T('Q')) opts ^= OPT_VERYQUIET;
				if (opts & OPT_VERYQUIET) opts |= OPT_QUIET;
				if (opts & OPT_QUIET) opts &= ~OPT_SHOWOPTS;
				break;
			case _T('r'): got = getRefFileDate(optarg, opts); break;
			case _T('='): // this is choice not mask
				if (optarg && *optarg && !optarg[1]) {
					got = 0;
					switch(TOLOWER(*optarg)) {
						case _T('c'): opeq = OPT_USE_CTIME; break;
						case _T('m'): opeq = OPT_USE_WTIME; break;
						case _T('a'): opeq = OPT_USE_ATIME; break;
					}
				}
				if(opeq) {got = -1; break; }
			case _T('?'): if (ch != tQst) PRINTF1p("Malformatted switch: %s\n", args[optind-1]);
			case _T('v'): got = 0; return _help(args[0], args[optind-1]); break;
			default: printf(_T("*** Unimplemented yet: %c %s\n"), c, optarg);
		}
		if (!got) break;
	}
#ifdef DEBUG1
	__PRN__
		printf(_T("-- ret: %.016I64x (%I64d)\n"), TIME2SET, TIME2SET); // 0167c8c0:96e52080
	printf(_T("-- got: %.016I64x (%I64d)\n"), got, got); // 0167c8c0:96e52080
#endif

	// copy any values (inc. zero), except -1.
	if (~got) {
		TIME2SET = got;
		opeq = OPT_USE_REFTIME;
	}

#ifdef DEBUG1
	__PRN__
		printf(_T("-- ret: %.016I64x (%I64d)\n"), TIME2SET, TIME2SET); // 0167c8c0:96e52080
	printf(_T("-- got: %.016I64x (%I64d)\n"), got, got); // 0167c8c0:96e52080
#endif

	if (!opfi) opfi = OPT_DIRS | OPT_FILES;
	if (!optm) optm = OPT_FILETIME | OPT_FILEDATE;
	if (!opwr) opwr = OPT_ATIME | OPT_WTIME;
	//if (!opeq) opeq = OPT_USE_CURTIME;

	if USING_TIMEFIELDS(opeq)
		switch FTIME_USED(opeq) {
			case OPT_USE_CTIME: opwr &= ~OPT_CTIME; break;
			case OPT_USE_WTIME: opwr &= ~OPT_WTIME; break;
			case OPT_USE_ATIME: opwr &= ~OPT_ATIME; break;
	}

	opts = opts | opfi | optm | opwr | opeq;

	//	if (opts & OPT_SHOWOPTS) _ShowOff(opts);
	//if (opts & OPT_RECURSIVE) { opts |= OPT_NOEXEC; opts &= ~OPT_CREATE; }

	//_getLocalDiff();
	ctr = 0;
	if (argn > optind) {
		//println;
		if (TIME2SET) {
			//printf("***\nProcess remaining args..\n");
			//	//int64toft(TIME2SET, &ft); //kampret kelewat!!!
			//	//fTime.dwLowDateTime = TIME2SET;	fTime.dwHighDateTime = TIME2SET shr 32;

			u.QuadPart = TIME2SET;
			fTime.dwLowDateTime = u.LowPart;
			fTime.dwHighDateTime = u.HighPart;

#ifdef DEBUG1
			printf("Setting date to "); PRINTxFT(&fTime);
			println;
			printf("argc:%d optind:%d\n", argn, optind);
#endif
			GetCurrentDirectory(MAXPATH, (LPSTR)fPath);
			StartDir = fPath;
			//clen = STRLEN(fPath);
			//printf(_T("sizeof fPath: %d, length: %d\n"), sizeof(fPath), clen);
			for (i = optind; i < argn; i++) {
				//FULLPATH(fPath, args[i], MAXPATH);
				GetFullPathName(args[i], MAXPATH, fPath, NULL);
				// // actually not worth! should use standard glob (*) instead
				// // but otherwise . dir will be normalized as curdir name
				// // and might give undesirable result on recursive operation
				// // (affect only subdir with the same name with curdir, when
				// // actually user need to process ALL subdirs)
				// // ----
				// // damn. they give the same result anyway
				// if dot1dir(args[1]) {
				// 	clen = STRLEN(fPath);
				// 	fPath[clen] = tBsl;
				// 	fPath[clen+1] = tDot;
				// 	fPath[clen+2] = tNul;
				// }
				//if NOT_QUIET PRINTF2p("\nProcessing filemask %d: \"%s\"\n", i-optind+1, args[i]);
				ctr += seek(fPath, &fTime, opts);
			}

		}
		else
			e = _T("Invalid date/time. Make sure you're not put -t in place of -d\n%s\n");

	}
	else
		e = _T("Missing file target. %s\n");

#ifdef DEBUG
	opts |= OPT_SHOWOPTS;
#endif
	if (opts & OPT_SHOWOPTS) {
		println;
		_ShowOff(opts);
		PRINTF("\nArguments: ");
		for (i = 1; i < argn; i++) {
			cp = args[i];
			while (*cp > tSPC && *cp != tGrt) cp++;
			if (*cp)
				printf("\"%s\" ", args[i]);
			else
				printf("%s ", args[i]);
		}
		println;
	}
	if (e) printf(e, try);
	else if NOT_VERYQUIET PRINTF1p("Done. %d objects found.\n", ctr);

	return ctr;
}

