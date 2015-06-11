#ifndef __CROSSANY_MACRO_H_
#define __CROSSANY_MACRO_H_

#define NS_CROSSANY_BEGIN namespace crossany {
#define NS_CROSSANY_END };
#define USE_NS_CROSSANY using namespace crossany;

#define NS_CROSSANY_UI_BEGIN namespace ui {
#define NS_CROSSANY_UI_END };
#define USE_NS_CROSSANY_UI using namespace crossany::ui;


#define CROSSANY_EXPORTS

#ifdef CROSSANY_EXPORTS
#define CROSSANY_API __declspec(dllexport)
#else
#define CROSSANY_API __declspec(dllimport)
#endif

#define X_VARP(varType, varName)\
protected: varType m##varName;\
public: virtual const varType get##varName(void) const {return (m##varName);};\
public: virtual void set##varName( const varType var){ (m##varName) = (varType)var;}; 

#define X_VAR_R(varType, varName)\
protected: varType m##varName;\
public: virtual const varType get##varName(void) const {return (m##varName);};


#endif