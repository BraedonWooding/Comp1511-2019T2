#!/bin/bash

gcc ll_v"$1".c -o ll_v
LLV_INCLUDE_PTRS_ON_SINGLE_BOX=1 ./ll_v $2

