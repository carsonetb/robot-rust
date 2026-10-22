#!/bin/bash
set -e

# This is all similar to what gradlew deploy does

PROJECT_NAME="robot-test"
TEAM=3636
ROBOT_IP="10.36.36.2"

cargo build --target arm-unknown-linux-gnueabi

echo "If program stalls, roboRIO isn't connected."
ssh lvuser@${ROBOT_IP} "/usr/local/frc/bin/frcKillRobot.sh -t -r"
echo "Connected, user program stopped."

scp target/arm-unknown-linux-gnueabi/debug/${PROJECT_NAME} lvuser@${ROBOT_IP}:/home/lvuser/frcUserProgram
ssh lvuser@${ROBOT_IP} "chmod +x /home/lvuser/frcUserProgram"

# Copies only necessary .so files, verify that this works and then move this to
# scripts.

remote_files=$(ssh lvuser@${ROBOT_IP} "ls /home/lvuser")

missing=()
for f in target/arm-unknown-linux-gnueabi/debug/build/robot-rust-*/out/libraries/linux/athena/shared/*.so; do
  if ! printf '%s\n' "$remote_files" | grep -qxF "$(basename "$f")"; then
    missing+=("$f")
  fi
done

if [ ${#missing[@]} -gt 0 ]; then
  scp "${missing[@]}" lvuser@${ROBOT_IP}:/home/lvuser
else
  echo "All .so libraries already exist on the target."
fi

echo "env LD_LIBRARY_PATH=/home/lvuser ./frcUserProgram" > robotCommand
scp robotCommand lvuser@${ROBOT_IP}:/home/lvuser/robotCommand
ssh lvuser@${ROBOT_IP} "chmod +x /home/lvuser/robotCommand"
rm robotCommand

echo "Deployed!"
