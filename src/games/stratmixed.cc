//
// This file is part of Gambit
// Copyright (c) 1994-2023, The Gambit Project (http://www.gambit-project.org)
//
// FILE: src/libgambit/mixed.cc
// Instantiation of template classes used in normal forms
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

#include "gambit.h"
#include "stratmixed.imp"

template class Gambit::MixedStrategyProfileRep<double>;
template class Gambit::MixedStrategyProfileRep<Gambit::Rational>;

template class Gambit::TableMixedStrategyProfileRep<double>;
template class Gambit::TableMixedStrategyProfileRep<Gambit::Rational>;

template class Gambit::TreeMixedStrategyProfileRep<double>;
template class Gambit::TreeMixedStrategyProfileRep<Gambit::Rational>;

template class Gambit::AggMixedStrategyProfileRep<double>;
template class Gambit::AggMixedStrategyProfileRep<Gambit::Rational>;

template class Gambit::BagentMixedStrategyProfileRep<double>;
template class Gambit::BagentMixedStrategyProfileRep<Gambit::Rational>;

template class Gambit::MixedStrategyProfile<double>;
template class Gambit::MixedStrategyProfile<Gambit::Rational>;
