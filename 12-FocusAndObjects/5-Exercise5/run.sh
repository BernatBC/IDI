#!/bin/bash

qmake && make -j$(nproc) && ./Bloc3_Exemple && make distclean
