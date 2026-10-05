/*
 * Copyright (C) Cross The Road Electronics.  All rights reserved.
 * License information can be found in CTRE_LICENSE.txt
 * For support and suggestions contact support@ctr-electronics.com or file
 * an issue tracker at https://github.com/CrossTheRoadElec/Phoenix-Releases
 */
#pragma once

#include "ctre/phoenix/StatusCodes.h"
#include "ctre/phoenix6/signals/SpnEnums.hpp"
#include <units/length.h>
#include <units/voltage.h>

namespace ctre {
namespace phoenix6 {

namespace hardware {
namespace core {
	/* forward proto */
	class CoreCANrange;
}
}

namespace sim {

	/**
	 * \brief Class to control the state of a simulated hardware#CANrange.
	 */
	class CANrangeSimState
	{
	private:
		int _id;

	public:
		/**
		 * \brief Creates an object to control the state of the given hardware#CANrange.
		 *
		 * \details Note the recommended method of accessing simulation features is to
		 *          use hardware#CANrange#GetSimState.
		 *
		 * \param device Device to which this simulation state is attached
		 */
		CANrangeSimState(hardware::core::CoreCANrange const &device);
		/* disallow copy, allow move */
		CANrangeSimState(CANrangeSimState const &) = delete;
		CANrangeSimState(CANrangeSimState &&) = default;
		CANrangeSimState &operator=(CANrangeSimState const &) = delete;
		CANrangeSimState &operator=(CANrangeSimState &&) = default;

		/**
		 * \brief Sets the simulated supply voltage of the CANrange.
		 *
		 * \details The minimum allowed supply voltage is 4 V - values below this
		 * will be promoted to 4 V.
		 *
		 * \param volts The supply voltage in Volts
		 * \returns Status code
		 */
		ctre::phoenix::StatusCode SetSupplyVoltage(units::voltage::volt_t volts);

		/**
		 * \brief Sets the simulated distance of the CANrange.
		 *
		 * \param meters The distance in meters
		 * \returns Status code
		 */
		ctre::phoenix::StatusCode SetDistance(units::length::meter_t meters);
	};
}

}
}
