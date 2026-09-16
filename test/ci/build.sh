#!/usr/bin/env bash
#
# Build the practice exam code.
#
# Usage:
#   ci/build.sh
set -euo pipefail

# Root directory.
ROOT_DIR="$(dirname "${BASH_SOURCE[0]}")/.."

# Build the library.
cd "$ROOT_DIR"
make build lib
