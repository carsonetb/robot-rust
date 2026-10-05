/*
 * Copyright (C) Cross The Road Electronics.  All rights reserved.
 * License information can be found in CTRE_LICENSE.txt
 * For support and suggestions contact support@ctr-electronics.com or file
 * an issue tracker at https://github.com/CrossTheRoadElec/Phoenix-Releases
 */
#pragma once

#include "ctre/phoenix/StatusCodes.h"
#include "ctre/phoenix6/signals/SpnEnums.hpp"
#include "ctre/phoenix6/sim/ChassisReference.hpp"
#include <units/angle.h>
#include <units/angular_velocity.h>
#include <units/voltage.h>
#include <units/current.h>

namespace ctre {
namespace phoenix6 {

namespace hardware {
namespace core {
	/* forward proto */
	class CoreCANdi;
}
}

namespace sim {

	/**
	 * \brief Class to control the state of a simulated hardware#CANdi.
	 */
	class CANdiSimState
	{
	private:
		int _id;

	public:
		/**
		 * \brief The orientation of the PWM1 sensor relative
		 * to the robot chassis.
		 *
		 * This value should not be changed based on the CANdi PWM1 invert.
		 * Rather, this value should be changed when the mechanical linkage
		 * between the sensor and the robot changes.
		 */
		ChassisReference Pwm1Orientation;

		/**
		 * \brief The orientation of the PWM2 sensor relative
		 * to the robot chassis.
		 *
		 * This value should not be changed based on the CANdi PWM2 invert.
		 * Rather, this value should be changed when the mechanical linkage
		 * between the sensor and the robot changes.
		 */
		ChassisReference Pwm2Orientation;

		/**
		 * \brief The orientation of the Quadrature sensor relative
		 * to the robot chassis.
		 *
		 * This value should not be changed based on the CANdi Quadrature invert.
		 * Rather, this value should be changed when the mechanical linkage
		 * between the sensor and the robot changes.
		 */
		ChassisReference QuadratureOrientation;
		/**
		 * \brief The number of quadrature edges per sensor rotation for an
		 * external quadrature sensor attached to the CANdi.
		 */
		int QuadratureEdgesPerRotation = 4096;

		/**
		 * \brief Creates an object to control the state of the given hardware#CANdi.
		 *
		 * \details Note the recommended method of accessing simulation features is to
		 *          use hardware#CANdi#GetSimState.
		 *
		 * \param device Device to which this simulation state is attached
		 */
		CANdiSimState(hardware::core::CoreCANdi const &device) :
			CANdiSimState{
				device,
				ChassisReference::CounterClockwise_Positive,
				ChassisReference::CounterClockwise_Positive,
				ChassisReference::CounterClockwise_Positive
			}
		{}
		/**
		 * \brief Creates an object to control the state of the given hardware#CANdi.
		 *
		 * \details Note the recommended method of accessing simulation features is to
		 *          use hardware#CANdi#GetSimState.
		 *
		 * \param device Device to which this simulation state is attached
		 * \param pwm1Orientation Orientation of the PWM1 sensor relative to the robot chassis
		 * \param pwm2Orientation Orientation of the PWM2 sensor relative to the robot chassis
		 * \param quadratureOrientation Orientation of the Quadrature sensor relative to the robot chassis
		 */
		CANdiSimState(
			hardware::core::CoreCANdi const &device,
			ChassisReference pwm1Orientation,
			ChassisReference pwm2Orientation,
			ChassisReference quadratureOrientation
		);
		/* disallow copy, allow move */
		CANdiSimState(CANdiSimState const &) = delete;
		CANdiSimState(CANdiSimState &&) = default;
		CANdiSimState &operator=(CANdiSimState const &) = delete;
		CANdiSimState &operator=(CANdiSimState &&) = default;

		/**
		 * \brief Sets the simulated supply voltage of the CANdi.
		 *
		 * \details The minimum allowed supply voltage is 4 V - values below this
		 * will be promoted to 4 V.
		 *
		 * \param volts The supply voltage in Volts
		 * \returns Status code
		 */
		ctre::phoenix::StatusCode SetSupplyVoltage(units::voltage::volt_t volts);
		/**
		 * \brief Sets the simulated output current of the CANdi.
		 *
		 * \param current The output current
		 * \return Status code
		 */
		ctre::phoenix::StatusCode SetOutputCurrent(units::current::ampere_t current);
		/**
		 * \brief Sets the simulated PWM1 Rise to Rise timing of the CANdi.
		 *
		 * \param time The time between two Rise events
		 * \return Status code
		 */
		ctre::phoenix::StatusCode SetPwm1RiseRise(units::time::second_t time);
		/**
		 * \brief Sets the simulated PWM1 Rise to Fall timing of the CANdi.
		 *
		 * \param time The time between the Rise and Fall events in seconds
		 * \return Status code
		 */
		ctre::phoenix::StatusCode SetPwm1RiseFall(units::time::second_t time);
		/**
		 * \brief Sets whether a PWM sensor is connected to the S1 pin.
		 *
		 * \param connected True if sensor is connected
		 * \return Status code
		 */
		ctre::phoenix::StatusCode SetPwm1Connected(bool connected);
		/**
		 * \brief Sets the simulated pulse width position of the CANdi. This is the position
		 * of an external PWM encoder connected to the S1 pin.
		 *
		 * \param position The new position
		 * \return Status code
		 */
		ctre::phoenix::StatusCode SetPwm1Position(units::angle::turn_t position);
		/**
		 * \brief Sets the simulated pulse width velocity of the CANdi. This is the velocity
		 * of an external PWM encoder connected to the S1 pin.
		 *
		 * \param velocity The new velocity
		 * \return Status code
		 */
		ctre::phoenix::StatusCode SetPwm1Velocity(units::angular_velocity::turns_per_second_t velocity);
		/**
		 * \brief Sets the simulated PWM2 Rise to Rise timing of the CANdi.
		 *
		 * \param time The time between two Rise events
		 * \return Status code
		 */
		ctre::phoenix::StatusCode SetPwm2RiseRise(units::time::second_t time);
		/**
		 * \brief Sets the simulated PWM2 Rise to Fall timing of the CANdi.
		 *
		 * \param time The time between the Rise and Fall events in seconds
		 * \return Status code
		 */
		ctre::phoenix::StatusCode SetPwm2RiseFall(units::time::second_t time);
		/**
		 * \brief Sets whether a PWM sensor is connected to the S2 pin.
		 *
		 * \param connected True if sensor is connected
		 * \return Status code
		 */
		ctre::phoenix::StatusCode SetPwm2Connected(bool connected);
		/**
		 * \brief Sets the simulated pulse width position of the CANdi. This is the position
		 * of an external PWM encoder connected to the S2 pin.
		 *
		 * \param position The new position
		 * \return Status code
		 */
		ctre::phoenix::StatusCode SetPwm2Position(units::angle::turn_t position);
		/**
		 * \brief Sets the simulated pulse width velocity of the CANdi. This is the velocity
		 * of an external PWM encoder connected to the S2 pin.
		 *
		 * \param velocity The new velocity
		 * \return Status code
		 */
		ctre::phoenix::StatusCode SetPwm2Velocity(units::angular_velocity::turns_per_second_t velocity);
		/**
		 * \brief Sets the simulated raw quadrature position of the CANdi.
		 *
		 * Inputs to this function over time should be continuous, as user calls of hardware#CANdi#SetQuadraturePosition will be accounted for in the callee.
		 *
		 * \details The CANdi integrates this to calculate the true reported quadrature position.
		 *
		 * When using the WPI Sim GUI, you will notice a readonly `position` and settable `rawPositionInput`.
		 * The readonly signal is the emulated position which will match self-test in Tuner and the hardware API.
		 * Changes to `rawPositionInput` will be integrated into the emulated position.
		 * This way a simulator can modify the position without overriding hardware API calls for home-ing the sensor.
		 *
		 * \param position The raw position
		 * \return Status code
		 */
		ctre::phoenix::StatusCode SetRawQuadraturePosition(units::angle::turn_t position);
		/**
		 * \brief Sets the simulated pulse width velocity of the CANdi.
		 *
		 * \param velocity The new velocity
		 * \return Status code
		 */
		ctre::phoenix::StatusCode SetQuadratureVelocity(units::angular_velocity::turns_per_second_t velocity);
		/**
		 * \brief Sets the state of the S1 pin
		 *
		 * \param state The state to set the S1 pin to
		 * \return Status code
		 */
		ctre::phoenix::StatusCode SetS1State(ctre::phoenix6::signals::S1StateValue state);
		/**
		 * \brief Sets the state of the S2 pin
		 *
		 * \param state The state to St the S2 pin to
		 * \return Status code
		 */
		ctre::phoenix::StatusCode SetS2State(ctre::phoenix6::signals::S2StateValue state);
	};
}

}
}
