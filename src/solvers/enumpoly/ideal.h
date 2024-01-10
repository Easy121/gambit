//
// This file is part of Gambit
// Copyright (c) 1994-2024, The Gambit Project (http://www.gambit-project.org)
//
// FILE: src/tools/enumpoly/ideal.h
// Declaration of gIdeal
//
// This program is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation; either version 2 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program; if not, write to the Free Software
// Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
//

#ifndef IDEAL_H
#define IDEAL_H

#include "odometer.h"
#include "gpolylst.h"

/*
   By the Hilbert basis theorem, every ideal is generated by some finite
basis, and for computational purposes we essentially think of ideals
as bases.  There are some important operations, however, that differ
across the various bases generating a single ideal, and for this
reason we will have a separate basis class.  Operator == is defined
setwise -- computationally we sort the two bases and then compare
termwise.
   In class ideal operator == is defined in terms of the ideal generated.
Computationally two ideals agree if their ordered reduced Grobner bases are
the same.
 */

// ***********************
//      class gIdeal
// ***********************

template <class T> class gIdeal {
 private:
   const gSpace*      Space;
   const term_order*  order;
         gPolyList<T> basis;
   
 public:
  gIdeal(const gSpace *, const term_order *); // Null gIdeal constructor
  gIdeal(const gSpace *, const term_order *,
	      const Gambit::List< gPoly<T> *> &);
  gIdeal(const term_order *, const gPolyList<T> &);
  gIdeal(const gIdeal<T> &);

  ~gIdeal();

   // Operators
   gIdeal<T>& operator=(const gIdeal<T> &);

   bool      operator==(const gIdeal<T> &) const;
   bool      operator!=(const gIdeal<T> &) const;
   gIdeal<T> operator+ (const gIdeal<T> &) const;
   gIdeal<T> operator* (const gIdeal<T> &) const;

   // Information
   inline int               Dmnsn()            const { return Space->Dmnsn(); }
   inline const gSpace*     TheSpace()         const { return Space         ; }
   inline int               NoBasisElements()  const { return basis.Length(); }
   inline const term_order* Order()            const { return order; }
   inline gPolyList<T>      CanonicalBasis()   const { return basis; }
          gIdeal<T>         MonomialIdeal()    const;
          Gambit::List<exp_vect>   MonomialBasis()    const;
                // This returns a monomial basis of the ring of polynomial
                // functions on the variety V(I), where I is the given ideal.
                // It fails if the variety is not zero dimensional.
          bool              IsRoot(const Gambit::Vector<T>&) const;

   bool ZeroDimensional()    const;
   bool IsEntireRing()       const;
   bool Contains(gPoly<T> &) const;
};  

#endif //# IDEAL_H
