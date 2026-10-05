#!/bin/bash
set -e

# This is all similar to what gradlew deploy does

PROJECT_NAME="robot-rust"
TEAM=3636
ROBOT_IP="what's this?"

cargo build --target arm-unknown-linux-gnueabi

ssh lvuser@{ROBOT_IP} "/etc/init.d/frcUserProgram stop"

scp target/arm-unknown-linux-gnueabi/release/${PROJECT_NAME} lvuser@${ROBOT_IP}:/home/lvuser/frcUserProgram
ssh lvuser@${ROBOT_IP} "chmod +x /home/lvuser/frcUserProgram"

scp libraries/linux/athena/shared/*.so lvuser@${ROBOT_IP}:/home/lvuser/

echo "env LD_LIBRARY_PATH=/home/lvuser ./frcUserProgram" > robotCommand
scp robotCommand lvuser@${ROBOT_IP}:/home/lvuser/robotCommand
ssh lvuser@${ROBOT_IP} "chmod +x /home/lvuser/robotCommand"
rm robotCommand

ssh lvuser@${ROBOT_IP} "/etc/init.d/frcUserProgram start"

echo "Deployed!"
