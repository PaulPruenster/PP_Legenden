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

perf stat -e rC701 ./sequential 1
perf stat -e rC702 ./sequential 1
perf stat -e rC704 ./sequential 1
perf stat -e rC708 ./sequential 1
perf stat -e rC710 ./sequential 1
perf stat -e rC71F ./sequential 1

