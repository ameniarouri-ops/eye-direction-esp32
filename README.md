# Eye Direction Detector - ESP32 (simulation phase)

Reads two analog sensors and decides LEFT, CENTER or RIGHT.

## Status

- [x] Wokwi simulation with 2 potentiometers as fake sensors
- [x] Smoothing, calibration, LEDs, CSV logging
- [ ] Real IR sensors
- [ ] Real data collection
- [ ] Small ML model

## Important

All data here is SIMULATED, not real eye data.

## What I learned

- How to read and smooth noisy analog sensor values
- How to calibrate sensors with min/max averages
- How to turn raw values into a decision using thresholds
- How to log data to CSV for later analysis
