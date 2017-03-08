#!/bin/bash
QUEUE=medium
Time=48:00
bsub -q $QUEUE -W $Time -W $Time "sh BatchJobs.sh  1.0"
bsub -q $QUEUE -W $Time -W $Time "sh BatchJobs.sh  1.1"
bsub -q $QUEUE -W $Time -W $Time "sh BatchJobs.sh  1.2"
bsub -q $QUEUE -W $Time -W $Time "sh BatchJobs.sh  1.3"
bsub -q $QUEUE -W $Time -W $Time "sh BatchJobs.sh  1.4"
bsub -q $QUEUE -W $Time -W $Time "sh BatchJobs.sh  1.5"
bsub -q $QUEUE -W $Time -W $Time "sh BatchJobs.sh  1.6"
bsub -q $QUEUE -W $Time -W $Time "sh BatchJobs.sh  1.7"
bsub -q $QUEUE -W $Time -W $Time "sh BatchJobs.sh  1.8"
bsub -q $QUEUE -W $Time -W $Time "sh BatchJobs.sh  1.9"
bsub -q $QUEUE -W $Time -W $Time "sh BatchJobs.sh  2.0"
bsub -q $QUEUE -W $Time -W $Time "sh BatchJobs.sh  2.1"
bsub -q $QUEUE -W $Time -W $Time "sh BatchJobs.sh  2.2"
bsub -q $QUEUE -W $Time -W $Time "sh BatchJobs.sh  2.3"
bsub -q $QUEUE -W $Time -W $Time "sh BatchJobs.sh  2.4"
bsub -q $QUEUE -W $Time -W $Time "sh BatchJobs.sh  2.5"
