#ifndef __CROSSANY_COORDINATE_H_
#define __CROSSANY_COORDINATE_H_
#include "macro.h"

//NS_CROSSANY_BEGIN
namespace crossany{

	class CROSSANY_API pos2{
	public:
		pos2(){ x = 0; y = 0; };
		pos2(const double& _x, const double& _y){ x = _x; y = _y; };
		~pos2(){};
		double getx() const { return x; }
		double gety() const { return y; }
		double setx(const double& _x){ x = _x; return x; }
		double sety(const double& _y){ y = _y; return y; }
		void set(const double& _x, const double& _y){ x = _x; y = _y; };
		bool operator== (const pos2& _p) const{ return x == _p.x && y == _p.y; }
	private:
		double x, y;
	public:
		const static pos2 ZERO;
	};

	class CROSSANY_API size{
	public:
		size(){ w = 0; h = 0; };
		size(const double& _w, const double& _h){ w = _w; h = _h; };
		~size(){};
		double getw(){ return w; }
		double geth(){ return h; }
		double setw(const double& _w){ w = _w; return w; }
		double seth(const double& _h){ h = _h; return h; }
		void set(const double& _w, const double& _h){ w = _w; h = _h; };
		void set(const size& _size){ w = _size.w; h = _size.h; };
		bool operator== (const size& _s) const{ return w == _s.w && h == _s.h; };
	private:
		double w, h;
	public:
		const static size ZERO;
	};

	class CROSSANY_API rect{
	public:
		rect() : mpos(0,0),msize(0,0){};
		rect(const pos2& _pos, const size& _size) : mpos(_pos), msize(_size){};
		~rect(){};
		double getw(){ return msize.getw(); };
		double geth(){ return msize.geth(); };
		double getx0(){ return mpos.getx(); };  // (left,bottom)
		double gety0(){ return mpos.gety(); };
		double getx1(){ return mpos.getx(); }; 
		double gety1(){ return mpos.gety() + msize.geth(); };
		double getx2(){ return mpos.getx() + msize.getw(); }; 
		double gety2(){ return mpos.gety() + msize.geth(); };
		double getx3(){ return mpos.getx() + msize.getw(); };
		double gety3(){ return mpos.gety(); };
		const pos2 getpos()const { return mpos; };
		const size getsize()const { return msize; };
		bool ptinrect(const pos2& _p){ if (_p.getx() >= getx0() && _p.getx() <= getx2() && _p.gety() >= gety0() && _p.gety() <= gety2()) return true; return false; };
		void set(const pos2& _pos, const size& _size){ mpos = _pos; msize = _size; };
		bool operator== (const rect& ar) const{ return mpos == ar.mpos && msize == ar.msize; };
	private:
		pos2 mpos;
		size msize;
	public:
		const static rect ZERO;
	};


}
//NS_CROSSANY_END

#endif