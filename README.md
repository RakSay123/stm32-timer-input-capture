# STM32 Bare-Metal Timer & PWM Driver
gif goes here

A hardware PWM implementation for the **STM32G070RB** written completely in **bare-metal C** using CMSIS register definitions. This project demonstrates how to generate PWM signals without STM32 HAL or LL libraries while building a reusable embedded firmware architecture.

The project is part of a larger firmware framework where peripherals are implemented as reusable drivers and combined into higher-level device abstractions.

---

### Features

- Bare-metal STM32 development using CMSIS
- No HAL or LL libraries
- Modular driver architecture
- General timer driver
- PWM driver supporting:
  - Channels 1–4
  - PWM Mode 1
  - PWM Mode 2
- LED device abstraction
- Adjustable duty cycle API
- Smooth LED breathing demo

---

## Project Structure

```text
Drivers/
│
├── gpio/
├── uart/
├── i2c/
├── systick/
└── timer/
      └── timer_pwm/

Devices/
│
├── led/
└── bno055/

device_instances/

init/

main.c
```

### Drivers

Drivers are responsible for interacting directly with STM32 peripherals.

Current drivers include:

- GPIO
- UART
- I2C
- SysTick
- Timer
- PWM

Each driver is designed to be reusable and independent of any particular application.

---

### Devices

Devices are built on top of one or more drivers.

For example:

```text
LED
 ├── GPIO
 └── Timer PWM

BNO055
 ├── GPIO
 └── I2C
```

This separation keeps application code clean while allowing peripherals to be reused across multiple devices.

---

### Device Instances

Board-specific hardware is defined in one location.

Examples include:

- ON BOARD LED
- PWM LED
- BNO055

Applications simply retrieve the desired device instead of manually configuring peripherals.

---

## PWM Theory

A timer is fundamentally a counter.

After configuring the timer's:
- Prescaler (PSC)
- Auto Reload Register (ARR)

the timer repeatedly counts

```text
0 → 1 → 2 → ... → ARR → 0
```

Each timer contains up to four independent channels.

When configured in **PWM Mode 1**, each channel compares the current timer count (`CNT`) against its corresponding compare register (`CCRx`).

```c
if (CNT < CCRx)
{
    Output = HIGH;
}
else
{
    Output = LOW;
}
```

Changing the value stored in `CCRx` changes how long the output remains HIGH during each PWM period.

This percentage of time spent HIGH is known as the **duty cycle**.

A higher duty cycle makes an LED appear brighter.

---

## PWM Initialization

Generating PWM requires:

1. Configure the GPIO pin for the appropriate Alternate Function.
2. Configure the timer base (PSC and ARR).
3. Configure the desired timer channel for PWM Mode 1 or PWM Mode 2.
4. Enable output preload.
5. Enable the capture/compare channel.
6. Configure the desired duty cycle.
7. Enable the timer.

After initialization, the timer hardware generates the PWM waveform automatically.

The CPU is no longer involved unless the duty cycle needs to change.

---

## Driver API

```c
TIM_PWM_Config_t pwm_led =
{
    .TIMx = TIM3,
    .channel = 1,
    .duty_cycle = 50,
    .pwm_mode = TIM_PWM1
};

timer_pwm_init(&pwm_led);
```

Changing brightness simply becomes

```c
timer_set_duty_cycle(&pwm_led, 75);
```

The timer hardware immediately updates the waveform.

---

## Challenges

### Hardware PWM

Unlike software delays or GPIO toggling, PWM generation is handled entirely by the timer peripheral after initial configuration.

### Alternate Functions

GPIO pins must be connected to timer channels using the correct Alternate Function before PWM signals appear on an output.

### Timer Channels

Each timer contains multiple independent channels.

Each channel has its own compare register while sharing the timer's counter and timing base.

### Interrupt Debugging

One interesting bug occurred after enabling timer interrupts without implementing the corresponding interrupt handler.

Because update interrupts were enabled, execution entered the default interrupt handler and remained there indefinitely, appearing as a silent program freeze.

This reinforced the importance of ensuring every enabled interrupt has a valid handler.

### Register-Level Debugging

STM32CubeIDE's **Expressions** window proved extremely useful.

Inspecting peripheral registers during execution made it much easier to determine whether hardware was actually being configured correctly.

---

## Lessons Learned

This project significantly improved my understanding of:

- Timer architecture
- PWM generation
- Duty cycle manipulation
- Alternate Function routing
- Timer channels
- Hardware-generated peripherals
- Interrupt handling
- Modular embedded firmware architecture

---

## Future Improvements

- RGB LED driver
- Servo motor driver
- DC motor driver
- Quadrature encoder support
- Complete timer driver
- ADC driver
- SPI driver
- DMA / DMAMUX support
- Advanced timer (TIM1) features
- Micromouse integration

---

## Technologies

- STM32G070RB
- STM32CubeIDE
- CMSIS
- Bare-metal C
- Git
