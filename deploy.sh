#!/bin/bash
set -e

# This is all similar to what gradlew deploy does

PROJECT_NAME="robot-rust"
TEAM=3636
ROBOT_IP="10.36.36.2"

cargo build --target arm-unknown-linux-gnueabi --release

echo "If program stalls, roboRIO isn't connected."
ssh lvuser@${ROBOT_IP} "sudo systemctl stop frcUserProgram"
echo "Connected, user program stopped."

scp target/arm-unknown-linux-gnueabi/release/${PROJECT_NAME} lvuser@${ROBOT_IP}:/home/lvuser/frcUserProgram
ssh lvuser@${ROBOT_IP} "chmod +x /home/lvuser/frcUserProgram"

scp libraries/linux/athena/shared/*.so lvuser@${ROBOT_IP}:/home/lvuser/

echo "env LD_LIBRARY_PATH=/home/lvuser ./frcUserProgram" > robotCommand
scp robotCommand lvuser@${ROBOT_IP}:/home/lvuser/robotCommand
ssh lvuser@${ROBOT_IP} "chmod +x /home/lvuser/robotCommand"
rm robotCommand

ssh lvuser@${ROBOT_IP} "sudo systemctl start frcUserProgram"

echo "Deployed!"
