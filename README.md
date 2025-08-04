# Cordelia RTOS (crtos)

<div align="center">

![icon](doc\diagrams\logo.png)

</div>

Cordelia Real-Time Operating System (CRTOS) is designed for ARM-Cortex M3/M4 cores.

## Overview

Cordelia RTOS is a lightweight, efficient real-time operating system specifically designed for resource-constrained embedded systems. It provides deterministic task scheduling, inter-task communication primitives.

## Features

- **Scheduling**: Supports round-robin scheduling algorithm.
- **Memory Management**: It support only static memory usage.
- **Inter-task Communication**: Semaphores and message queues
- **Hardware Abstraction**: Cortex-M4/M3 support
- **Low Memory Footprint**: Optimized for microcontrollers with limited RAM and flash.

## Directory Structure

```
crtos/
├── src/                    # Source code
│   ├── kernel/            # Kernel implementation
│   ├── lib/               # System libraries
│   └── examples/          # Example applications
├── doc/                   # Documentation
│   ├── Doxyfile            # Doxygen file                     
└── README.md             # This file
```

### Prerequisites

- ARM GCC toolchain
- Make
- OpenOCD (only for flash and debug)

### Building

1. Clone the repository:
```bash
git clone https://github.com/kskozgun/crtos.git
cd crtos
```

2. Configure and build:
```bash
make build
```

### Running Examples

After building, you can run the example applications:

```bash
# Flash to target device
make flash
```

## Getting Started

[LINK]() # TODO: Add github doc link

## Supported Platforms

- ARM Cortex-M series (M3, M4)

## Contributing

1. Fork the repository
2. Create a feature branch (`git checkout -b feature/amazing-feature`)
3. Commit your changes (`git commit -m 'Add amazing feature'`)
4. Push to the branch (`git push origin feature/amazing-feature`)
5. Open a Pull Request

## License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.

## Acknowledgments

- ADD course in here

## Contact

- **Project Owner**: [kskozgun](https://github.com/kskozgun)
- **Repository**: [https://github.com/kskozgun/crtos](https://github.com/kskozgun/crtos)
- **Issues**: [https://github.com/kskozgun/crtos/issues](https://github.com/kskozgun/crtos/issues)

## Roadmap

- [ ] Add cooperative scheduler option
- [ ] Add semaphore synchronization primitive
- [ ] Implement message queue data structure
- [ ] Automated build and documentation with GitHub Actions
- [ ] Add low-power mode features in IDLE state.
- [ ] Implement mutex support
- [ ] Port to ARM Cortex-M0+ cores
- [ ] Port to RISC-V cores
---
