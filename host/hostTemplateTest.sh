#!/bin/bash

UART_PORT="/dev/ttyACM0"
BAUD_RATE=115200
TEST_VAL=1235

function send_cmd() {
    local CMD="$1"
    echo "Sending: $CMD"
    echo -e "\r$CMD" > "$UART_PORT"
}

# Ensure UART is accessible
if [[ ! -e "$UART_PORT" ]]; then
    echo "Error: UART device $UART_PORT not found"
    exit 1
fi

# Setup UART: 8N1, no flow control
stty -F "$UART_PORT" $BAUD_RATE cs8 -cstopb -parenb -ixon -ixoff -crtscts raw

# Clear input buffer
cat "$UART_PORT" > /dev/null & CLEAR_PID=$!
sleep 0.2
kill $CLEAR_PID

# Run commands
send_cmd "template test"
sleep 5

# Read response (optional)
cat "$UART_PORT"


