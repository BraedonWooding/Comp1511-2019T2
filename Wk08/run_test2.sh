#!/bin/bash

gcc ll_v2.c -o ll_v2
LLV_INCLUDE_PTRS_ON_SINGLE_BOX=1 ./ll_v2 $1

