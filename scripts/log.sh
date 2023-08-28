#!/bin/bash
set -e
VERSION=0.0.0

function log()
{
    if [ $# -eq 2 ]; then
        log_level=$2
    else
        log_level="error"
    fi
    
    if [[ "$log_level" = "info" || "$log_level" = "INFO" ]];then
        echo "[$(date "+%Y-%m-%d %T")][$log_level]$1" >> ${LOG_FILE}
    else
        echo "[$(date "+%Y-%m-%d %T")][$log_level]$1" | tee -a ${LOG_FILE}
    fi
}
