/*==============================================================================

                                    O  F  E  L  I

                           Object  Finite  Element  Library

  ==============================================================================

   Copyright (C) 1998 - 2021 Rachid Touzani

   This file is part of OFELI.

   OFELI is free software: you can redistribute it and/or modify
   it under the terms of the GNU Lesser General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   OFELI is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU Lesser General Public License for more details.

   You should have received a copy of the GNU Lesser General Public License
   along with OFELI. If not, see <http://www.gnu.org/licenses/>.

  ==============================================================================

          Definition of class 'FastMarching' for Fast Marching Method
                            for 2-D uniform grids

  ==============================================================================*/

#ifndef __FAST_MARCHING_2DG_H
#define __FAST_MARCHING_2DG_H

#include "equations/Equa.h"
#include "equations/interface/FMHeap.h"
#include "mesh/Grid.h"
#include "linear_algebra/Vect.h"
#include "util/util.h"

/*!
 * \file FastMarching2DG.h
 * \brief Fast Marching Method for 2-D uniform grids
 */

namespace OFELI {
/*!
 *  \addtogroup OFELI
 *  @{
 */

/*!
 * \class FastMarching2DG
 * \brief class for the fast marching algorithm on 2-D uniform grids
 *
 * \details This class implements the Fast Marching method to solve
 * the eikonal equation in a 2-D uniform grid.
 * In other words, the class solves the partial differential equation
 *    |&nabla;T|F = 1
 * with T = 0 on the interface, where \c F is the velocity 
 */

class FastMarching2DG : virtual public Equa
{

 public:

   using Equa::_u;
   using Equa::_v;
   using Equa::_b;

/*!
 * \brief Default Constructor
 * \details Initializes to default value grid data
 */
    FastMarching2DG();

/*!
 * \brief Constructor using grid data
 * \details Constructor using Grid instance
 * \param [in] g Instance of class Grid
 * \param [in] T Vector containing the on input an initialization of the distance function and once
 * the function \c run is invoked the distance at grid nodes.
 * The initialization vector must use the following rules:
 * <ul>
 *    <li>The solution must be supplied at all grid points in the vicinity of the interface(s).
 *    <li>All other grid nodes must have the value \c INFINITY wth positive value if the node is in an outer
 *        domain and negative if it is in an inner domain
 * </ul>
 */
    FastMarching2DG(const Grid&   g,
                    Vect<real_t>& T);

/*!
 * \brief Constructor
 * \details Constructor using Grid instance and propagation speed
 * \param [in] g Instance of class Grid
 * \param [in] T Vector containing the on input an initialization of the distance function and once
 * the function \c run is invoked the distance at grid nodes.
 * The initialization vector must use the following rules:
 * <ul>
 *    <li>The solution must be supplied at all grid points in the vicinity of the interface(s).
 *    <li>All other grid nodes must have the value \c INFINITY wth positive value if the node is in an outer
 *        domain and negative if it is in an inner domain
 * </ul>
 * \param [in] F Vector containing propagation speed at grid nodes
 */
    FastMarching2DG(const Grid&   g,
                    Vect<real_t>& T,
                    Vect<real_t>& F);

/// \brief Destructor
    ~FastMarching2DG();

/**
 * @brief Define grid and solution vector
 * @details This function is to be used if the default constructor has been used
 * @param [in] g Instance of class Grid
 * @param [in] T Vector containing the on input an initialization of the distance function and once
 * the function \c run is invoked the distance at grid nodes.
 * The initialization vector must use the following rules:
 * <ul>
 *    <li>The solution must be supplied at all grid points in the vicinity of the interface(s).
 *    <li>All other grid nodes must have the value \c INFINITY wth positive value if the node is in an outer
 *        domain and negative if it is in an inner domain
 * </ul>
 */
    void set(const Grid&   g,
             Vect<real_t>& T);

/**
 * @brief Define grid, solution vector and prppagation speed
 * @details This function is to be used if the default constructor has been used
 * @param [in] g Instance of class Grid
 * @param [in] T Vector containing the on input an initialization of the distance function and once
 * the function \c run is invoked the distance at grid nodes.
 * The initialization vector must use the following rules:
 * <ul>
 *    <li>The solution must be supplied at all grid points in the vicinity of the interface(s).
 *    <li>All other grid nodes must have the value \c INFINITY wth positive value if the node is in an outer
 *        domain and negative if it is in an inner domain
 * </ul>
 * @param [in] F Vector containing propagation speed at grid nodes
 */
    void set(const Grid&   g,
             Vect<real_t>& T,
             Vect<real_t>& F);


/** \brief Execute Fast Marching Procedure
 *  \details Once this function is invoked, the vector \c phi in the constructor or in the member function \c set
 *  contains the solution.
 *  @return Return value:
 *  <ul>
 *    <li> = 0 if solution has been normally computed
 *    <li> != 0 An error has occurred
 *  </ul>
 */
    int run();

#ifndef DOXYGEN_SHOULD_SKIP_THIS
    void build() { }
#endif /* DOXYGEN_SHOULD_SKIP_THIS */

/// \brief Check consistency by computing the discrete residual.
/// \details This function returns residual error (||&nabla;u|<sup>2</sup>|F|<sup>2</sup>-1|)
    real_t getResidual();
  
 private:

   FMHeap _Narrow;
   Pt *_p, *_np;
   vector<Pt> _U;
   vector<Pt *> _neigs;
   const Grid *_theGrid;
   size_t _nx, _ny;
   real_t _hx, _hy;
   void init();
   real_t eval();
   size_t Neigs();
 
   size_t IJ(int i, int j) const { return (_ny+1)*(i-1)+j-1; }
 };

/*! @} End of Doxygen Groups */
} /* namespace OFELI */

#endif
