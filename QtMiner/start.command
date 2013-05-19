!#/bin/bash
cd "`dirname "$0"`"
open QtMiner.app
./cgminer --api-listen --api-allow W:127.0.0.1

