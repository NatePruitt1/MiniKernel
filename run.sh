#!/usr/bin/env bash
set -euo pipefail

ROOT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"

BUILDER_IMAGE="minikernel-build"
QEMU_IMAGE="minikernel-qemu"

BUILD_DOCKERFILE="$ROOT_DIR/dockerfile"
QEMU_DOCKERFILE="$ROOT_DIR/dockerfile.qemu"

if ! command -v docker >/dev/null 2>&1; then
  echo "docker is required but not installed."
  exit 1
fi

echo "[1/4] Building cross-compiler image ($BUILDER_IMAGE)..."
docker build -t "$BUILDER_IMAGE" -f "$BUILD_DOCKERFILE" "$ROOT_DIR"

echo "[2/4] Building QEMU image ($QEMU_IMAGE)..."
docker build -t "$QEMU_IMAGE" -f "$QEMU_DOCKERFILE" "$ROOT_DIR"

echo "[3/4] Building kernel image (kernel/out/kernel8.img)..."
docker run --rm \
  -v "$ROOT_DIR":/app \
  -w /app/kernel \
  "$BUILDER_IMAGE" \
  make clean all

echo "[4/4] Booting in QEMU..."
docker run --rm -it \
  -v "$ROOT_DIR/kernel/out":/work \
  "$QEMU_IMAGE"
