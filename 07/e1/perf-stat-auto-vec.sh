#!/bin/bash

# Execute job in the partition "lva" unless you have special requirements.
#SBATCH --partition=lva
# Name your job to be able to identify it later
#SBATCH --job-name mergesort_parallel
# Redirect output stream to this file
#SBATCH --output=perf-stat-auto-vec.log
# Maximum number of tasks (=processes) to start in total
#SBATCH --ntasks=1
# Maximum number of tasks (=processes) to start per node
#SBATCH --ntasks-per-node=1
# Enforce exclusive node allocation, do not share with other jobs
#SBATCH --exclusive

perf stat -e rC701 ./e1_auto-vectorization 1
perf stat -e rC702 ./e1_auto-vectorization 1
perf stat -e rC704 ./e1_auto-vectorization 1
perf stat -e rC708 ./e1_auto-vectorization 1
perf stat -e rC710 ./e1_auto-vectorization 1
perf stat -e rC71F ./e1_auto-vectorization 1

