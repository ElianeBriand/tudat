/*    Copyright (c) 2010-2018, Delft University of Technology
 *    All rigths reserved
 *
 *    This file is part of the Tudat. Redistribution and use in source and
 *    binary forms, with or without modification, are permitted exclusively
 *    under the terms of the Modified BSD license. You should have received
 *    a copy of the license with this file. If not, please or visit:
 *    http://tudat.tudelft.nl/LICENSE.
 *
 */

#ifndef TUDAT_KALMAN_FILTER_H
#define TUDAT_KALMAN_FILTER_H

#include <limits>
#include <iostream>

#include <Eigen/Core>
#include <Eigen/Geometry>

#include <boost/bind.hpp>
#include <boost/function.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/make_shared.hpp>
#include <boost/lambda/lambda.hpp>

#include "Tudat/Mathematics/BasicMathematics/mathematicalConstants.h"
#include "Tudat/Mathematics/NumericalIntegrators/numericalIntegrator.h"
#include "Tudat/Mathematics/Statistics/randomVariableGenerator.h"

namespace tudat
{

namespace filters
{

//! Kalman Filter class.
/*!
 *  Base class for the set up and use of Kalman filters.
 *  \tparam IndependentVariableType Type of independent variable. Default is double.
 *  \tparam DependentVariableType Type of dependent variable. Default is double.
 */
template< typename IndependentVariableType = double, typename DependentVariableType = double >
class KalmanFilterBase
{
public:

    //! Typedef of the state and measurement vectors.
    typedef Eigen::Matrix< DependentVariableType, Eigen::Dynamic, 1 > DependentVector;

    //! Typedef of the state and measurement matrices.
    typedef Eigen::Matrix< DependentVariableType, Eigen::Dynamic, Eigen::Dynamic > DependentMatrix;

    //! Typedef of the function describing the system.
    typedef boost::function< DependentVector( const IndependentVariableType, const DependentVector&, const DependentVector& ) > SystemFunction;

    //! Typedef of the function describing the measurements.
    typedef boost::function< DependentVector( const IndependentVariableType, const DependentVector& ) > MeasurementFunction;

    //! Typedef of the integrator.
    typedef numerical_integrators::NumericalIntegrator< IndependentVariableType, DependentVector > Integrator;

    //! Constructor.
    /*!
     *  Constructor.
     *  \param systemUncertainty Matrix defining the uncertainty in modeling of the system.
     *  \param measurementUncertainty Matrix defining the uncertainty in modeling of the measurements.
     *  \param initialTime Scalar representing the value of the initial time.
     *  \param initialStateVector Vector representing the initial (estimated) state of the system. It is used as first
     *      a-priori estimate of the state vector.
     *  \param initialCovarianceMatrix Matrix representing the initial (estimated) covariance of the system. It is used as first
     *      a-priori estimate of the covariance matrix.
     *  \param isStateToBeIntegrated Boolean defining whether the system function needs to be integrated.
     *  \param integrator Pointer to integrator to be used to propagate state.
     */
    KalmanFilterBase( const DependentMatrix& systemUncertainty,
                      const DependentMatrix& measurementUncertainty,
                      const IndependentVariableType initialTime,
                      const DependentVector& initialStateVector,
                      const DependentMatrix& initialCovarianceMatrix,
                      const bool isStateToBeIntegrated,
                      const boost::shared_ptr< Integrator > integrator ) :
        systemUncertainty_( systemUncertainty ), measurementUncertainty_( measurementUncertainty ), initialTime_( initialTime ),
        aPosterioriStateEstimate_( initialStateVector ), aPosterioriCovarianceEstimate_( initialCovarianceMatrix ),
        isStateToBeIntegrated_( isStateToBeIntegrated ), integrator_( integrator )
    {
        // Check that uncertainty matrices are square
        if ( systemUncertainty_.rows( ) != systemUncertainty_.cols( ) )
        {
            throw std::runtime_error( "Error in setting up filter. The system uncertainty matrix has to be square." );
        }
        if ( measurementUncertainty_.rows( ) != measurementUncertainty_.cols( ) )
        {
            throw std::runtime_error( "Error in setting up filter. The measurement uncertainty matrix has to be square." );
        }

        // Create noise distributions
        generateNoiseDistributions( );
    }

    //! Default destructor.
    /*!
     *  Default destructor.
     */
    virtual ~KalmanFilterBase( ){ }

    //! Function to update the filter with the new step data.
    /*!
     *  Function to update the filter with the new step data.
     *  \param currentTime Scalar representing current time.
     *  \param currentControlVector Vector representing the current control input.
     *  \param currentMeasurementVector Vector representing current measurement.
     */
    virtual void updateFilter( const IndependentVariableType currentTime, const DependentVector& currentControlVector,
                               const DependentVector& currentMeasurementVector ) = 0;

    //! Function to retrieve current state estimate.
    /*!
     *  Function to retrieve current state estimate. The state estimate needs to first be computed by updating the filter with the
     *  updateFilter function.
     *  \return Current state estimate.
     */
    Eigen::Matrix< DependentVariableType, Eigen::Dynamic, 1 > getCurrentStateEstimate( )
    {
        return aPosterioriStateEstimate_;
    }

    //! Function to retrieve the history of estimated states.
    /*!
     *  Function to retrieve the history of estimated states.
     *  \return History of estimated states.
     */
    std::vector< DependentVector > getEstimatedStateHistory( )
    {
        return estimatedStateHistory_;
    }

    //! Function to retrieve the history of estimated covariance matrices.
    /*!
     *  Function to retrieve the history of estimated covariance matrices.
     *  \return History of estimated covariance matrices.
     */
    std::vector< DependentMatrix > getEstimatedCovarianceHistory( )
    {
        return estimatedCovarianceHistory_;
    }

    //! Function to retrieve the history of system and measurement noise used by the updateFilter function.
    /*!
     *  Function to retrieve the history of system and measurement noise.
     *  \return History of system and measurement noise, output as a std::pair.
     */
    std::pair< std::vector< DependentVector >, std::vector< DependentVector > > getNoiseHistory( )
    {
        return std::make_pair( systemNoiseHistory_, measurementNoiseHistory_ );
    }

    //! Function to propagate state to the next time step.
    /*!
     *  Function to propagate state to the next time step, by using the integrator settings provided
     *  in the input.
     *  \param intervalEnd Time to propagate to.
     *  \param initialStepSize Initial (or constant) step size for propagation.
     *  \param finalTimeTolerance Tolerance used to define whether final time has been reached.
     *  \return Propagated state at the requested time.
     */
    DependentVector integrateState( const IndependentVariableType intervalEnd,
                                    const IndependentVariableType initialStepSize,
                                    const IndependentVariableType finalTimeTolerance = std::numeric_limits< IndependentVariableType >::epsilon( ) )
    {
        return integrator_->integrateTo( intervalEnd, initialStepSize, finalTimeTolerance );
    }

protected:

    //! Function to create the function that defines the system model.
    /*!
     *  Function to create the function that defines the system model. The output of this function is then bound
     *  to the systemFunction_ variable, via the boost::bind command.
     *  \param currentTime Scalar representing the current time.
     *  \param currentStateVector Vector representing the current state.
     *  \param currentControlVector Vector representing the current control input.
     *  \return Vector representing the estimated state.
     */
    virtual DependentVector createSystemFunction( const IndependentVariableType currentTime,
                                                  const DependentVector& currentStateVector,
                                                  const DependentVector& currentControlVector ) = 0;

    //! Function to create the function that defines the system model.
    /*!
     *  Function to create the function that defines the system model. The output of this function is then bound
     *  to the measurementFunction_ variable, via the boost::bind command.
     *  \param currentTime Scalar representing the current time.
     *  \param currentStateVector Vector representing the current state.
     *  \return Vector representing the estimated measurement.
     */
    virtual DependentVector createMeasurementFunction( const IndependentVariableType currentTime,
                                                       const DependentVector& currentStateVector ) = 0;

    //! Function to produce system noise.
    /*!
     *  Function to produce system noise, based on a Gaussian distribution, with zero mean and standard
     *  deviation given by the diagonal elements of the input system uncertainty matrix.
     *  \return Vector representing system noise.
     */
    DependentVector produceSystemNoise( )
    {
        // Declare system noise vector
        DependentVector systemNoise;
        systemNoise.resize( systemUncertainty_.rows( ), 1 );

        // Loop over dimensions and add noise
        for ( int i = 0; i < systemUncertainty_.rows( ); i++ )
        {
            systemNoise[ i ] = static_cast< DependentVariableType >( systemNoiseDistribution_.at( i )->getRandomVariableValue( ) );
        }

        // Give back noise
        systemNoiseHistory_.push_back( systemNoise );
        return systemNoise;
    }

    //! Function to produce measurement noise.
    /*!
     *  Function to produce measurement noise, based on a Gaussian distribution, with zero mean and standard
     *  deviation given by the diagonal elements of the input measurement uncertainty matrix.
     *  \return Vector representing measurement noise.
     */
    DependentVector produceMeasurementNoise( )
    {
        // Declare system noise vector
        DependentVector measurementNoise;
        measurementNoise.resize( measurementUncertainty_.rows( ), 1 );

        // Loop over dimensions and add noise
        for ( int i = 0; i < measurementUncertainty_.rows( ); i++ )
        {
            measurementNoise[ i ] = static_cast< DependentVariableType >( measurementNoiseDistribution_.at( i )->getRandomVariableValue( ) );
        }

        // Give back noise
        measurementNoiseHistory_.push_back( measurementNoise );
        return measurementNoise;
    }

    //! System function.
    /*!
     *  System function that will be used to retrieve the a-priori estimated state for the next step.
     */
    SystemFunction systemFunction_;

    //! Measurement function.
    /*!
     *  Measurement function that will be used to retrieve the estimated measurement for the next step,
     *  based on the current state.
     */
    MeasurementFunction measurementFunction_;

    //! Matrix representing the uncertainty in system modeling.
    DependentMatrix systemUncertainty_;

    //! Matrix representing the uncertainty in measurement modeling.
    DependentMatrix measurementUncertainty_;

    //! Scalar representing the initial time.
    IndependentVariableType initialTime_;

    //! Vector representing the a-posteriori estimated state.
    /*!
     *  Vector representing the a-posteriori estimated state, i.e., the state after the prediction and
     *  update steps of the Kalman filter.
     */
    DependentVector aPosterioriStateEstimate_;

    //! Matrix representing the a-posteriori estimated covariance.
    /*!
     *  Matrix representing the a-posteriori estimated covariance, i.e., the covariance after the prediction and
     *  update steps of the Kalman filter.
     */
    DependentMatrix aPosterioriCovarianceEstimate_;

    //! Boolean specifying whether the state needs to be integrated.
    bool isStateToBeIntegrated_;

    //! Pointer to the integrator settings.
    /*!
     *  Pointer to the integrator settings, which is used to propagate the state to the new time step.
     */
    boost::shared_ptr< Integrator > integrator_;

    //! Vector of estimated states vectors.
    std::vector< DependentVector > estimatedStateHistory_;

    //! Vector of estimated covariance matrices.
    std::vector< DependentMatrix > estimatedCovarianceHistory_;

private:

    //! Function to generate the noise distributions for both system and measurement modeling.
    /*!
     *  Function to generate the noise distributions for both system and measurement modeling, which uses
     *  a Gaussian distribution, with zero mean and standard deviation given by the diagonal elements of the
     *  input system and measurement uncertainty matrices.
     */
    void generateNoiseDistributions( )
    {
        using namespace tudat::statistics;

        // Create system noise
        for ( int i = 0; i < systemUncertainty_.rows( ); i++ )
        {
            systemNoiseDistribution_.push_back( createBoostContinuousRandomVariableGenerator(
                        normal_boost_distribution, { 0.0, static_cast< double >( systemUncertainty_( i, i ) ) }, 12345.0 ) );
        }

        // Create measurement noise
        for ( int i = 0; i < measurementUncertainty_.rows( ); i++ )
        {
            measurementNoiseDistribution_.push_back( createBoostContinuousRandomVariableGenerator(
                        normal_boost_distribution, { 0.0, static_cast< double >( measurementUncertainty_( i, i ) ) }, 54321.0 ) );
        }
    }

    //! Vector where the system noise generators are stored.
    std::vector< boost::shared_ptr< statistics::RandomVariableGenerator< double > > > systemNoiseDistribution_;

    //! Vector where the measurement noise generators are stored.
    std::vector< boost::shared_ptr< statistics::RandomVariableGenerator< double > > > measurementNoiseDistribution_;

    //! Vector of system noise.
    std::vector< DependentVector > systemNoiseHistory_;

    //! Vector of measurement noise.
    std::vector< DependentVector > measurementNoiseHistory_;

};

//! Typedef for a filter with double data type.
typedef KalmanFilterBase< > KalmanFilter;

//! Typedef for a shared-pointer to a filter with double data type.
typedef boost::shared_ptr< KalmanFilter > KalmanFilterPointer;

} // namespace filters

} // namespace tudat

#endif // TUDAT_KALMAN_FILTER_H
