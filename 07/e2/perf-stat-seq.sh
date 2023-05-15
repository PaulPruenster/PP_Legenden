#!/bin/bash

# Execute job in the partition "lva" unless you have special requirements.
#SBATCH --partition=lva
# Name your job to be able to identify it later
#SBATCH --job-name perf_sequential
# Redirect output stream to this file
#SBATCH --output=perf_sequential.log
# Maximum number of tasks (=processes) to start in total
#SBATCH --ntasks=1
# Maximum number of tasks (=processes) to start per node
#SBATCH --ntasks-per-node=1
# Enforce exclusive node allocation, do not share with other jobs
#SBATCH --exclusive

perf stat -e r01C7 ./sequential 1
perf stat -e r02C7 ./sequential 1
perf stat -e r04C7 ./sequential 1
perf stat -e r08C7 ./sequential 1
perf stat -e r10C7 ./sequential 1
perf stat -e r1FC7 ./sequential 1

