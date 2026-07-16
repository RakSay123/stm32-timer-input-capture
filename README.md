# STM32 Timer Input Capture & PWM Monitor
![PWM Monitor Demo](media/pwm-monitor-demo.gif)
A bare-metal STM32 project demonstrating **timer input capture** by measuring a PWM waveform generated from another timer.

Instead of simply generating PWM, this project uses a second timer configured in **Input Capture mode** to analyze the waveform in real time and calculate:

- PWM Period
- HIGH Time
- LOW Time
- Duty Cycle

The project is written entirely using **register-level programming** without HAL, with reusable peripheral and device drivers.

# Features

- Bare-metal STM32G070RB development
- Generic timer input capture driver
- Generic PWM driver
- PWM monitor implemented as a device driver
- Non-blocking application architecture
- UART debugging
- Heartbeat status LED
- PWM breathing LED
- Real-time waveform measurements

Measured values include:

- Period
- HIGH pulse width
- LOW pulse width
- Duty cycle percentage

---

# Project Architecture

```
Application
│
├── PWM Monitor
├── LED
└── System
      │
      ├── Timer Input Capture Driver
      ├── Timer PWM Driver
      ├── UART Driver
      ├── GPIO Driver
      └── SysTick Driver
```

The application periodically:

- updates the breathing LED
- updates the heartbeat LED
- services the PWM monitor
- prints measurements over UART

All tasks execute without blocking delays.

---

# How It Works

## PWM Generation

TIM3 Channel 1 generates a PWM waveform that drives an LED.

The LED brightness is continuously changed using software to create a breathing effect.

---

## PWM Measurement

A second timer is configured for Input Capture.

Rather than using STM32's dedicated PWM Input mode, this project intentionally measures the waveform manually to better understand how Input Capture works.

The monitor alternates between:

```
WAIT_RISING
        ↓
WAIT_FALLING
        ↓
WAIT_NEXT_RISING
        ↓
(repeat)
```

From these timestamps it calculates

```
Period
    = Rising₂ − Rising₁

HIGH Time
    = Falling₁ − Rising₁

LOW Time
    = Rising₂ − Falling₁

Duty
    = HIGH / Period × 100%
```

---

# Example Output

```
[PWM_MONITOR] Period: 1000 Ticks
[PWM_MONITOR] High: 500 Ticks
[PWM_MONITOR] Low: 500 Ticks
[PWM_MONITOR] Duty: 50%
```

As the LED breathes, the duty cycle smoothly changes:

```
31%
37%
44%
50%
57%
63%
70%
76%
83%
89%
96%
...
```

---

# What I Learned

This project helped me understand that **Input Capture is essentially the opposite of Output Compare**.

Instead of asking:

> "When should the timer change an output?"

Input Capture asks:

> "When an external event occurs, what was the timer count?"

The timer hardware automatically copies the current CNT value into CCRx whenever the configured edge is detected.

This allows software to measure pulse widths and timing without continuously polling GPIO inputs.

---

# Limitations

The PWM monitor currently uses:

- polling
- software polarity switching
- a simple state machine

Measurements are reliable across most duty cycles but begin to fail near approximately:

- below ~4%
- above ~97%

At extreme duty cycles, the HIGH or LOW pulse becomes so short that software may not switch capture polarity before the next edge arrives.

Future versions will explore:

- interrupt-driven capture
- STM32 PWM Input mode
- DMA-based capture

---

# Repository Structure

```
Drivers/
    gpio/
    uart/
    systick/
    timer/
        timer_pwm/
        timer_input_capture/

Devices/
    led/
    pwm_monitor/

device_instances/

init/

Src/
```

---

# Future Improvements

- Interrupt-driven PWM monitor
- PWM Input mode implementation
- DMA capture
- Encoder interface
- One Pulse mode
- Driver cleanup and additional documentation

---
