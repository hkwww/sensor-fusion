/**
 * Copyright (C) 2018-2019  Sergey Morozov <sergey@morozov.ch>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef SENSOR_FUSION_CONSTANTVELOCITY_HPP
#define SENSOR_FUSION_CONSTANTVELOCITY_HPP


#include "definitions.hpp"
#include "../state_vector_views/CVStateVectorView.hpp"
#include "ProcessModel.hpp"

#include <ctime>


namespace ser94mor
{
  namespace sensor_fusion
  {
    using CVProcessModelBase = ProcessModel<CVStateVector, CVStateCovarianceMatrix, CVControlVector,
                                            CVProcessNoiseCovarianceMatrix, CVROStateVectorView, CVRWStateVectorView,
                                            PMKind::e_CV, kCVIsLinear>;

    /**
     * A concrete process model class for CV process model. The State vector for process model consists of
     *   [ px, py, vx, vy ].
     * The naming of matrices are taken from the
     * "Thrun, S., Burgard, W. and Fox, D., 2005. Probabilistic robotics. MIT press."
     */
    class CVProcessModel : public CVProcessModelBase
    {
    public:
      /**
       * Constructor.
       */
      CVProcessModel();

      /**
       * @param dt a difference between the current measurement timestamp and the previous measurement timestamp
       * @return a state transition matrix
       */
      CVStateTransitionMatrix A(double_t dt) const;

      /**
       * @return a control transition matrix
       */
      static CVControlTransitionMatrix B();

      /**
       * @param dt a difference between the current measurement timestamp and the previous measurement timestamp
       * @return a process covariance matrix
       */
      CVProcessCovarianceMatrix R(double_t dt) const;

      /**
       * Subtract one state vector from another.
       *
       * @param sv_1 a state vector to subtract from
       * @param sv_2 a state vector which to subtract
       *
       * @return a difference between two state vectors
       */
      static CVStateVector Subtract(const CVStateVector& sv_1, const CVStateVector& sv_2);

      /**
       * Sums two vectors.
       *
       * @param sv_1 a first state vector
       * @param sv_2 a second state vector
       *
       * @return a sum of two state vectors
       */
      static CVStateVector Add(const StateVector_type& sv_1, const StateVector_type& sv_2);

    private:
      CVStateTransitionMatrix state_transition_matrix_prototype_;
    };

  }
}


#endif //SENSOR_FUSION_CONSTANTVELOCITY_HPP
