# Architecture

The following figure illustrates the simple hierarchy of CRTOS **implementation**. Kernel and hardware parts are tried to be **decoupled** as much as possible.

```plantuml
@startuml
!include crtos_arch.pu
@enduml
```

The following figure illustrates the working principle of CRTOS. **SysTick** timer is used for calling the scheduler and PendSV is used for context switching. The following table must be followed during interrupt initialization.

<div align="center">

***IRQ Priorities***

| Interrupt | Priority | Purpose | Note |
|-----------|----------|---------|------| 
| SysTick   | High     | Task scheduling trigger | Time slice is based on **SysTick** configuration |
| PendSV    | Lowest   | Context switching | The function returns to **PSP** & **Thread Mode** |
</div>

The scheduler runs in ***Handler Mode*** using ***MSP*** stack pointer; tasks run in ***Thread Mode*** using ***PSP*** stack pointer.

```plantuml
@startuml Round Robin Scheduler State Diagram
!include round_robin_states.pu
@enduml
```