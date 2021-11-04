#!/bin/bash

# Links together `to_post` and `post_calc`
# takes a infix expr and computes it

./to_post.exe "$1" | { read -d '' x; ./post_calc.exe "$x"; }
