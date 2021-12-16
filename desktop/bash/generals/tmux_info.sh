#!/bin/bash

################# check binary #################
tmux_path=$(command -v tmux)
if [ -z "$tmux_path" ];then echo "tmux not found";exit;fi

watch_path=$(command -v watch)
if [ -z "$watch_path" ];then echo "watch not found";exit;fi

sensors_path=$(command -v sensors)
if [ -z "$sensors_path" ];then echo "sensors not found";exit;fi

htop_path=$(command -v htop)
if [ -z "$htop_path" ];then echo "htop not found";exit;fi

iostat_path=$(command -v iostat)
if [ -z "$iostat_path" ];then echo "iostat not found";exit;fi

bmon_path=$(command -v bmon)
if [ -z "$bmon_path" ];then echo "bmon not found";exit;fi

################# start new tmux session #################
session="watch_info"
tmux new -d -s $session

################# split window into 4 panes #################
tmux split-window -v -t $session
tmux select-pane -t 0
tmux split-window -h -t $session
tmux select-pane -t 2
tmux split-window -h -t $session

################# start programs in each pane #################
tmux send-keys -t $session:0.0 'htop' C-m
tmux send-keys -t $session:0.1 'watch -n1 iostat' C-m
tmux send-keys -t $session:0.2 'bmon' C-m
tmux send-keys -t $session:0.3 'watch -n1 sensors' C-m

################# actual tmux running #################
tmux attach -t $session
