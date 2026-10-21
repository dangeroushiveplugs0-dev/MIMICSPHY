# SPENCLMX Architecture — M0

## Principles
- Renderer-independent C++ core; no Unreal or Android UI dependencies in solver code.
- Begin with a small, testable secondary-motion solver inspired by KawaiiPhysics, not a direct port.
- Keep rigid-body, soft-body, and liquid solvers separate until benchmarks justify integration.
- Kotlin/JNI, Python, Rust, Lua, and SQLite are optional adapters/tools, not mandatory dependencies of the core.

## Language roles
- C++20: native simulation core.
- Kotlin/JNI: future Android test shell.
- Python: offline asset tools, test generation, automation.
- Rust: evaluate for isolated memory-sensitive utilities after API stabilization.
- Lua: optional runtime scripting, sandboxed and instruction-budgeted.
- SQLite: optional project metadata; not solver storage.

## Milestones
M0: vector math, fixed-length bone chain, gravity, external acceleration, damping, stiffness, finite-value validation, CMake tests.
M1: sphere/capsule collision constraints, reset/teleport handling, warm-up.
M2: stable C ABI and Android NDK/JNI smoke test.
M3: animation synchronization and reusable settings assets.
M4: detailed mesh collision plus optional proxies; Android profiling.
M5: separate soft-body prototype; compare position-based dynamics and FEM.
M6: viscous liquid prototype with reconstructed surface.
M7: optional Python and Lua adapters if justified.

Every milestone must compile and pass tests in CI. Performance claims require repeatable benchmarks. Review licenses before adding dependencies.