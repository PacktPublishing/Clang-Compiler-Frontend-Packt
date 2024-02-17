#!/bin/sh
find . \( -name "*.log" -o -name "*~" -o -name "*.tmp" -o -name "build" \) -exec rm -rf {} \;

