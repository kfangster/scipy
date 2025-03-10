/* File: minpack2module.c
 * This file is auto-generated with f2py (version:1.21.2).
 * f2py is a Fortran to Python Interface Generator (FPIG), Second Edition,
 * written by Pearu Peterson <pearu@cens.ioc.ee>.
 * Generation date: Thu Nov  4 16:35:04 2021
 * Do not edit this file directly unless you know what you are doing!!!
 */

#ifdef __cplusplus
extern "C" {
#endif

/*********************** See f2py2e/cfuncs.py: includes ***********************/
#include "Python.h"
#include <stdarg.h>
#include "fortranobject.h"
#include <string.h>

/**************** See f2py2e/rules.py: mod_rules['modulebody'] ****************/
static PyObject *minpack2_error;
static PyObject *minpack2_module;

/*********************** See f2py2e/cfuncs.py: typedefs ***********************/
typedef char * string;

/****************** See f2py2e/cfuncs.py: typedefs_generated ******************/
/*need_typedefs_generated*/

/********************** See f2py2e/cfuncs.py: cppmacros **********************/
\
#define FAILNULL(p) do {                                            \
    if ((p) == NULL) {                                              \
        PyErr_SetString(PyExc_MemoryError, "NULL pointer found");   \
        goto capi_fail;                                             \
    }                                                               \
} while (0)

#define STRINGMALLOC(str,len)\
    if ((str = (string)malloc(sizeof(char)*(len+1))) == NULL) {\
        PyErr_SetString(PyExc_MemoryError, "out of memory");\
        goto capi_fail;\
    } else {\
        (str)[len] = '\0';\
    }

#if defined(PREPEND_FORTRAN)
#if defined(NO_APPEND_FORTRAN)
#if defined(UPPERCASE_FORTRAN)
#define F_FUNC(f,F) _##F
#else
#define F_FUNC(f,F) _##f
#endif
#else
#if defined(UPPERCASE_FORTRAN)
#define F_FUNC(f,F) _##F##_
#else
#define F_FUNC(f,F) _##f##_
#endif
#endif
#else
#if defined(NO_APPEND_FORTRAN)
#if defined(UPPERCASE_FORTRAN)
#define F_FUNC(f,F) F
#else
#define F_FUNC(f,F) f
#endif
#else
#if defined(UPPERCASE_FORTRAN)
#define F_FUNC(f,F) F##_
#else
#define F_FUNC(f,F) f##_
#endif
#endif
#endif
#if defined(UNDERSCORE_G77)
#define F_FUNC_US(f,F) F_FUNC(f##_,F##_)
#else
#define F_FUNC_US(f,F) F_FUNC(f,F)
#endif

#define rank(var) var ## _Rank
#define shape(var,dim) var ## _Dims[dim]
#define old_rank(var) (PyArray_NDIM((PyArrayObject *)(capi_ ## var ## _tmp)))
#define old_shape(var,dim) PyArray_DIM(((PyArrayObject *)(capi_ ## var ## _tmp)),dim)
#define fshape(var,dim) shape(var,rank(var)-dim-1)
#define len(var) shape(var,0)
#define flen(var) fshape(var,0)
#define old_size(var) PyArray_SIZE((PyArrayObject *)(capi_ ## var ## _tmp))
/* #define index(i) capi_i ## i */
#define slen(var) capi_ ## var ## _len
#define size(var, ...) f2py_size((PyArrayObject *)(capi_ ## var ## _tmp), ## __VA_ARGS__, -1)

#define STRINGFREE(str) do {if (!(str == NULL)) free(str);} while (0)

#ifdef DEBUGCFUNCS
#define CFUNCSMESS(mess) fprintf(stderr,"debug-capi:"mess);
#define CFUNCSMESSPY(mess,obj) CFUNCSMESS(mess) \
    PyObject_Print((PyObject *)obj,stderr,Py_PRINT_RAW);\
    fprintf(stderr,"\n");
#else
#define CFUNCSMESS(mess)
#define CFUNCSMESSPY(mess,obj)
#endif

#ifndef max
#define max(a,b) ((a > b) ? (a) : (b))
#endif
#ifndef min
#define min(a,b) ((a < b) ? (a) : (b))
#endif
#ifndef MAX
#define MAX(a,b) ((a > b) ? (a) : (b))
#endif
#ifndef MIN
#define MIN(a,b) ((a < b) ? (a) : (b))
#endif

#define STRINGCOPYN(to,from,buf_size)                           \
    do {                                                        \
        int _m = (buf_size);                                    \
        char *_to = (to);                                       \
        char *_from = (from);                                   \
        FAILNULL(_to); FAILNULL(_from);                         \
        (void)strncpy(_to, _from, sizeof(char)*_m);             \
        _to[_m-1] = '\0';                                      \
        /* Padding with spaces instead of nulls */              \
        for (_m -= 2; _m >= 0 && _to[_m] == '\0'; _m--) {      \
            _to[_m] = ' ';                                      \
        }                                                       \
    } while (0)


/************************ See f2py2e/cfuncs.py: cfuncs ************************/
static int f2py_size(PyArrayObject* var, ...)
{
  npy_int sz = 0;
  npy_int dim;
  npy_int rank;
  va_list argp;
  va_start(argp, var);
  dim = va_arg(argp, npy_int);
  if (dim==-1)
    {
      sz = PyArray_SIZE(var);
    }
  else
    {
      rank = PyArray_NDIM(var);
      if (dim>=1 && dim<=rank)
        sz = PyArray_DIM(var, dim-1);
      else
        fprintf(stderr, "f2py_size: 2nd argument value=%d fails to satisfy 1<=value<=%d. Result will be 0.\n", dim, rank);
    }
  va_end(argp);
  return sz;
}

static int
double_from_pyobj(double* v, PyObject *obj, const char *errmess)
{
    PyObject* tmp = NULL;
    if (PyFloat_Check(obj)) {
        *v = PyFloat_AsDouble(obj);
        return !(*v == -1.0 && PyErr_Occurred());
    }

    tmp = PyNumber_Float(obj);
    if (tmp) {
        *v = PyFloat_AsDouble(tmp);
        Py_DECREF(tmp);
        return !(*v == -1.0 && PyErr_Occurred());
    }
    if (PyComplex_Check(obj))
        tmp = PyObject_GetAttrString(obj,"real");
    else if (PyBytes_Check(obj) || PyUnicode_Check(obj))
        /*pass*/;
    else if (PySequence_Check(obj))
        tmp = PySequence_GetItem(obj,0);
    if (tmp) {
        PyErr_Clear();
        if (double_from_pyobj(v,tmp,errmess)) {Py_DECREF(tmp); return 1;}
        Py_DECREF(tmp);
    }
    {
        PyObject* err = PyErr_Occurred();
        if (err==NULL) err = minpack2_error;
        PyErr_SetString(err,errmess);
    }
    return 0;
}

static int
string_from_pyobj(string *str,int *len,const string inistr,PyObject *obj,const char *errmess)
{
    PyArrayObject *arr = NULL;
    PyObject *tmp = NULL;
#ifdef DEBUGCFUNCS
fprintf(stderr,"string_from_pyobj(str='%s',len=%d,inistr='%s',obj=%p)\n",(char*)str,*len,(char *)inistr,obj);
#endif
    if (obj == Py_None) {
        if (*len == -1)
            *len = strlen(inistr); /* Will this cause problems? */
        STRINGMALLOC(*str,*len);
        STRINGCOPYN(*str,inistr,*len+1);
        return 1;
    }
    if (PyArray_Check(obj)) {
        if ((arr = (PyArrayObject *)obj) == NULL)
            goto capi_fail;
        if (!ISCONTIGUOUS(arr)) {
            PyErr_SetString(PyExc_ValueError,"array object is non-contiguous.");
            goto capi_fail;
        }
        if (*len == -1)
            *len = (PyArray_ITEMSIZE(arr))*PyArray_SIZE(arr);
        STRINGMALLOC(*str,*len);
        STRINGCOPYN(*str,PyArray_DATA(arr),*len+1);
        return 1;
    }
    if (PyBytes_Check(obj)) {
        tmp = obj;
        Py_INCREF(tmp);
    }
    else if (PyUnicode_Check(obj)) {
        tmp = PyUnicode_AsASCIIString(obj);
    }
    else {
        PyObject *tmp2;
        tmp2 = PyObject_Str(obj);
        if (tmp2) {
            tmp = PyUnicode_AsASCIIString(tmp2);
            Py_DECREF(tmp2);
        }
        else {
            tmp = NULL;
        }
    }
    if (tmp == NULL) goto capi_fail;
    if (*len == -1)
        *len = PyBytes_GET_SIZE(tmp);
    STRINGMALLOC(*str,*len);
    STRINGCOPYN(*str,PyBytes_AS_STRING(tmp),*len+1);
    Py_DECREF(tmp);
    return 1;
capi_fail:
    Py_XDECREF(tmp);
    {
        PyObject* err = PyErr_Occurred();
        if (err == NULL) {
            err = minpack2_error;
        }
        PyErr_SetString(err, errmess);
    }
    return 0;
}


/********************* See f2py2e/cfuncs.py: userincludes *********************/
/*need_userincludes*/

/********************* See f2py2e/capi_rules.py: usercode *********************/


/* See f2py2e/rules.py */
extern void F_FUNC(dcsrch,DCSRCH)(double*,double*,double*,double*,double*,double*,string,double*,double*,int*,double*,size_t);
extern void F_FUNC(dcstep,DCSTEP)(double*,double*,double*,double*,double*,double*,double*,double*,double*,int*,double*,double*);
/*eof externroutines*/

/******************** See f2py2e/capi_rules.py: usercode1 ********************/


/******************* See f2py2e/cb_rules.py: buildcallback *******************/
/*need_callbacks*/

/*********************** See f2py2e/rules.py: buildapi ***********************/

/*********************************** dcsrch ***********************************/
static char doc_f2py_rout_minpack2_dcsrch[] = "\
stp,f,g,task = dcsrch(stp,f,g,ftol,gtol,xtol,task,stpmin,stpmax,isave,dsave)\n\nWrapper for ``dcsrch``.\
\n\nParameters\n----------\n"
"stp : input float\n"
"f : input float\n"
"g : input float\n"
"ftol : input float\n"
"gtol : input float\n"
"xtol : input float\n"
"task : input string(len=60)\n"
"stpmin : input float\n"
"stpmax : input float\n"
"isave : in/output rank-1 array('i') with bounds (2)\n"
"dsave : in/output rank-1 array('d') with bounds (13)\n"
"\nReturns\n-------\n"
"stp : float\n"
"f : float\n"
"g : float\n"
"task : string(len=60)";
/* extern void F_FUNC(dcsrch,DCSRCH)(double*,double*,double*,double*,double*,double*,string,double*,double*,int*,double*,size_t); */
static PyObject *f2py_rout_minpack2_dcsrch(const PyObject *capi_self,
                           PyObject *capi_args,
                           PyObject *capi_keywds,
                           void (*f2py_func)(double*,double*,double*,double*,double*,double*,string,double*,double*,int*,double*,size_t)) {
    PyObject * volatile capi_buildvalue = NULL;
    volatile int f2py_success = 1;
/*decl*/

  double stp = 0;
  PyObject *stp_capi = Py_None;
  double f = 0;
  PyObject *f_capi = Py_None;
  double g = 0;
  PyObject *g_capi = Py_None;
  double ftol = 0;
  PyObject *ftol_capi = Py_None;
  double gtol = 0;
  PyObject *gtol_capi = Py_None;
  double xtol = 0;
  PyObject *xtol_capi = Py_None;
  string task = NULL;
  int slen(task);
  PyObject *task_capi = Py_None;
  double stpmin = 0;
  PyObject *stpmin_capi = Py_None;
  double stpmax = 0;
  PyObject *stpmax_capi = Py_None;
  int *isave = NULL;
  npy_intp isave_Dims[1] = {-1};
  const int isave_Rank = 1;
  PyArrayObject *capi_isave_tmp = NULL;
  int capi_isave_intent = 0;
  PyObject *isave_capi = Py_None;
  double *dsave = NULL;
  npy_intp dsave_Dims[1] = {-1};
  const int dsave_Rank = 1;
  PyArrayObject *capi_dsave_tmp = NULL;
  int capi_dsave_intent = 0;
  PyObject *dsave_capi = Py_None;
    static char *capi_kwlist[] = {"stp","f","g","ftol","gtol","xtol","task","stpmin","stpmax","isave","dsave",NULL};

/*routdebugenter*/
#ifdef F2PY_REPORT_ATEXIT
f2py_start_clock();
#endif
    if (!PyArg_ParseTupleAndKeywords(capi_args,capi_keywds,\
        "OOOOOOOOOOO|:minpack2.dcsrch",\
        capi_kwlist,&stp_capi,&f_capi,&g_capi,&ftol_capi,&gtol_capi,&xtol_capi,&task_capi,&stpmin_capi,&stpmax_capi,&isave_capi,&dsave_capi))
        return NULL;
/*frompyobj*/
  /* Processing variable stp */
    f2py_success = double_from_pyobj(&stp,stp_capi,"minpack2.dcsrch() 1st argument (stp) can't be converted to double");
  if (f2py_success) {
  /* Processing variable f */
    f2py_success = double_from_pyobj(&f,f_capi,"minpack2.dcsrch() 2nd argument (f) can't be converted to double");
  if (f2py_success) {
  /* Processing variable g */
    f2py_success = double_from_pyobj(&g,g_capi,"minpack2.dcsrch() 3rd argument (g) can't be converted to double");
  if (f2py_success) {
  /* Processing variable ftol */
    f2py_success = double_from_pyobj(&ftol,ftol_capi,"minpack2.dcsrch() 4th argument (ftol) can't be converted to double");
  if (f2py_success) {
  /* Processing variable gtol */
    f2py_success = double_from_pyobj(&gtol,gtol_capi,"minpack2.dcsrch() 5th argument (gtol) can't be converted to double");
  if (f2py_success) {
  /* Processing variable xtol */
    f2py_success = double_from_pyobj(&xtol,xtol_capi,"minpack2.dcsrch() 6th argument (xtol) can't be converted to double");
  if (f2py_success) {
  /* Processing variable task */
  slen(task) = 60;
  f2py_success = string_from_pyobj(&task,&slen(task),"",task_capi,"string_from_pyobj failed in converting 7th argument `task' of minpack2.dcsrch to C string");
  if (f2py_success) {
  /* Processing variable stpmin */
    f2py_success = double_from_pyobj(&stpmin,stpmin_capi,"minpack2.dcsrch() 8th argument (stpmin) can't be converted to double");
  if (f2py_success) {
  /* Processing variable stpmax */
    f2py_success = double_from_pyobj(&stpmax,stpmax_capi,"minpack2.dcsrch() 9th argument (stpmax) can't be converted to double");
  if (f2py_success) {
  /* Processing variable isave */
  isave_Dims[0]=2;
  capi_isave_intent |= F2PY_INTENT_INOUT;
  capi_isave_tmp = array_from_pyobj(NPY_INT,isave_Dims,isave_Rank,capi_isave_intent,isave_capi);
  if (capi_isave_tmp == NULL) {
    PyObject *exc, *val, *tb;
    PyErr_Fetch(&exc, &val, &tb);
    PyErr_SetString(exc ? exc : minpack2_error,"failed in converting 10th argument `isave' of minpack2.dcsrch to C/Fortran array" );
    npy_PyErr_ChainExceptionsCause(exc, val, tb);
  } else {
    isave = (int *)(PyArray_DATA(capi_isave_tmp));

  /* Processing variable dsave */
  dsave_Dims[0]=13;
  capi_dsave_intent |= F2PY_INTENT_INOUT;
  capi_dsave_tmp = array_from_pyobj(NPY_DOUBLE,dsave_Dims,dsave_Rank,capi_dsave_intent,dsave_capi);
  if (capi_dsave_tmp == NULL) {
    PyObject *exc, *val, *tb;
    PyErr_Fetch(&exc, &val, &tb);
    PyErr_SetString(exc ? exc : minpack2_error,"failed in converting 11st argument `dsave' of minpack2.dcsrch to C/Fortran array" );
    npy_PyErr_ChainExceptionsCause(exc, val, tb);
  } else {
    dsave = (double *)(PyArray_DATA(capi_dsave_tmp));

/*end of frompyobj*/
#ifdef F2PY_REPORT_ATEXIT
f2py_start_call_clock();
#endif
/*callfortranroutine*/
        (*f2py_func)(&stp,&f,&g,&ftol,&gtol,&xtol,task,&stpmin,&stpmax,isave,dsave,slen(task));
if (PyErr_Occurred())
  f2py_success = 0;
#ifdef F2PY_REPORT_ATEXIT
f2py_stop_call_clock();
#endif
/*end of callfortranroutine*/
        if (f2py_success) {
/*pyobjfrom*/
/*end of pyobjfrom*/
        CFUNCSMESS("Building return value.\n");
        capi_buildvalue = Py_BuildValue("dddy",stp,f,g,task);
/*closepyobjfrom*/
/*end of closepyobjfrom*/
        } /*if (f2py_success) after callfortranroutine*/
/*cleanupfrompyobj*/
  if((PyObject *)capi_dsave_tmp!=dsave_capi) {
    Py_XDECREF(capi_dsave_tmp); }
  }  /*if (capi_dsave_tmp == NULL) ... else of dsave*/
  /* End of cleaning variable dsave */
  if((PyObject *)capi_isave_tmp!=isave_capi) {
    Py_XDECREF(capi_isave_tmp); }
  }  /*if (capi_isave_tmp == NULL) ... else of isave*/
  /* End of cleaning variable isave */
  } /*if (f2py_success) of stpmax*/
  /* End of cleaning variable stpmax */
  } /*if (f2py_success) of stpmin*/
  /* End of cleaning variable stpmin */
    STRINGFREE(task);
  }  /*if (f2py_success) of task*/
  /* End of cleaning variable task */
  } /*if (f2py_success) of xtol*/
  /* End of cleaning variable xtol */
  } /*if (f2py_success) of gtol*/
  /* End of cleaning variable gtol */
  } /*if (f2py_success) of ftol*/
  /* End of cleaning variable ftol */
  } /*if (f2py_success) of g*/
  /* End of cleaning variable g */
  } /*if (f2py_success) of f*/
  /* End of cleaning variable f */
  } /*if (f2py_success) of stp*/
  /* End of cleaning variable stp */
/*end of cleanupfrompyobj*/
    if (capi_buildvalue == NULL) {
/*routdebugfailure*/
    } else {
/*routdebugleave*/
    }
    CFUNCSMESS("Freeing memory.\n");
/*freemem*/
#ifdef F2PY_REPORT_ATEXIT
f2py_stop_clock();
#endif
    return capi_buildvalue;
}
/******************************* end of dcsrch *******************************/

/*********************************** dcstep ***********************************/
static char doc_f2py_rout_minpack2_dcstep[] = "\
stx,fx,dx,sty,fy,dy,stp,brackt = dcstep(stx,fx,dx,sty,fy,dy,stp,fp,dp,brackt,stpmin,stpmax)\n\nWrapper for ``dcstep``.\
\n\nParameters\n----------\n"
"stx : input float\n"
"fx : input float\n"
"dx : input float\n"
"sty : input float\n"
"fy : input float\n"
"dy : input float\n"
"stp : input float\n"
"fp : input float\n"
"dp : input float\n"
"brackt : input int\n"
"stpmin : input float\n"
"stpmax : input float\n"
"\nReturns\n-------\n"
"stx : float\n"
"fx : float\n"
"dx : float\n"
"sty : float\n"
"fy : float\n"
"dy : float\n"
"stp : float\n"
"brackt : int";
/* extern void F_FUNC(dcstep,DCSTEP)(double*,double*,double*,double*,double*,double*,double*,double*,double*,int*,double*,double*); */
static PyObject *f2py_rout_minpack2_dcstep(const PyObject *capi_self,
                           PyObject *capi_args,
                           PyObject *capi_keywds,
                           void (*f2py_func)(double*,double*,double*,double*,double*,double*,double*,double*,double*,int*,double*,double*)) {
    PyObject * volatile capi_buildvalue = NULL;
    volatile int f2py_success = 1;
/*decl*/

  double stx = 0;
  PyObject *stx_capi = Py_None;
  double fx = 0;
  PyObject *fx_capi = Py_None;
  double dx = 0;
  PyObject *dx_capi = Py_None;
  double sty = 0;
  PyObject *sty_capi = Py_None;
  double fy = 0;
  PyObject *fy_capi = Py_None;
  double dy = 0;
  PyObject *dy_capi = Py_None;
  double stp = 0;
  PyObject *stp_capi = Py_None;
  double fp = 0;
  PyObject *fp_capi = Py_None;
  double dp = 0;
  PyObject *dp_capi = Py_None;
  int brackt = 0;
  PyObject *brackt_capi = Py_None;
  double stpmin = 0;
  PyObject *stpmin_capi = Py_None;
  double stpmax = 0;
  PyObject *stpmax_capi = Py_None;
    static char *capi_kwlist[] = {"stx","fx","dx","sty","fy","dy","stp","fp","dp","brackt","stpmin","stpmax",NULL};

/*routdebugenter*/
#ifdef F2PY_REPORT_ATEXIT
f2py_start_clock();
#endif
    if (!PyArg_ParseTupleAndKeywords(capi_args,capi_keywds,\
        "OOOOOOOOOOOO|:minpack2.dcstep",\
        capi_kwlist,&stx_capi,&fx_capi,&dx_capi,&sty_capi,&fy_capi,&dy_capi,&stp_capi,&fp_capi,&dp_capi,&brackt_capi,&stpmin_capi,&stpmax_capi))
        return NULL;
/*frompyobj*/
  /* Processing variable stx */
    f2py_success = double_from_pyobj(&stx,stx_capi,"minpack2.dcstep() 1st argument (stx) can't be converted to double");
  if (f2py_success) {
  /* Processing variable fx */
    f2py_success = double_from_pyobj(&fx,fx_capi,"minpack2.dcstep() 2nd argument (fx) can't be converted to double");
  if (f2py_success) {
  /* Processing variable dx */
    f2py_success = double_from_pyobj(&dx,dx_capi,"minpack2.dcstep() 3rd argument (dx) can't be converted to double");
  if (f2py_success) {
  /* Processing variable sty */
    f2py_success = double_from_pyobj(&sty,sty_capi,"minpack2.dcstep() 4th argument (sty) can't be converted to double");
  if (f2py_success) {
  /* Processing variable fy */
    f2py_success = double_from_pyobj(&fy,fy_capi,"minpack2.dcstep() 5th argument (fy) can't be converted to double");
  if (f2py_success) {
  /* Processing variable dy */
    f2py_success = double_from_pyobj(&dy,dy_capi,"minpack2.dcstep() 6th argument (dy) can't be converted to double");
  if (f2py_success) {
  /* Processing variable stp */
    f2py_success = double_from_pyobj(&stp,stp_capi,"minpack2.dcstep() 7th argument (stp) can't be converted to double");
  if (f2py_success) {
  /* Processing variable fp */
    f2py_success = double_from_pyobj(&fp,fp_capi,"minpack2.dcstep() 8th argument (fp) can't be converted to double");
  if (f2py_success) {
  /* Processing variable dp */
    f2py_success = double_from_pyobj(&dp,dp_capi,"minpack2.dcstep() 9th argument (dp) can't be converted to double");
  if (f2py_success) {
  /* Processing variable brackt */
    brackt = (int)PyObject_IsTrue(brackt_capi);
    f2py_success = 1;
  if (f2py_success) {
  /* Processing variable stpmin */
    f2py_success = double_from_pyobj(&stpmin,stpmin_capi,"minpack2.dcstep() 11st argument (stpmin) can't be converted to double");
  if (f2py_success) {
  /* Processing variable stpmax */
    f2py_success = double_from_pyobj(&stpmax,stpmax_capi,"minpack2.dcstep() 12nd argument (stpmax) can't be converted to double");
  if (f2py_success) {
/*end of frompyobj*/
#ifdef F2PY_REPORT_ATEXIT
f2py_start_call_clock();
#endif
/*callfortranroutine*/
        (*f2py_func)(&stx,&fx,&dx,&sty,&fy,&dy,&stp,&fp,&dp,&brackt,&stpmin,&stpmax);
if (PyErr_Occurred())
  f2py_success = 0;
#ifdef F2PY_REPORT_ATEXIT
f2py_stop_call_clock();
#endif
/*end of callfortranroutine*/
        if (f2py_success) {
/*pyobjfrom*/
/*end of pyobjfrom*/
        CFUNCSMESS("Building return value.\n");
        capi_buildvalue = Py_BuildValue("dddddddi",stx,fx,dx,sty,fy,dy,stp,brackt);
/*closepyobjfrom*/
/*end of closepyobjfrom*/
        } /*if (f2py_success) after callfortranroutine*/
/*cleanupfrompyobj*/
  } /*if (f2py_success) of stpmax*/
  /* End of cleaning variable stpmax */
  } /*if (f2py_success) of stpmin*/
  /* End of cleaning variable stpmin */
  } /*if (f2py_success) of brackt*/
  /* End of cleaning variable brackt */
  } /*if (f2py_success) of dp*/
  /* End of cleaning variable dp */
  } /*if (f2py_success) of fp*/
  /* End of cleaning variable fp */
  } /*if (f2py_success) of stp*/
  /* End of cleaning variable stp */
  } /*if (f2py_success) of dy*/
  /* End of cleaning variable dy */
  } /*if (f2py_success) of fy*/
  /* End of cleaning variable fy */
  } /*if (f2py_success) of sty*/
  /* End of cleaning variable sty */
  } /*if (f2py_success) of dx*/
  /* End of cleaning variable dx */
  } /*if (f2py_success) of fx*/
  /* End of cleaning variable fx */
  } /*if (f2py_success) of stx*/
  /* End of cleaning variable stx */
/*end of cleanupfrompyobj*/
    if (capi_buildvalue == NULL) {
/*routdebugfailure*/
    } else {
/*routdebugleave*/
    }
    CFUNCSMESS("Freeing memory.\n");
/*freemem*/
#ifdef F2PY_REPORT_ATEXIT
f2py_stop_clock();
#endif
    return capi_buildvalue;
}
/******************************* end of dcstep *******************************/
/*eof body*/

/******************* See f2py2e/f90mod_rules.py: buildhooks *******************/
/*need_f90modhooks*/

/************** See f2py2e/rules.py: module_rules['modulebody'] **************/

/******************* See f2py2e/common_rules.py: buildhooks *******************/

/*need_commonhooks*/

/**************************** See f2py2e/rules.py ****************************/

static FortranDataDef f2py_routine_defs[] = {
  {"dcsrch",-1,{{-1}},0,(char *)F_FUNC(dcsrch,DCSRCH),(f2py_init_func)f2py_rout_minpack2_dcsrch,doc_f2py_rout_minpack2_dcsrch},
  {"dcstep",-1,{{-1}},0,(char *)F_FUNC(dcstep,DCSTEP),(f2py_init_func)f2py_rout_minpack2_dcstep,doc_f2py_rout_minpack2_dcstep},

/*eof routine_defs*/
  {NULL}
};

static PyMethodDef f2py_module_methods[] = {

  {NULL,NULL}
};

static struct PyModuleDef moduledef = {
  PyModuleDef_HEAD_INIT,
  "minpack2",
  NULL,
  -1,
  f2py_module_methods,
  NULL,
  NULL,
  NULL,
  NULL
};

PyMODINIT_FUNC PyInit_minpack2(void) {
  int i;
  PyObject *m,*d, *s, *tmp;
  m = minpack2_module = PyModule_Create(&moduledef);
  Py_SET_TYPE(&PyFortran_Type, &PyType_Type);
  import_array();
  if (PyErr_Occurred())
    {PyErr_SetString(PyExc_ImportError, "can't initialize module minpack2 (failed to import numpy)"); return m;}
  d = PyModule_GetDict(m);
  s = PyUnicode_FromString("1.21.2");
  PyDict_SetItemString(d, "__version__", s);
  Py_DECREF(s);
  s = PyUnicode_FromString(
    "This module 'minpack2' is auto-generated with f2py (version:1.21.2).\nFunctions:\n"
"  stp,f,g,task = dcsrch(stp,f,g,ftol,gtol,xtol,task,stpmin,stpmax,isave,dsave)\n"
"  stx,fx,dx,sty,fy,dy,stp,brackt = dcstep(stx,fx,dx,sty,fy,dy,stp,fp,dp,brackt,stpmin,stpmax)\n"
".");
  PyDict_SetItemString(d, "__doc__", s);
  Py_DECREF(s);
  s = PyUnicode_FromString("1.21.2");
  PyDict_SetItemString(d, "__f2py_numpy_version__", s);
  Py_DECREF(s);
  minpack2_error = PyErr_NewException ("minpack2.error", NULL, NULL);
  /*
   * Store the error object inside the dict, so that it could get deallocated.
   * (in practice, this is a module, so it likely will not and cannot.)
   */
  PyDict_SetItemString(d, "_minpack2_error", minpack2_error);
  Py_DECREF(minpack2_error);
  for(i=0;f2py_routine_defs[i].name!=NULL;i++) {
    tmp = PyFortranObject_NewAsAttr(&f2py_routine_defs[i]);
    PyDict_SetItemString(d, f2py_routine_defs[i].name, tmp);
    Py_DECREF(tmp);
  }


/*eof initf2pywraphooks*/
/*eof initf90modhooks*/

/*eof initcommonhooks*/


#ifdef F2PY_REPORT_ATEXIT
  if (! PyErr_Occurred())
    on_exit(f2py_report_on_exit,(void*)"minpack2");
#endif
  return m;
}
#ifdef __cplusplus
}
#endif
