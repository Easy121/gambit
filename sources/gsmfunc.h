//#
//# FILE: gsmfunc.h -- definition of FuncDescObj, Function Descriptor Object
//#                    companion to GSM
//#
//# $Id$
//#




#ifndef GSMFUNC_H
#define GSMFUNC_H


//#include "gmisc.h"
#include "gsmincl.h"

#include "gstring.h"

//#include "portion.h"

class gOutput;

#define NO_DEFAULT_VALUE  ( (Portion*)  0 )
#define PARAM_NOT_FOUND   ( (int)      -1 )
#define PARAM_AMBIGUOUS   ( (int)      -2 )


#define PASS_BY_REFERENCE    true
#define PASS_BY_VALUE        false

#define AUTO_VAL_OR_REF      true

#define NON_LISTABLE         false
#define LISTABLE             true

#define NO_PREDEFINED_PARAMS ( (ParamInfoType*) 0 )



class FuncDescObj;
class CallFuncObj;

class gInteger;
class GSM;
class NewInstr;
class Portion;
class ListPortion;
class ReferencePortion;

template <class T> class gList;
template <class T> class RefCountHashTable;


class ParamInfoType
{
friend FuncDescObj;
friend CallFuncObj;
friend GSM;
  
private:
  gString      Name;
  PortionSpec  Spec;
  Portion*     DefaultValue;
  bool         PassByReference;

public:
  ParamInfoType( void );
  ParamInfoType( const ParamInfoType& param_info );
  ParamInfoType
    ( 
     const gString& name, 
     const PortionSpec& spec,
     Portion* default_value = NO_DEFAULT_VALUE, 
     const bool pass_by_ref = false
     );
  ~ParamInfoType();

  ParamInfoType& operator = ( const ParamInfoType& param_info );
};



class FuncInfoType
{
public:
  Portion*             (*FuncPtr)(Portion **);
  gList<NewInstr*>* FuncInstr;
  bool                 UserDefined;
  bool                 Listable;
  int                  NumParams;
  ParamInfoType*       ParamInfo;
};



class FuncDescObj
{
private:

  static RefCountHashTable< gList< NewInstr* >* > _RefCountTable;

  void _SetFuncInfo
    ( 
     const int f_index, 
     const int num_params,
     const bool listable
     );

  void _SetParamInfo
    ( 
     const int         f_index, 
     const int         index, 
     const gString&    name,
     const PortionSpec spec,
     Portion*          default_value,
     const bool        pass_by_reference
     );

protected:
  FuncDescObj( FuncDescObj& func );

  gString        _FuncName;
  int            _NumFuncs;
  FuncInfoType*  _FuncInfo;

  
public:
  FuncDescObj( const gString& func_name );
  virtual ~FuncDescObj();

  void SetFuncInfo
    (
     Portion*        (*func_ptr)(Portion**),
     const int       num_params = 0, 
     const ParamInfoType param_info[] = 0,
     const bool listable = LISTABLE
     );

  void SetFuncInfo
    (
     gList< NewInstr* >* func_instr,
     const int       num_params = 0, 
     const ParamInfoType param_info[] = 0,
     const bool listable = LISTABLE
     );

  void SetParamInfo
    ( 
     Portion*          (*func_ptr)(Portion**),
     const int         index, 
     const gString&    name,
     const PortionSpec spec,
     Portion*          default_value = NO_DEFAULT_VALUE,
     const bool        pass_by_reference = PASS_BY_VALUE
     );

  void SetParamInfo
    ( 
     gList< NewInstr* >* func_instr,
     const int         index, 
     const gString&    name,
     const PortionSpec spec,
     Portion*          default_value = NO_DEFAULT_VALUE,
     const bool        pass_by_reference = PASS_BY_VALUE
     );
  
  void SetParamInfo
    (
     Portion* (*func_ptr)(Portion**),
     const ParamInfoType param_info[]
     );
  
  void SetParamInfo
    (
     gList< NewInstr* >* func_instr,
     const ParamInfoType param_info[]
     );
  
  bool Combine( FuncDescObj* newfunc );

  gString FuncName ( void ) const;

  gList<gString> FuncList(void) const;
  void Dump(gOutput& f, int i) const;
  void Dump(gOutput& f) const;
};




class CallFuncObj : public FuncDescObj
{
 private:
  struct RunTimeParamInfoType
  {
    ReferencePortion* Ref;
    bool              Defined;
    bool              AutoValOrRef;
  };

  gOutput&              _StdOut;
  gOutput&              _StdErr;

  int                   _FuncIndex;
  int                   _NumParams;
  int                   _NumParamsDefined;
  Portion**             _Param;
  RunTimeParamInfoType* _RunTimeParamInfo;
  bool*                 _FuncMatch;
  int                   _CurrParamIndex;
  bool                  _ErrorOccurred;

  gString _ParamName( const int index ) const;

  static bool _TypeMatch( Portion* p, PortionSpec ExpectedSpec, bool Listable);

  static bool _ListDimMatch( ListPortion* p1, ListPortion* p2 );
  static bool _ListNestedCheck( Portion* p, const ParamInfoType& info );

  static void _ErrorMessage
    (
     gOutput& s,
     const int error_num, 
     const long& num1 = 0,
     const gString& str1 = "",
     const gString& str2 = "",
     const gString& str3 = "",
     const gString& str4 = ""
     );

 public:
  CallFuncObj( FuncDescObj* func, gOutput& s_out, gOutput& s_err );
  ~CallFuncObj();

  int         NumParams ( void ) const;
  bool        SetCurrParamIndex ( const gString& param_name );

  bool  SetCurrParam ( Portion* param, bool auto_val_or_ref = false );

  void        SetErrorOccurred ( void );

  ReferencePortion* GetParamRef ( int index ) const;

  Portion* CallFunction      ( GSM*, Portion** param );
  Portion* CallListFunction  ( GSM*, Portion** ParamIn );

  void Dump(gOutput& f) const;
};



#endif  // GSMFUNC_H


