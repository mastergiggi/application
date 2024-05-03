# Configuration files for development with Visual Studio Code

## Copy json files

```shell
mkdir ~/zephyr-workspace/.vscode
cd ~/zephyr-workspace/application/ide/vscode
cp *.json ~/zephyr-workspace/.vscode
```

## Build task

Press [CTRL] + [SHIFT] + [B] to start west build using the `native_sim` board.

## Debug launch

Press [CTRL] + [SHIFT] + [D] and select the `GDB Launch` to start debug session.
