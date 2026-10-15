# SPENCLMX — Mobile-First Physics Lab

A compact, touch-first physics authoring sandbox with a 3D viewport, large touch targets, collapsible tools, and explicit collision-shape application.

## Foundation
- TypeScript + Vite app shell
- Three.js viewport and multi-face raycasting
- Rapier 3D WebAssembly rigid-body runtime
- Responsive mobile inspector, scene grid, simulation controls
- GitHub Actions build verification and web artifact upload

## Collision authoring goals
1. **Paint mask:** paint/erase collision coverage like weight or texture painting.
2. **Multi-face selection:** select multiple faces, add/remove faces, and preview the region.
3. **Apply:** selected/painted faces are baked into triangle-mesh collider buffers in mesh-local coordinates; colliders use authored triangles rather than bounding boxes. Rapier triangle meshes are best suited to fixed geometry; dynamic concave mesh contacts require stability testing, and convex decomposition remains needed for production moving concave assets.
4. **Per-mesh tuning:** each applied triangle region has friction, restitution, damping, and impulse-strength controls. Friction/restitution apply to each Rapier collider; damping and the current impulse test are body-level settings, so multiple regions currently share the strongest configured value.

## Physics roadmap
- Armature-aware collision attachment: colliders are stored in mesh-local coordinates, but rigged-model import, per-bone attachment, and deformation-driven collider updates are not implemented in the current cube demo.
- Rigid bodies, joints, contact events, collision layers and sensors via Rapier
- Interaction and impulse tests for punching/contact response
- Jiggle and secondary-motion constraints
- Soft/deformable bodies and FEM adapter research
- Scene save/load, import/export, profiling, automated tests and Android packaging

## Architecture
Rapier + WASM is the first rigid-body backend; Three.js handles rendering and face picking. Keep UI, collision data and simulation backends modular. Mojo and Verse are optional research/tooling candidates, not required browser runtime dependencies. “AMD FEM” needs a verified upstream project/specification before integration, so an adapter seam is reserved instead of claiming unsupported integration.

## Android testing
The CI workflow creates a debug APK using Capacitor and Android Gradle (Android API 35 / build-tools 35.0.0). Download the `spenclmx-android-debug-apk` artifact from a successful Actions run, install it on a test device, and verify touch controls, Rapier WASM initialization, gravity, and collision stability. This is a debug build, not a signed release APK.

## Run
```sh
npm install
npm run dev
npm run build
```

GitHub Actions builds both the web app and a debug Android APK artifact. APK generation is not considered verified until the Android workflow succeeds; install the artifact on-device to validate WebView/WASM behavior.