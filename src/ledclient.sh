#!/bin/bash

# pipes to communicate with server
pipe=/tmp/myfifo1
pipew=${pipe}_sr
piper=${pipe}_sw

mydir=`dirname $0`
me=`basename $0`

function show_help
{
  echo 'Usage:'
  echo "$me <args>"
  echo "Examples:"
  echo "$me server <start|stop>"
  echo "$me on|off|state"
  echo "$me color [red|green|blue]"
  echo "$me rate [0..5]"
}

function execute_command
{
  if [[ ! -p $pipew || ! -p $piper ]]; then
    echo "Server not running"
    exit 1
  fi

  local cmd
  cmd=$1
  echo $cmd > $pipew
  read line < $piper
  echo $line
}

function check_result
{
  local results
  results=("$1")
  if [[ ${results[0]} != "OK" ]]; then
    echo 'Command' ${results[0]}
    return 1
  fi
  return 0
}

function _set_param
{
  echo "Changing LED $1 to $2"
  local result
  result=$(execute_command "set-led-$1 $2")
  if [[ $? != 0 ]]; then
    echo 'Error:' $result
    return $?
  fi
  check_result $result
  if [[ $? == 0 ]]; then
    echo 'Done'
  fi
}

function _get_param
{
  local result args
  result=$(execute_command "get-led-$1")
  if [[ $? != 0 ]]; then
    echo 'Error:' $result
    return $?
  fi

  IFS=' ' read -a args <<< "$result"
  check_result ${args[0]}
  if [[ $? == 0 ]]; then
    echo "LED $1 is ${args[1]}"
  fi
}

# Simple commands in args

function on
{
  _set_param state on
  return $?
}

function off
{
  _set_param state off
  return $?
}

function state
{
  _get_param state
  return $?
}

function color
{
  if [[ -z $1 ]]; then
    _get_param color
  else
    _set_param color $1
  fi
  return $?
}

function rate
{
  if [[ -z $1 ]]; then
    _get_param rate
  else
    _set_param rate $1
  fi
  return $?
}

function server
{
  if [[ $1 == "start" ]]; then
    ${mydir}/ledcontrol $pipe &
    echo 'Done'
  fi
  if [[ $1 == "stop" ]]; then
    execute_command 'exit'
  fi
  return $?
}

function summary
{
  state && color && rate
  return $?
}


help_commands=("-h help --help")
if [[ $help_commands =~ $1 || -z $1 ]]; then
  show_help
else
  eval $1 $2
fi