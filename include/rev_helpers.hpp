#pragma once

namespace rev_helpers {

struct SparkMaxHandle;

SparkMaxHandle* sparkmax_create(int can_id);
void sparkmax_set(SparkMaxHandle* motor, double speed);
void sparkmax_set_voltage(SparkMaxHandle* motor, double voltage);
void sparkmax_destroy(SparkMaxHandle* motor);

}  // namespace rev_helpers
