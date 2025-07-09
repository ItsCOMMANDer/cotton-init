# Init System Feature List

| Feature                     | Status / Notes                              |
|-----------------------------|---------------------------------------------|
| **Basic service supervision** | ✅ Start, stop, restart, monitor services     |
| **Parallel service startup**  | ✅ Start independent services concurrently     |
| **Dependency management**     | ✅ Support service dependencies                |
| **Service descriptions in Lua** | ✅ Use embedded Lua for flexible service files  |
| **Logging**                   | ⚠️ Basic logging (to be implemented)             |
| **CLI tool for management**   | ⚠️ Optional: tool to query and control services  |
| **Socket activation**         | ❌ Not planned                                 |
| **Mount/target management**   | ❌ Delegated to separate standalone service     |
| **Hotplug/device management** | ❌ Leave to udev or other dedicated tool        |
| **Resource limits (cgroups)** | ✅ Support core controllers: cpu, memory, pids  |
| **Service restart on failure**| ✅ Automatic restart of crashed services        |
| **Unified service lifecycle hooks** | ⚠️ Lua hooks for start/stop (planned)          |
| **Security / permission management** | ⚠️ TBD (depending on cgroup and user privileges)  |

(AI Generated)
