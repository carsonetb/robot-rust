/*
 * Copyright (C) Cross The Road Electronics.  All rights reserved.
 * License information can be found in CTRE_LICENSE.txt
 * For support and suggestions contact support@ctr-electronics.com or file
 * an issue tracker at https://github.com/CrossTheRoadElec/Phoenix-Releases
 */
#pragma once

#include <algorithm>
#include <cmath>
#include <initializer_list>
#include <span>
#include <stdexcept>

#include "ctre/phoenix6/swerve/utility/circular_buffer.hpp"
#include "units/time.h"

namespace ctre {
namespace phoenix6 {
namespace swerve {

/**
 * This class implements a linear, digital filter. All types of FIR and IIR
 * filters are supported. Static factory methods are provided to create commonly
 * used types of filters.
 *
 * Filters are of the form:<br>
 *  y[n] = (b0 x[n] + b1 x[n-1] + … + bP x[n-P]) -
 *         (a0 y[n-1] + a2 y[n-2] + … + aQ y[n-Q])
 *
 * Where:<br>
 *  y[n] is the output at time "n"<br>
 *  x[n] is the input at time "n"<br>
 *  y[n-1] is the output from the LAST time step ("n-1")<br>
 *  x[n-1] is the input from the LAST time step ("n-1")<br>
 *  b0 … bP are the "feedforward" (FIR) gains<br>
 *  a0 … aQ are the "feedback" (IIR) gains<br>
 * IMPORTANT! Note the "-" sign in front of the feedback term! This is a common
 *            convention in signal processing.
 *
 * What can linear filters do? Basically, they can filter, or diminish, the
 * effects of undesirable input frequencies. High frequencies, or rapid changes,
 * can be indicative of sensor noise or be otherwise undesirable. A "low pass"
 * filter smooths out the signal, reducing the impact of these high frequency
 * components.  Likewise, a "high pass" filter gets rid of slow-moving signal
 * components, letting you detect large changes more easily.
 *
 * Example FRC applications of filters:
 *  - Getting rid of noise from an analog sensor input (note: the roboRIO's FPGA
 *    can do this faster in hardware)
 *  - Smoothing out joystick input to prevent the wheels from slipping or the
 *    robot from tipping
 *  - Smoothing motor commands so that unnecessary strain isn't put on
 *    electrical or mechanical components
 *  - If you use clever gains, you can make a PID controller out of this class!
 *
 * For more on filters, we highly recommend the following articles:<br>
 * https://en.wikipedia.org/wiki/Linear_filter<br>
 * https://en.wikipedia.org/wiki/Iir_filter<br>
 * https://en.wikipedia.org/wiki/Fir_filter<br>
 *
 * Note 1: Calculate() should be called by the user on a known, regular period.
 * You can use a Notifier for this or do it "inline" with code in a
 * periodic function.
 *
 * Note 2: For ALL filters, gains are necessarily a function of frequency. If
 * you make a filter that works well for you at, say, 100Hz, you will most
 * definitely need to adjust the gains if you then want to run it at 200Hz!
 * Combining this with Note 1 - the impetus is on YOU as a developer to make
 * sure Calculate() gets called at the desired, constant frequency!
 *
 * This is a copy of the WPILib implementation to fix
 * https://github.com/wpilibsuite/allwpilib/pull/6628.
 */
template <class T>
class LinearFilter {
 public:
  /**
   * Create a linear FIR or IIR filter.
   *
   * @param ffGains The "feedforward" or FIR gains.
   * @param fbGains The "feedback" or IIR gains.
   */
  LinearFilter(std::span<const double> ffGains, std::span<const double> fbGains)
      : m_inputs(ffGains.size()),
        m_outputs(fbGains.size()),
        m_inputGains(ffGains.begin(), ffGains.end()),
        m_outputGains(fbGains.begin(), fbGains.end()) {
    for (size_t i = 0; i < ffGains.size(); ++i) {
      m_inputs.emplace_front(0.0);
    }
    for (size_t i = 0; i < fbGains.size(); ++i) {
      m_outputs.emplace_front(0.0);
    }
  }

  /**
   * Create a linear FIR or IIR filter.
   *
   * @param ffGains The "feedforward" or FIR gains.
   * @param fbGains The "feedback" or IIR gains.
   */
  LinearFilter(std::initializer_list<double> ffGains,
               std::initializer_list<double> fbGains)
      : LinearFilter({ffGains.begin(), ffGains.end()},
                     {fbGains.begin(), fbGains.end()}) {}

  // Static methods to create commonly used filters
  /**
   * Creates a one-pole IIR low-pass filter of the form:<br>
   *   y[n] = (1 - gain) x[n] + gain y[n-1]<br>
   * where gain = e<sup>-dt / T</sup>, T is the time constant in seconds
   *
   * Note: T = 1 / (2 pi f) where f is the cutoff frequency in Hz, the frequency
   * above which the input starts to attenuate.
   *
   * This filter is stable for time constants greater than zero.
   *
   * @param timeConstant The discrete-time time constant in seconds.
   * @param period       The period in seconds between samples taken by the
   *                     user.
   */
  static LinearFilter<T> SinglePoleIIR(double timeConstant,
                                       units::second_t period) {
    double gain = std::exp(-period.value() / timeConstant);
    return LinearFilter({1.0 - gain}, {-gain});
  }

  /**
   * Creates a first-order high-pass filter of the form:<br>
   *   y[n] = gain x[n] + (-gain) x[n-1] + gain y[n-1]<br>
   * where gain = e<sup>-dt / T</sup>, T is the time constant in seconds
   *
   * Note: T = 1 / (2 pi f) where f is the cutoff frequency in Hz, the frequency
   * below which the input starts to attenuate.
   *
   * This filter is stable for time constants greater than zero.
   *
   * @param timeConstant The discrete-time time constant in seconds.
   * @param period       The period in seconds between samples taken by the
   *                     user.
   */
  static LinearFilter<T> HighPass(double timeConstant, units::second_t period) {
    double gain = std::exp(-period.value() / timeConstant);
    return LinearFilter({gain, -gain}, {-gain});
  }

  /**
   * Creates a K-tap FIR moving average filter of the form:<br>
   *   y[n] = 1/k (x[k] + x[k-1] + … + x[0])
   *
   * This filter is always stable.
   *
   * @param taps The number of samples to average over. Higher = smoother but
   *             slower
   * @throws std::runtime_error if number of taps is less than 1.
   */
  static LinearFilter<T> MovingAverage(int taps) {
    if (taps <= 0) {
      throw std::runtime_error("Number of taps must be greater than zero.");
    }

    std::vector<double> gains(taps, 1.0 / taps);
    return LinearFilter(gains, {});
  }

  /**
   * Reset the filter state.
   */
  void Reset() {
    std::fill(m_inputs.begin(), m_inputs.end(), T{0.0});
    std::fill(m_outputs.begin(), m_outputs.end(), T{0.0});
  }

  /**
   * Resets the filter state, initializing internal buffers to the provided
   * values.
   *
   * These are the expected lengths of the buffers, depending on what type of
   * linear filter used:
   *
   * <table>
   *   <tr>
   *     <th>Type</th>
   *     <th>Input Buffer Size</th>
   *     <th>Output Buffer Size</th>
   *   </tr>
   *   <tr>
   *     <td>Unspecified</td>
   *     <td>size of {@code ffGains}</td>
   *     <td>size of {@code fbGains}</td>
   *   </tr>
   *   <tr>
   *     <td>Single Pole IIR</td>
   *     <td>1</td>
   *     <td>1</td>
   *   </tr>
   *   <tr>
   *     <td>High-Pass</td>
   *     <td>2</td>
   *     <td>1</td>
   *   </tr>
   *   <tr>
   *     <td>Moving Average</td>
   *     <td>{@code taps}</td>
   *     <td>0</td>
   *   </tr>
   *   <tr>
   *     <td>Finite Difference</td>
   *     <td>size of {@code stencil}</td>
   *     <td>0</td>
   *   </tr>
   *   <tr>
   *     <td>Backward Finite Difference</td>
   *     <td>{@code Samples}</td>
   *     <td>0</td>
   *   </tr>
   * </table>
   *
   * @param inputBuffer Values to initialize input buffer.
   * @param outputBuffer Values to initialize output buffer.
   * @throws std::runtime_error if size of inputBuffer or outputBuffer does not
   *   match the size of ffGains and fbGains provided in the constructor.
   */
  void Reset(std::span<const T> inputBuffer, std::span<const T> outputBuffer) {
    // Clear buffers
    Reset();

    if (inputBuffer.size() != m_inputGains.size() ||
        outputBuffer.size() != m_outputGains.size()) {
      throw std::runtime_error(
          "Incorrect length of inputBuffer or outputBuffer");
    }

    for (size_t i = 0; i < inputBuffer.size(); ++i) {
      m_inputs.push_front(inputBuffer[i]);
    }
    for (size_t i = 0; i < outputBuffer.size(); ++i) {
      m_outputs.push_front(outputBuffer[i]);
    }
  }

  /**
   * Calculates the next value of the filter.
   *
   * @param input Current input value.
   *
   * @return The filtered value at this step
   */
  T Calculate(T input) {
    T retVal{0.0};

    // Rotate the inputs
    if (m_inputGains.size() > 0) {
      m_inputs.push_front(input);
    }

    // Calculate the new value
    for (size_t i = 0; i < m_inputGains.size(); ++i) {
      retVal += m_inputs[i] * m_inputGains[i];
    }
    for (size_t i = 0; i < m_outputGains.size(); ++i) {
      retVal -= m_outputs[i] * m_outputGains[i];
    }

    // Rotate the outputs
    if (m_outputGains.size() > 0) {
      m_outputs.push_front(retVal);
    }

    return retVal;
  }

  /**
   * Returns the last value calculated by the LinearFilter.
   *
   * @return The last value.
   */
  T LastValue() const { return m_outputs.front(); }

 private:
  circular_buffer<T> m_inputs;
  circular_buffer<T> m_outputs;
  std::vector<double> m_inputGains;
  std::vector<double> m_outputGains;

  /**
   * Factorial of n.
   *
   * @param n Argument of which to take factorial.
   */
  static constexpr int Factorial(int n) {
    if (n < 2) {
      return 1;
    } else {
      return n * Factorial(n - 1);
    }
  }
};

}
}
}
