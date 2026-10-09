#include "rev_helpers.hpp"
#include <memory>
#include "rev/SparkMax.h"
#include "rev/SparkLowLevel.h"
#include "units/voltage.h"

namespace rev_helpers {

struct NeoHandle {
  rev::spark::SparkMax motor;

  NeoHandle(int id) : motor(id, rev::spark::SparkLowLevel::MotorType::kBrushless) {}
};

NeoHandle* neo_create(int can_id) { return new NeoHandle(can_id); }

void neo_set(NeoHandle* handle, double speed) { handle->motor.Set(speed); }

void neo_set_voltage(NeoHandle* handle, double voltage) { handle->motor.SetVoltage(units::volt_t{voltage}); }

void neo_destroy(NeoHandle* handle) { delete handle; }

}  // namespace rev_helpers
