/*
 * Copyright (C) Cross The Road Electronics.  All rights reserved.
 * License information can be found in CTRE_LICENSE.txt
 * For support and suggestions contact support@ctr-electronics.com or file
 * an issue tracker at https://github.com/CrossTheRoadElec/Phoenix-Releases
 */
#pragma once

#include "ctre/phoenix6/controls/ControlRequest.hpp"
#include "ctre/phoenix6/signals/SpnEnums.hpp"
#include "ctre/phoenix6/StatusSignal.hpp"
#include "ctre/phoenix6/hardware/traits/HasTalonControls.hpp"
#include "ctre/phoenix6/hardware/traits/HasTalonSignals.hpp"


namespace ctre {
namespace phoenix6 {
namespace hardware {
namespace traits {

/**
 * Contains everything common between Talon motor controllers.
 */
class CommonTalon : public HasTalonControls, public HasTalonSignals
{
public:
    virtual ~CommonTalon() = default;

    using HasTalonControls::SetControl;


};

}
}
}
}

