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
3. **Apply:** validate the authored region and create a derived collider attached to the source object, without destroying the source mesh. The initial UI will record collider recipes; true collider mesh baking is a separate implementation milestone.

## Physics roadmap
- Rigid bodies, joints, contact events, collision layers and sensors via Rapier
- Interaction and impulse tests for punching/contact response
- Jiggle and secondary-motion constraints
- Soft/deformable bodies and FEM adapter research
- Scene save/load, import/export, profiling, automated tests and Android packaging

## Architecture
Rapier + WASM is the first rigid-body backend; Three.js handles rendering and face picking. Keep UI, collision data and simulation backends modular. Mojo and Verse are optional research/tooling candidates, not required browser runtime dependencies. “AMD FEM” needs a verified upstream project/specification before integration, so an adapter seam is reserved instead of claiming unsupported integration.

## Run
```sh
npm install
npm run dev
npm run build
```

The current CI target is a static web build, not an Android APK yet.