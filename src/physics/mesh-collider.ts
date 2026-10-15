import * as THREE from 'three';
import RAPIER from '@dimforge/rapier3d-compat';

/** Bake authored triangle faces into mesh-local collider buffers without replacing them with a bounding box. */
export function bakeTriangleRegion(position: THREE.BufferAttribute | THREE.InterleavedBufferAttribute, faceIndices: readonly number[]) {
  const vertices: number[] = [];
  const indices: number[] = [];
  for (const face of [...new Set(faceIndices)].sort((a, b) => a - b)) {
    const first = face * 3;
    if (!Number.isInteger(face) || face < 0 || first + 2 >= position.count) continue;
    for (let corner = 0; corner < 3; corner++) {
      const i = first + corner;
      vertices.push(position.getX(i), position.getY(i), position.getZ(i));
      indices.push(indices.length);
    }
  }
  if (indices.length < 3) throw new Error('At least one complete triangle is required');
  return { vertices: new Float32Array(vertices), indices: new Uint32Array(indices), triangleCount: indices.length / 3 };
}

/** Rapier triangle-mesh surface shape. Static geometry is preferred; dynamic concave meshes need stability testing. */
export function createTriangleSurfaceCollider(vertices: Float32Array, indices: Uint32Array, friction = 0.7, restitution = 0.05) {
  if (vertices.length < 9 || vertices.length % 3 !== 0 || indices.length < 3 || indices.length % 3 !== 0) throw new Error('Invalid triangle mesh collider buffers');
  for (const index of indices) if (index >= vertices.length / 3) throw new Error('Triangle mesh index is out of bounds');
  return RAPIER.ColliderDesc.trimesh(vertices, indices).setFriction(friction).setRestitution(restitution);
}
