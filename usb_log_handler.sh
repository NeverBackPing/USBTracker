#!/bin/bash

SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"

LOGFILE="$SCRIPT_DIR/usbtracker.log"
BIN="$SCRIPT_DIR/usbtracker"

if ! pgrep -f "$BIN" > /dev/null; then
    "$BIN" >> "$LOGFILE" 2>&1 &
fi