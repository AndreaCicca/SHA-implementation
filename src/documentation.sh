#!/bin/bash

docker run --rm -u $(id -u) -v $(pwd):/work -it olgapaw/doxygen-latex doxygen

cd latex

docker run --rm -v $(pwd):/work -it olgapaw/doxygen-latex make