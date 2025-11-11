#!/bin/bash
# flash_and_monitor.sh - Build, Flash and Monitor ESP32-S3

set -e

# Colors for output
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
NC='\033[0m' # No Color

echo -e "${GREEN}═══════════════════════════════════════${NC}"
echo -e "${GREEN}  ESP32-S3 Build, Flash & Monitor${NC}"
echo -e "${GREEN}═══════════════════════════════════════${NC}"

# Check if port is provided
if [ -z "$1" ]; then
    echo -e "${YELLOW}Usage: $0 <PORT>${NC}"
    echo -e "${YELLOW}Example: $0 /dev/ttyUSB0${NC}"
    echo -e "${YELLOW}Example: $0 COM3${NC}"
    exit 1
fi

PORT=$1

echo -e "\n${GREEN}[1/4] Setting target to ESP32-S3...${NC}"
idf.py set-target esp32s3

echo -e "\n${GREEN}[2/4] Building project...${NC}"
idf.py build

echo -e "\n${GREEN}[3/4] Flashing to $PORT...${NC}"
idf.py -p $PORT flash

echo -e "\n${GREEN}[4/4] Starting monitor...${NC}"
echo -e "${YELLOW}Press Ctrl+] to exit monitor${NC}\n"
idf.py -p $PORT monitor
