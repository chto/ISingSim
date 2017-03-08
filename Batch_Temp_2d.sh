#!/bin/bash
QUEUE=medium
Time=48:00
bsub -q $QUEUE -W $Time -W $Time "sh BatchJobs.sh  0.1"
bsub -q $QUEUE -W $Time -W $Time "sh BatchJobs.sh  0.2"
bsub -q $QUEUE -W $Time -W $Time "sh BatchJobs.sh  0.3"
bsub -q $QUEUE -W $Time -W $Time "sh BatchJobs.sh  0.4"
bsub -q $QUEUE -W $Time -W $Time "sh BatchJobs.sh  0.5"
bsub -q $QUEUE -W $Time -W $Time "sh BatchJobs.sh  0.6"
bsub -q $QUEUE -W $Time -W $Time "sh BatchJobs.sh  0.7"
bsub -q $QUEUE -W $Time -W $Time "sh BatchJobs.sh  0.8"
bsub -q $QUEUE -W $Time -W $Time "sh BatchJobs.sh  0.9"
bsub -q $QUEUE -W $Time -W $Time "sh BatchJobs.sh  1.0"
bsub -q $QUEUE -W $Time -W $Time "sh BatchJobs.sh  1.1"
bsub -q $QUEUE -W $Time -W $Time "sh BatchJobs.sh  1.2"
bsub -q $QUEUE -W $Time -W $Time "sh BatchJobs.sh  1.3"
bsub -q $QUEUE -W $Time -W $Time "sh BatchJobs.sh  1.4"
bsub -q $QUEUE -W $Time -W $Time "sh BatchJobs.sh  1.5"
bsub -q $QUEUE -W $Time -W $Time "sh BatchJobs.sh  1.6"
