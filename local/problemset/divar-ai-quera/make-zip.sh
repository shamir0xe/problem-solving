#!/bin/bash

if [[ $# -lt 1 ]]; then
  echo "Enter the file name"
  exit 1
fi

if [[ -f "$1.zip" ]]; then
  echo "Remove the previous instance"
  rm -rf "$1.zip"
fi

zip -jr "$1.zip" src/solution.py src/python_requirements.txt
