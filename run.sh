#!/bin/bash

cleanup(){
  echo ""
  tput cnorm
}
trap cleanup EXIT INT

tput civis
./build/main "$@"
