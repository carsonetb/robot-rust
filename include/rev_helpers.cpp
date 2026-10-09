#include "rev_helpers.hpp"
#include <memory>
#include "rev/SparkMax.h"
#include "rev/SparkLowLevel.h"
#include "units/voltage.h"

namespace rev_helpers {

struct SparkMaxHandle {
  rev::spark::SparkMax motor;

  SparkMaxHandle(int id) : motor(id, rev::spark::SparkLowLevel::MotorType::kBrushless) {}
};

SparkMaxHandle* sparkmax_create(int can_id) { return new SparkMaxHandle(can_id); }

void sparkmax_set(SparkMaxHandle* handle, double speed) { handle->motor.Set(speed); }

void sparkmax_set_voltage(SparkMaxHandle* handle, double voltage) { handle->motor.SetVoltage(units::volt_t{voltage}); }

void sparkmax_destroy(SparkMaxHandle* handle) { delete handle; }

}  // namespace rev_helpers
